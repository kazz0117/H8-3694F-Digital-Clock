#include "3694F.h"
#include "global_ex.h"
#include "sys_def.h"
#include "led_def.h"
#include "clock_def.h"
#include <machine.h>

#define TIMER_INFO_NUM 16

extern T_TIME gCurrentTime;

// �����V���b�g�^�C�}�[���
typedef struct {
	_UBYTE state;	// ���ꂪ0�̂Ƃ��ق��̃����o�̒l�͖��Ӗ�!!
	#define STATE_TIMER_UNUSED  (0)
	#define STATE_TIMER_RUNNING (1)
	_UDWORD time_set;	// �ݒ莞��(ms)
	_UDWORD time_remaining;	// �c�莞��(ms)
	void (*func)();	// �^�C���A�E�g���ɌĂԃR�[���o�b�N�֐�
} T_TIMER_INFO;

// �O���[�o���ϐ�
T_TIMER_INFO TimerInfo[TIMER_INFO_NUM];
_SINT gBeepOn = 0;
_SINT gLedLightingEnable;

// �v���g�^�C�v�錾
static void ManageTimer(void);
static void CheckAlarmingTime(T_TIME *time);
static void StopAlarm(void);

///////////////////////////
// �^�C�}�[�`������      //
///////////////////////////
void InitTimerA(void)
{
		// �^�C�}�[�`(���v�p�^�C���x�[�X) //
	TIMERA->TMA.STYLE.CLUSTER.OUTPUT_SELECT = 0x00;	// TMOW�[�q�o�̓N���b�N(���g�p) �������ꂢ��Ȃ�������
	TIMERA->TMA.STYLE.CLUSTER.INTERNAL_CLOCK_SELECT3 = 1;	// �v���X�P�[���v���v�p�^�C���x�[�X�ɐݒ�
	TIMERA->TMA.STYLE.CLUSTER.OVERFLOW_PERIOD = 1;	// �I�[�o�[�t���[����0.5s
}

////////////////////////////////
// �^�C�}�[�`���荞�݃n���h�� //
////////////////////////////////
void TimerA_IH(void)
{
static _SINT count;
static _SINT flg_LED;

#define CORRECTION_ENABLE  (1)
#define CORRECTION_DISABLE (0)

static _SINT SecondCorrection = CORRECTION_ENABLE;

	set_imask_ccr((_UBYTE)1);	// ���荞�݋֎~

	INTERRUPT->IRR1.BIT.IRRTA = 0;

	// LED�u�����N��gLedLightingEnable�̒l��LED�h���C�o������
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

		// ���ݎ�����i�߂鏈��	
		if(++gCurrentTime.ss == 60) {
			gCurrentTime.ss = 0;
			if(++gCurrentTime.mm == 60) {
				gCurrentTime.mm = 0;
				if(++gCurrentTime.hh == 24) {
					gCurrentTime.hh = 0;
				}
			}
		}

		// �덷�␳����(�b���̓}�C�R���{�[�h�̃��b�g�Ɉˑ�)
		if(gCurrentTime.hh == 0 && gCurrentTime.mm == 0 && gCurrentTime.ss == 0) {
			SecondCorrection = CORRECTION_ENABLE;
		}
		if(gCurrentTime.hh == 0 && gCurrentTime.mm == 0 && gCurrentTime.ss == 1 && SecondCorrection == CORRECTION_ENABLE) {
			gCurrentTime.ss = 0;
			SecondCorrection = CORRECTION_DISABLE;
		}


		// �A���[����炷�ׂ��������������
		CheckAlarmingTime(&gCurrentTime);

		set_imask_ccr((_UBYTE)0);	// ���荞�݋���

	}



}

