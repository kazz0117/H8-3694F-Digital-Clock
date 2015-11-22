/***********************************************************************/
/*                                                                     */
/*  FILE        :clock.c                                               */
/*  DATE        :Fri, Sep 20, 2013                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3694F                                              */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.16).    */
/*                                                                     */
/***********************************************************************/
                  
#include "3694F.h"
#include "binary_def.h"
#include "led_def.h"
#include "clock_def.h"
#include "key_def.h"
#include <machine.h>

// 時計のモード
enum {	MODE_ADJUSTING,
		MODE_DISPLAYING,
};

#define ADJUSTMENT_WAIT_COUNT (3000L)

// 時刻設定の状態
enum {	ADJUSTING_INIT,
		ADJUSTING_HOUR,
		ADJUSTING_MINUTE,
		ADJUSTING_SECOND,
		ADJUSTING_CANCELED,
		ADJUSTING_DONE,
};

// グローバル変数
// I/Oポート(h8/3694f用定義) //
volatile T_P1   *PORT1     = (T_P1   *)0xffd0;	// Port1
volatile T_P2   *PORT2     = (T_P2   *)0xffd5;	// Port2
volatile T_P5   *PORT5     = (T_P5   *)0xffd1;	// Port5
volatile T_P7   *PORT7     = (T_P7   *)0xffda;	// Port7
volatile T_P8   *PORT8     = (T_P8   *)0xffdb;	// Port8
volatile T_PB   *PORTB     = (T_PB   *)0xffdd;	// PortB
volatile T_WDT  *TIMER     = (T_WDT  *)0xffc0;	// ウォッチドッグタイマー
volatile T_TIMA *TIMERA    = (T_TIMA *)0xffa6;	// タイマＡ
volatile T_TIMV *TIMERV    = (T_TIMV *)0xffa0; 	// タイマＶ
volatile T_INT  *INTERRUPT = (T_INT  *)0xfff2;	// 割り込み

T_TIME gCurrentTime;	// 現在時刻
int ClockMode = MODE_ADJUSTING;	// 	現在の時計モード
int AdjustmentState = ADJUSTING_INIT;	// 時刻設定の状態

extern T_LED_INFO gLedInfo[DIGITS_NUM];

// プロトタイプ宣言
void InitPort(void);
void InitCurrentTime(void);
void DisplayCurrentTime(void);
void AdjustTime(void);
void Wait(_UDWORD time);
void TimeAdjustmentInit(T_TIME *time);
void TimeAdjustmentHour(T_TIME *time);
void TimeAdjustmentMinute(T_TIME *time);
void TimeAdjustmentSecond(T_TIME *time);

///////////////////////////
// メイン                //
///////////////////////////
void main(void)
{

	// システム起動時初期化
	set_imask_ccr((_UBYTE)1);	// 割り込み禁止

	InitPort();
	InitTimerA();
	InitTimerV();
	InitCurrentTime();
	
	INTERRUPT->IRR1.BIT.IRRTA = 0;	
	INTERRUPT->IENR1.BIT.IENTA = 1;	// タイマーＡ割り込み要求有効化

	TIMERV->TCSRV.BIT.CMFA = 0;	// タイマーＶコンペアマッチＡ(割り込み要因？)クリア
	TIMERV->TCRV0.BIT.CMIEA = 1;	// タイマーＶ割り込み要求

	set_imask_ccr((_UBYTE)0);	// 割り込み許可

	InitDigitsValues();
	// ７セグメントLED表示タスク起動
	StartLed();
	// キースキャンタスク起動
	ScanKeys();

	
	for(;;) {

		switch(ClockMode) {
			case MODE_ADJUSTING:
				AdjustTime();
				break;
		
			case MODE_DISPLAYING:
				DisplayCurrentTime();
				break;
		
			default:
				break;
		}
	}

}

