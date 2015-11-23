#ifndef _GLOBAL_EX_H_
#define _GLOBAL_EX_H_

#include "3694F.h"

// I/O�|�[�g //
extern T_P1   *PORT1;	// Port1�A�N�Z�X�|�C���^
extern T_P2   *PORT2;   // Port2
extern T_P5   *PORT5;	// Port5�A�N�Z�X�|�C���^
extern T_P7   *PORT7;	// Port7�A�N�Z�X�|�C���^
extern T_P8   *PORT8;	// Port8�A�N�Z�X�|�C���^
extern T_PB   *PORTB;   // PortB�A�N�Z�X�|�C���^
extern T_WDT  *TIMER;	// �E�H�b�`�h�b�O�^�C�}�[�A�N�Z�X�|�C���^
extern T_TIMA *TIMERA;	// �^�C�}�`�A�N�Z�X�|�C���^
extern T_TIMV *TIMERV;	// �^�C�}�u
extern T_INT  *INTERRUPT;	// ���荞��


extern void DispDigit(void);
extern _SINT SetTimer(_UDWORD time, void *func);
extern void BeepOn(_UDWORD time);
extern void BeepOff(void);

#endif
