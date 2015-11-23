#include "3694F.h"
#include "global_ex.h"
#include "sys_def.h"
#include "led_def.h"
#include "clock_def.h"
#include <machine.h>

#define TIMER_INFO_NUM 16

extern T_TIME gCurrentTime;

// ワンショットタイマー情報
typedef struct {
	_UBYTE state;	// これが0のときほかのメンバの値は無意味!!
	#define STATE_TIMER_UNUSED  (0)
	#define STATE_TIMER_RUNNING (1)
	_UDWORD time_set;	// 設定時間(ms)
	_UDWORD time_remaining;	// 残り時間(ms)
	void (*func)();	// タイムアウト時に呼ぶコールバック関数
} T_TIMER_INFO;

// グローバル変数
T_TIMER_INFO TimerInfo[TIMER_INFO_NUM];
_SINT gBeepOn = 0;
_SINT gLedLightingEnable;

// プロトタイプ宣言
static void ManageTimer(void);
static void CheckAlarmingTime(T_TIME *time);
static void StopAlarm(void);

///////////////////////////
// タイマーＡ初期化      //
///////////////////////////
void InitTimerA(void)
{
		// タイマーＡ(時計用タイムベース) //
	TIMERA->TMA.STYLE.CLUSTER.OUTPUT_SELECT = 0x00;	// TMOW端子出力クロック(未使用) ←★これいらないかも★
	TIMERA->TMA.STYLE.CLUSTER.INTERNAL_CLOCK_SELECT3 = 1;	// プリスケーラＷ時計用タイムベースに設定
	TIMERA->TMA.STYLE.CLUSTER.OVERFLOW_PERIOD = 1;	// オーバーフロー周期0.5s
}

////////////////////////////////
// タイマーＡ割り込みハンドラ //
////////////////////////////////
void TimerA_IH(void)
{
static _SINT count;
static _SINT flg_LED;

#define CORRECTION_ENABLE  (1)
#define CORRECTION_DISABLE (0)

static _SINT SecondCorrection = CORRECTION_ENABLE;

	set_imask_ccr((_UBYTE)1);	// 割り込み禁止

	INTERRUPT->IRR1.BIT.IRRTA = 0;

	// LEDブリンクはgLedLightingEnableの値をLEDドライバが見る
	if(gLedLightingEnable == LED_DISABLE) {

		PORT1->DATAR.BIT.P11 = 1;	// LED
		PORT1->DATAR.BIT.P12 = 1;	// LED

		gLedLightingEnable = LED_ENABLE;
	} else {

		PORT1->DATAR.BIT.P11 = 0;	// LED
		PORT1->DATAR.BIT.P12 = 0;	// LED

		gLedLightingEnable = LED_DISABLE;
	}
	
	count++;
	if(count == 2) {
		count = 0;

		// 現在時刻を進める処理	
		if(++gCurrentTime.ss == 60) {
			gCurrentTime.ss = 0;
			if(++gCurrentTime.mm == 60) {
				gCurrentTime.mm = 0;
				if(++gCurrentTime.hh == 24) {
					gCurrentTime.hh = 0;
				}
			}
		}

		// 誤差補正処理(秒数はマイコンボードのロットに依存)
		if(gCurrentTime.hh == 0 && gCurrentTime.mm == 0 && gCurrentTime.ss == 0) {
			SecondCorrection = CORRECTION_ENABLE;
		}
		if(gCurrentTime.hh == 0 && gCurrentTime.mm == 0 && gCurrentTime.ss == 1 && SecondCorrection == CORRECTION_ENABLE) {
			gCurrentTime.ss = 0;
			SecondCorrection = CORRECTION_DISABLE;
		}


		// アラームを鳴らすべき時刻だったら鳴動
		CheckAlarmingTime(&gCurrentTime);

		set_imask_ccr((_UBYTE)0);	// 割り込み許可

	}



}

///////////////////////////
// タイマーＶ初期化      //
///////////////////////////
void InitTimerV(void)
{
_SINT i;
	TIMERV->TCRV0.BIT.CKS = 0x03;	// 内部クロックφ/128でカウント
									// CLOCK=20MHzなら156250Hzになる。
	TIMERV->TCRV1.BIT.ICKS0 = 1;	//
	
	TIMERV->TCORA.BYTE = 156;	// 156250/156=1001.603Hz
								// これで1msecに非常に近い時間を得る
								
	TIMERV->TCRV0.BIT.CCLR = 0x01;	// コンペアマッチＡでカウンタをクリア
	
	// 拡張ワンショットタイマ情報初期化
	for(i = 0; i < TIMER_INFO_NUM; i++) {
		TimerInfo[i].state = STATE_TIMER_UNUSED;
	}
}