///////////////////////////
// 入出力ポート初期化    //
///////////////////////////
void InitPort(void)
{
	// ポート１
	PORT1->CTRLR.BIT.PCR11 = 1;	// コロン(アノード) 出力
	PORT1->CTRLR.BIT.PCR12 = 1;	// コロン(カソード) 出力
	PORT1->CTRLR.BIT.PCR14 = 1;	// beep 出力
	PORT1->CTRLR.BIT.PCR15 = 1;	// アラーム制御 出力
	PORT1->DATAR.BIT.P15 = 1;	// アラーム非鳴動(負論理)
	
	// ポート５
	PORT5->CTRLR.BIT.PCR50 = 1;	// 7セグdigit1 出力
	PORT5->CTRLR.BIT.PCR51 = 1;	// 7セグdigit2 出力
	PORT5->CTRLR.BIT.PCR52 = 1;	// 7セグdigit3 出力
	PORT5->CTRLR.BIT.PCR53 = 1;	// 7セグdigit4 出力
	PORT5->CTRLR.BIT.PCR54 = 1;	// 7セグdigit5 出力
	PORT5->CTRLR.BIT.PCR55 = 1;	// 7セグdigit6 出力

	// ポート８
	PORT8->CTRLR.BIT.PCR80 = 1; // 7セグ'a' 出力
	PORT8->CTRLR.BIT.PCR81 = 1; // 7セグ'b' 出力
	PORT8->CTRLR.BIT.PCR82 = 1; // 7セグ'c' 出力
	PORT8->CTRLR.BIT.PCR83 = 1; // 7セグ'd' 出力
	PORT8->CTRLR.BIT.PCR84 = 1; // 7セグ'e' 出力
	// PCR85はブートモード用に使用済
	PORT8->CTRLR.BIT.PCR86 = 1; // 7セグ'f' 出力
	PORT8->CTRLR.BIT.PCR87 = 1; // 7セグ'g' 出力
}

///////////////////////////
// 現在時刻初期化        //
///////////////////////////
void InitCurrentTime(void)
{
	gCurrentTime.hh = 0;	// 時
	gCurrentTime.mm = 0;	// 分
	gCurrentTime.ss = 0;	// 秒	
}

///////////////////////////
// 現在時刻表示          //
///////////////////////////
void DisplayCurrentTime(void) {
	gLedInfo[DIGIT2].value = gCurrentTime.ss / 10;
	gLedInfo[DIGIT1].value = gCurrentTime.ss % 10;
	gLedInfo[DIGIT4].value = gCurrentTime.mm / 10;
	gLedInfo[DIGIT3].value = gCurrentTime.mm % 10;
	gLedInfo[DIGIT6].value = gCurrentTime.hh / 10;
	gLedInfo[DIGIT5].value = gCurrentTime.hh % 10;

	// キー１が押下されたら時刻設定モードに遷移
	if(Key1State == KEY_ON) {
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
		ClockMode = MODE_ADJUSTING;
		AdjustmentState = ADJUSTING_INIT;
	}

}

///////////////////////////
// 時刻設定              //
///////////////////////////
void AdjustTime(void) {
static T_TIME AdjustingTime;
	
	switch(AdjustmentState) {
		// 時刻設定初期処理
		case ADJUSTING_INIT:
			TimeAdjustmentInit(&AdjustingTime);
			break;

		// 時設定
		case ADJUSTING_HOUR:
			TimeAdjustmentHour(&AdjustingTime);
			break;

		// 分設定
		case ADJUSTING_MINUTE:
			TimeAdjustmentMinute(&AdjustingTime);
			break;

		// 秒設定
		case ADJUSTING_SECOND:
			TimeAdjustmentSecond(&AdjustingTime);
			break;
			
	}
}

//////////////////////////////
// 指定時間何もしないで待つ //
//////////////////////////////
void Wait(_UDWORD time)
{
_UDWORD i;
volatile int a;
	for(i = 0; i < time; i++) {
		a += i;
	}
}

///////////////////////////
// 時刻設定初期処理      //
///////////////////////////
void TimeAdjustmentInit(T_TIME *time)
{
	// 現在時刻をもってくる
	time->hh = gCurrentTime.hh;
	time->mm = gCurrentTime.mm;
	time->ss = gCurrentTime.ss;
	// 表示
	gLedInfo[DIGIT2].value = time->ss / 10;
	gLedInfo[DIGIT1].value = time->ss % 10;
	gLedInfo[DIGIT4].value = time->mm / 10;
	gLedInfo[DIGIT3].value = time->mm % 10;
	gLedInfo[DIGIT6].value = time->hh / 10;
	gLedInfo[DIGIT5].value = time->hh % 10;
	// 時設定状態に遷移
	AdjustmentState = ADJUSTING_HOUR;
}