///////////////////////////
// �^�C�}�[�u������      //
///////////////////////////
void InitTimerV(void)
{
_SINT i;
	TIMERV->TCRV0.BIT.CKS = 0x03;	// �����N���b�N��/128�ŃJ�E���g
									// CLOCK=20MHz�Ȃ�156250Hz�ɂȂ�B
	TIMERV->TCRV1.BIT.ICKS0 = 1;	//
	
	TIMERV->TCORA.BYTE = 156;	// 156250/156=1001.603Hz
								// �����1msec�ɔ��ɋ߂����Ԃ𓾂�
								
	TIMERV->TCRV0.BIT.CCLR = 0x01;	// �R���y�A�}�b�`�`�ŃJ�E���^���N���A
	
	// �g�������V���b�g�^�C�}��񏉊���
	for(i = 0; i < TIMER_INFO_NUM; i++) {
		TimerInfo[i].state = STATE_TIMER_UNUSED;
	}
}

////////////////////////////////
// �^�C�}�[�u���荞�݃n���h�� //
////////////////////////////////
void TimerV_IH(void)
{
static _SINT flg_beep;

	TIMERV->TCSRV.BIT.CMFA = 0;	// ���荞�ݗv�����N���A

	//Beep
	if(flg_beep == 1 && gBeepOn == 1) {
		PORT1->DATAR.BIT.P14 = 1;
		flg_beep = 0;
	} else {
		PORT1->DATAR.BIT.P14 = 0;
		flg_beep = 1;
	}
			
	ManageTimer();	// �����V���b�g�^�C�}�[�̃J�E���g�_�E������

}

////////////////////////////////
// �����V���b�g�^�C�}�[���Z   //
////////////////////////////////
static void ManageTimer(void)
{
_SINT i;

	for(i = 0; i < TIMER_INFO_NUM; i++) {
		// ���쒆�̃^�C�}�[����������(�c�莞�Ԍ��Z�Ō��ʂ�0�̃^�C�}�[�̓_��)
		if(TimerInfo[i].state == STATE_TIMER_RUNNING && TimerInfo[i].time_set != 0) {
			// �c�莞�Ԃ�-1msec����
			TimerInfo[i].time_remaining--;
			// ���ʁA�c�莞�Ԃ�0�ɂȂ��Ă�����
			if(TimerInfo[i].time_remaining == 0) {
				// �^�C�}�[�����
				TimerInfo[i].state = STATE_TIMER_UNUSED;
				// �R�[���o�b�N�֐����Ă�
				TimerInfo[i].func();
			}
		}
	}
}

////////////////////////////////
// �����V���b�g�^�C�}�[�Z�b�g //
////////////////////////////////
_SINT SetTimer(_UDWORD time, void *func)
{
_SINT i;
	if(time != 0 && func != NULL) {
		// �󂢂Ă�^�C�}���������c
		for(i = 0; i < TIMER_INFO_NUM; i++) {
			if(TimerInfo[i].state == STATE_TIMER_UNUSED) {
				// �^�C�}����ݒ肵�ėL����(����!!)
				TimerInfo[i].state = STATE_TIMER_RUNNING;
				TimerInfo[i].time_set = time;
				TimerInfo[i].time_remaining = time;
				TimerInfo[i].func = (void *)func;

				return i;	// �^�C�}�[ID
			}			
		}		
		return SYS_TIMER_FULL;	
	} else {
		return SYS_ERROR;
	}
}

////////////////////////////////
// �^�C�}�[�L�����Z��         //
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
// �w�莞��beep���J�n       //
////////////////////////////////
void BeepOn(_UDWORD time)
{
	SetTimer(time, BeepOff);
	gBeepOn = 1;
}

////////////////////////////////
// beep����~               //
////////////////////////////////
void BeepOff(void)
{
	gBeepOn = 0;
}

////////////////////////////////
// �w�莞���ɃA���[����     //
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
		
		PORT1->DATAR.BIT.P15 = 0;	// �A���[�����J�n
		SetTimer(1000L, StopAlarm);	// �A���[������~
		
	}
	
}

////////////////////////////////
// �A���[������~           //
////////////////////////////////
static void StopAlarm(void)
{
	PORT1->DATAR.BIT.P15 = 1;
}
