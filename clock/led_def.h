#ifndef _LED_DEF_H_
#define _LED_DEF_H_

// �����f�W�b�g�w��
enum {
	DIGIT6,
	DIGIT5,
	DIGIT4,
	DIGIT3,
	DIGIT2,
	DIGIT1,
	DIGITS_NUM
};

// LED�X�e�[�g
enum {
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
};

// LED�u�����N����p
enum {
	LED_ENABLE,
	LED_DISABLE
};

// LED�\���������
#pragma pack 1
typedef struct {
				_UBYTE value;	// ���l���̂���
				_UBYTE code;	// ASCII�R�[�h
				struct {
						_UBYTE a  : 1;
						_UBYTE b  : 1;
						_UBYTE c  : 1;
						_UBYTE d  : 1;
						_UBYTE e  : 1;
						_UBYTE f  : 1;
						_UBYTE g  : 1;
				}	segment;	// �Z�O�����g(0:����, 1:�_��)
				_SINT state;	// �_�����
} T_LED_INFO;
#pragma unpack

#endif