///////////////////////////
// 「時」設定            //
///////////////////////////
void TimeAdjustmentHour(T_TIME *time)
{
	// 表示
	gLedInfo[DIGIT6].value = time->hh / 10; gLedInfo[DIGIT6].state = STATE_LED_BLINK;
	gLedInfo[DIGIT5].value = time->hh % 10; gLedInfo[DIGIT5].state = STATE_LED_BLINK;
	// カウントダウン
	if(Key2State == KEY_ON) {
		if(--time->hh == -1) {
			time->hh = 23;
		}
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// カウントアップ
	if(Key3State == KEY_ON) {
		if(++time->hh == 24) {
			time->hh = 0;
		}
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// 時刻設定キャンセル
	if(Key1State == KEY_ON) {
		gLedInfo[DIGIT6].state = STATE_LED_ON;
		gLedInfo[DIGIT5].state = STATE_LED_ON;
		ClockMode = MODE_DISPLAYING;
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// 分設定に遷移
	if(Key4State == KEY_ON) {
		gLedInfo[DIGIT6].state = STATE_LED_ON;
		gLedInfo[DIGIT5].state = STATE_LED_ON;
		AdjustmentState = ADJUSTING_MINUTE;
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
}

///////////////////////////
// 「分」設定            //
///////////////////////////
void TimeAdjustmentMinute(T_TIME *time)
{
	// 表示
	gLedInfo[DIGIT4].value = time->mm / 10; gLedInfo[DIGIT4].state = STATE_LED_BLINK;
	gLedInfo[DIGIT3].value = time->mm % 10; gLedInfo[DIGIT3].state = STATE_LED_BLINK;
	// カウントダウン
	if(Key2State == KEY_ON) {
		if(--time->mm == -1) {
			time->mm = 59;
		}
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// カウントアップ
	if(Key3State == KEY_ON) {
		if(++time->mm == 60) {
			time->mm = 0;
		}
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// 時刻設定キャンセル
	if(Key1State == KEY_ON) {
		gLedInfo[DIGIT4].state = STATE_LED_ON;
		gLedInfo[DIGIT3].state = STATE_LED_ON;
		ClockMode = MODE_DISPLAYING;
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// 秒設定に遷移
	if(Key4State == KEY_ON) {
		gLedInfo[DIGIT4].state = STATE_LED_ON;
		gLedInfo[DIGIT3].state = STATE_LED_ON;
		AdjustmentState = ADJUSTING_SECOND;
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
}

///////////////////////////
// 「秒」設定            //
///////////////////////////
void TimeAdjustmentSecond(T_TIME *time)
{
	// 表示
	gLedInfo[DIGIT2].value = time->ss / 10; gLedInfo[DIGIT2].state = STATE_LED_BLINK;
	gLedInfo[DIGIT1].value = time->ss % 10; gLedInfo[DIGIT1].state = STATE_LED_BLINK;
	// カウントダウン
	if(Key2State == KEY_ON) {
		if(--time->ss == -1) {
			time->ss = 59;
		}
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// カウントアップ
	if(Key3State == KEY_ON) {
		if(++time->ss == 60) {
			time->ss = 0;
		}
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// 時刻設定キャンセル
	if(Key1State == KEY_ON) {
		gLedInfo[DIGIT2].state = STATE_LED_ON;
		gLedInfo[DIGIT1].state = STATE_LED_ON;
		ClockMode = MODE_DISPLAYING;
		BeepOn(32L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
	// 時刻設定を完了して時刻表示モードに遷移
	if(Key4State == KEY_ON) {
		gLedInfo[DIGIT2].state = STATE_LED_ON;
		gLedInfo[DIGIT1].state = STATE_LED_ON;
		// 現在時刻を設定
		set_imask_ccr((_UBYTE)1);	// 割り込み禁止
		gCurrentTime.ss = time->ss;
		gCurrentTime.mm = time->mm;
		gCurrentTime.hh = time->hh;
		set_imask_ccr((_UBYTE)0);	// 割り込み許可
		ClockMode = MODE_DISPLAYING;
		BeepOn(128L);
		Wait(ADJUSTMENT_WAIT_COUNT);
	}
}
