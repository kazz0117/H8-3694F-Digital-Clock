#ifndef _LED_DEF_H_
#define _LED_DEF_H_

// �����f�W�b�g�w��
#define DIGIT6     (0)
#define DIGIT5     (1)
#define DIGIT4     (2)
#define DIGIT3     (3)
#define DIGIT2     (4)
#define DIGIT1     (5)
#define DIGITS_NUM (6)

// LED�X�e�[�g
#define STATE_LED_OFF   (0)
#define STATE_LED_ON    (1)
#define STATE_LED_BLINK (2)

// LED�u�����N����p
#define LED_ENABLE  (1)
#define LED_DISABLE (0)

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
				int state;	// �_�����
} T_LED_INFO;
#pragma unpack

#endif
