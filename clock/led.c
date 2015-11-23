// 7�Z�O�����gLED�h���C�o

#include "global_ex.h"
#include "led_def.h"
#include "timer.h"

// �f�W�b�g��Ԏw��
enum {
	STATE_DIGIT6_ON,
	STATE_DIGIT5_ON,
	STATE_DIGIT4_ON,
	STATE_DIGIT3_ON,
	STATE_DIGIT2_ON,
	STATE_DIGIT1_ON,
	DIGIT_STATES_NUM,
};

// LED�_������
#define LED_LIGHTING_DURATION (3L)

// �t�H���g                       a  b  c  d  e  f  g
const _UBYTE Font[12][7] = {	{ 1, 1, 1, 1, 1, 1, 0},		// 0
	   							{ 0, 1, 1, 0, 0, 0, 0},		// 1
								{ 1, 1, 0, 1, 1, 0, 1},		// 2
								{ 1, 1, 1, 1, 0, 0, 1},		// 3
								{ 0, 1, 1, 0, 0, 1, 1},		// 4
								{ 1, 0, 1, 1, 0, 1, 1},		// 5
								{ 1, 0, 1, 1, 1, 1, 1},		// 6
								{ 1, 1, 1, 0, 0, 1, 0},		// 7
								{ 1, 1, 1, 1, 1, 1, 1},		// 8
								{ 1, 1, 1, 1, 0, 1, 1},		// 9
								{ 1, 1, 1, 0, 1, 1, 1},		// A(10)
								{ 0, 0, 0, 0, 0, 0, 1}	};	// -(11)

// �O���[�o���ϐ�
T_LED_INFO gLedInfo[DIGITS_NUM];
extern _SINT gLedLightingEnable;

// �v���g�^�C�v�錾
static void SetSegments(_SINT digit);
static void LedOff(void);

_SINT CurrentDigitState;

/////////////////////////////
// 7�Z�O�����gLED�\���J�n  //
/////////////////////////////
void StartLed(void)
{
	CurrentDigitState = STATE_DIGIT6_ON;
	DispDigit();
}

///////////////////////////
// 7�Z�O�����gLED�\��    //
///////////////////////////
void DispDigit(void)
{
	SetTimer(LED_LIGHTING_DURATION, DispDigit);

	// �d���f��7�Z�O�����gLED����
	if(PORTB->DATAR.BIT.PB4 == 0) {
		LedOff();
		return;
	}
	
	switch(CurrentDigitState) {
		case STATE_DIGIT6_ON:
			PORT5->DATAR.BIT.P50 = 0;	// �O�̌�������
			SetSegments(DIGIT6);
			// ���̌���_��
			if(gLedInfo[DIGIT6].state == STATE_LED_ON) {
				PORT5->DATAR.BIT.P55 = 1;
			// �u�����N�������ݒ肳��Ă���ꍇ
			} else if(gLedInfo[DIGIT6].state == STATE_LED_BLINK && gLedLightingEnable == LED_ENABLE) {
				PORT5->DATAR.BIT.P55 = 1;
			} else {
				PORT5->DATAR.BIT.P55 = 0;
			}
			break;
			
		case STATE_DIGIT5_ON:
			PORT5->DATAR.BIT.P55 = 0;	// �O�̌�������
			SetSegments(DIGIT5);
			// ���̌���_��
			if(gLedInfo[DIGIT5].state == STATE_LED_ON) {
				PORT5->DATAR.BIT.P54 = 1;
			// �u�����N�������ݒ肳��Ă���ꍇ
			} else if(gLedInfo[DIGIT5].state == STATE_LED_BLINK && gLedLightingEnable == LED_ENABLE) {
				PORT5->DATAR.BIT.P54 = 1;
			} else {
				PORT5->DATAR.BIT.P54 = 0;
			}
			break;

		case STATE_DIGIT4_ON:
			PORT5->DATAR.BIT.P54 = 0;	// �O�̌�������
			SetSegments(DIGIT4);
			// ���̌���_��
			if(gLedInfo[DIGIT4].state == STATE_LED_ON) {
				PORT5->DATAR.BIT.P53 = 1;
			// �u�����N�������ݒ肳��Ă���ꍇ
			} else if(gLedInfo[DIGIT4].state == STATE_LED_BLINK && gLedLightingEnable == LED_ENABLE) {
				PORT5->DATAR.BIT.P53 = 1;
			} else {
				PORT5->DATAR.BIT.P53 = 0;
			}
			break;
			 
		case STATE_DIGIT3_ON:
			PORT5->DATAR.BIT.P53 = 0;	// �O�̌�������
			SetSegments(DIGIT3);
			// ���̌���_��
			if(gLedInfo[DIGIT3].state == STATE_LED_ON) {
				PORT5->DATAR.BIT.P52 = 1;
			// �u�����N�������ݒ肳��Ă���ꍇ
			} else if(gLedInfo[DIGIT3].state == STATE_LED_BLINK && gLedLightingEnable == LED_ENABLE) {
				PORT5->DATAR.BIT.P52 = 1;
			} else {
				PORT5->DATAR.BIT.P52 = 0;
			}
			break;
			
		case STATE_DIGIT2_ON:
			PORT5->DATAR.BIT.P52 = 0;	// �O�̌�������
			SetSegments(DIGIT2);
			// ���̌���_��
			if(gLedInfo[DIGIT2].state == STATE_LED_ON) {
				PORT5->DATAR.BIT.P51 = 1;
			// �u�����N�������ݒ肳��Ă���ꍇ
			} else if(gLedInfo[DIGIT2].state == STATE_LED_BLINK && gLedLightingEnable == LED_ENABLE) {
				PORT5->DATAR.BIT.P51 = 1;
			} else {
				PORT5->DATAR.BIT.P51 = 0;
			}
			break;
	
		case STATE_DIGIT1_ON:
			PORT5->DATAR.BIT.P51 = 0;	// �O�̌�������
			SetSegments(DIGIT1);
			// ���̌���_��
			if(gLedInfo[DIGIT1].state == STATE_LED_ON) {
				PORT5->DATAR.BIT.P50 = 1;
			// �u�����N�������ݒ肳��Ă���ꍇ
			} else if(gLedInfo[DIGIT1].state == STATE_LED_BLINK && gLedLightingEnable == LED_ENABLE) {
				PORT5->DATAR.BIT.P50 = 1;
			} else {
				PORT5->DATAR.BIT.P50 = 0;
			}
			break;
		
		default:
			break;
	}

	if(++CurrentDigitState >= DIGIT_STATES_NUM) {
		CurrentDigitState = STATE_DIGIT6_ON;
	}
}

