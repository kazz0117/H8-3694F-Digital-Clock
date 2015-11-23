// �L�[�X�L�����^�X�N

#include "global_ex.h"
#include "key_def.h"
#include <machine.h>

#define KEY_WAIT (150)

// �O���[�o���ϐ�
_SINT Key1State = KEY_OFF;
_SINT Key2State = KEY_OFF;
_SINT Key3State = KEY_OFF;
_SINT Key4State = KEY_OFF;

void ScanKeys(void)
{
static _SINT Key1Count = 0;
static _SINT Key2Count = 0;
static _SINT Key3Count = 0;
static _SINT Key4Count = 0;
static _SINT KeyWaitCount = 0;

	if(KeyWaitCount >= 1) {
		KeyWaitCount--;
	}

	// �L�[�P
	if(PORTB->DATAR.BIT.PB6 == 1 && Key1State == KEY_OFF && KeyWaitCount == 0) {
		Key1Count++;
		if(Key1Count >= 5) {
			Key1State = KEY_ON;
			Key1Count = 0;
			KeyWaitCount = KEY_WAIT;
		}
	} else {
		Key1State = KEY_OFF;
		Key1Count = 0;
	}

	// �L�[�Q
	if(PORTB->DATAR.BIT.PB1 == 1 && Key2State == KEY_OFF && KeyWaitCount == 0) {
		Key2Count++;
		if(Key2Count >= 5) {
			Key2State = KEY_ON;
			Key2Count = 0;
			KeyWaitCount = KEY_WAIT;
		}
	} else {
		Key2State = KEY_OFF;
		Key2Count = 0;
	}

	// �L�[�R
	if(PORTB->DATAR.BIT.PB2 == 1 && Key3State == KEY_OFF && KeyWaitCount == 0) {
		Key3Count++;
		if(Key3Count >= 5) {
			Key3State = KEY_ON;
			Key3Count = 0;
			KeyWaitCount = KEY_WAIT;
		}
	} else {
		Key3State = KEY_OFF;
		Key3Count = 0;
	}

	// �L�[�S
	if(PORTB->DATAR.BIT.PB3 == 1 && Key4State == KEY_OFF && KeyWaitCount == 0) {
		Key4Count++;
		if(Key4Count >= 5) {
			Key4State = KEY_ON;
			Key4Count = 0;
			KeyWaitCount = KEY_WAIT;
		}
	} else {
		Key4State = KEY_OFF;
		Key4Count = 0;
	}
	
	SetTimer(2L, ScanKeys);
}