////////////////////////////////
// タイマーＶ割り込みハンドラ //
////////////////////////////////
void TimerV_IH(void)
{
static _SINT flg_beep;

	TIMERV->TCSRV.BIT.CMFA = 0;	// 割り込み要因をクリア

	//Beep
	if(flg_beep == 1 && gBeepOn == 1) {
		PORT1->DATAR.BIT.P14 = 1;
		flg_beep = 0;
	} else {
		PORT1->DATAR.BIT.P14 = 0;
		flg_beep = 1;
	}
			
	ManageTimer();	// ワンショットタイマーのカウントダウン処理

}

////////////////////////////////
// ワンショットタイマー減算   //
////////////////////////////////
static void ManageTimer(void)
{
_SINT i;

	for(i = 0; i < TIMER_INFO_NUM; i++) {
		// 動作中のタイマーを見つけたら(残り時間減算で結果が0のタイマーはダメ)
		if(TimerInfo[i].state == STATE_TIMER_RUNNING && TimerInfo[i].time_set != 0) {
			// 残り時間を-1msecする
			TimerInfo[i].time_remaining--;
			// 結果、残り時間が0になっていたら
			if(TimerInfo[i].time_remaining == 0) {
				// タイマーおわり
				TimerInfo[i].state = STATE_TIMER_UNUSED;
				// コールバック関数を呼ぶ
				TimerInfo[i].func();
			}
		}
	}
}

////////////////////////////////
// ワンショットタイマーセット //
////////////////////////////////
_SINT SetTimer(_UDWORD time, void *func)
{
_SINT i;
	if(time != 0 && func != NULL) {
		// 空いてるタイマをさがす…
		for(i = 0; i < TIMER_INFO_NUM; i++) {
			if(TimerInfo[i].state == STATE_TIMER_UNUSED) {
				// タイマ情報を設定して有効化(発動!!)
				TimerInfo[i].state = STATE_TIMER_RUNNING;
				TimerInfo[i].time_set = time;
				TimerInfo[i].time_remaining = time;
				TimerInfo[i].func = (void *)func;

				return i;	// タイマーID
			}			
		}		
		return SYS_TIMER_FULL;	
	} else {
		return SYS_ERROR;
	}
}

////////////////////////////////
// タイマーキャンセル         //
////////////////////////////////
_SINT KillTimer(_SINT timer_id)
{
	if(TimerInfo[timer_id].state = STATE_TIMER_RUNNING){
		TimerInfo[timer_id].state = STATE_TIMER_UNUSED;
		return SYS_SUCCESS;
	} else {
		return SYS_ERROR;
	}
}

////////////////////////////////
// 指定時間beep鳴動開始       //
////////////////////////////////
void BeepOn(_UDWORD time)
{
	SetTimer(time, BeepOff);
	gBeepOn = 1;
}

////////////////////////////////
// beep鳴動停止               //
////////////////////////////////
void BeepOff(void)
{
	gBeepOn = 0;
}

////////////////////////////////
// 指定時刻にアラーム鳴動     //
////////////////////////////////
static void CheckAlarmingTime(T_TIME *time)
{
	if((time->hh ==  8 && time->mm == 55 && time->ss == 0) ||
	   (time->hh == 10 && time->mm == 30 && time->ss == 0) ||
	   (time->hh == 10 && time->mm == 45 && time->ss == 0) ||
	   (time->hh == 11 && time->mm == 50 && time->ss == 0) ||
	   (time->hh == 13 && time->mm ==  0 && time->ss == 0) ||
	   (time->hh == 14 && time->mm ==  0 && time->ss == 0) ||
	   (time->hh == 14 && time->mm == 15 && time->ss == 0) ||
	   (time->hh == 15 && time->mm ==  0 && time->ss == 0)   ) {
		
		PORT1->DATAR.BIT.P15 = 0;	// アラーム鳴動開始
		SetTimer(1000L, StopAlarm);	// アラーム鳴動停止
		
	}
	
}

////////////////////////////////
// アラーム鳴動停止           //
////////////////////////////////
static void StopAlarm(void)
{
	PORT1->DATAR.BIT.P15 = 1;
}