///////////////////////////
// 7�Z�O�����gLED�ݒ�    //
///////////////////////////
void SetSegments(_SINT digit)
{
	PORT8->DATAR.BIT.P80 = Font[gLedInfo[digit].value][0];	// segment 'a'
	PORT8->DATAR.BIT.P81 = Font[gLedInfo[digit].value][1];	// segment 'b'
	PORT8->DATAR.BIT.P82 = Font[gLedInfo[digit].value][2];	// segment 'c'
	PORT8->DATAR.BIT.P83 = Font[gLedInfo[digit].value][3];	// segment 'd'
	PORT8->DATAR.BIT.P84 = Font[gLedInfo[digit].value][4];	// segment 'e'
	PORT8->DATAR.BIT.P86 = Font[gLedInfo[digit].value][5];	// segment 'f'
	PORT8->DATAR.BIT.P87 = Font[gLedInfo[digit].value][6];	// segment 'g'
}

///////////////////////////
// 7�Z�O�����gLED������  //
///////////////////////////
void InitDigitsValues(void)
{
	gLedInfo[DIGIT6].value = 0;	gLedInfo[DIGIT6].state = STATE_LED_ON;
	gLedInfo[DIGIT5].value = 0;	gLedInfo[DIGIT5].state = STATE_LED_ON;
	gLedInfo[DIGIT4].value = 0;	gLedInfo[DIGIT4].state = STATE_LED_ON;
	gLedInfo[DIGIT3].value = 0;	gLedInfo[DIGIT3].state = STATE_LED_ON;
	gLedInfo[DIGIT2].value = 0;	gLedInfo[DIGIT2].state = STATE_LED_ON;
	gLedInfo[DIGIT1].value = 0;	gLedInfo[DIGIT1].state = STATE_LED_ON;
}

///////////////////////////
// 7�Z�O�����gLED�S����  //
///////////////////////////
void LedOff(void)
{
	PORT8->DATAR.BIT.P80 = 0;
	PORT8->DATAR.BIT.P81 = 0;
	PORT8->DATAR.BIT.P82 = 0;
	PORT8->DATAR.BIT.P83 = 0;
	PORT8->DATAR.BIT.P84 = 0;
	PORT8->DATAR.BIT.P86 = 0;
	PORT8->DATAR.BIT.P87 = 0;
	
	PORT5->DATAR.BIT.P50 = 0;
	PORT5->DATAR.BIT.P51 = 0;
	PORT5->DATAR.BIT.P52 = 0;
	PORT5->DATAR.BIT.P53 = 0;
	PORT5->DATAR.BIT.P54 = 0;
	PORT5->DATAR.BIT.P55 = 0;
}