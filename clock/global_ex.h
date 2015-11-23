#ifndef _GLOBAL_EX_H_
#define _GLOBAL_EX_H_

#include "3694F.h"

// I/Oポート //
extern T_P1   *PORT1;	// Port1アクセスポインタ
extern T_P2   *PORT2;   // Port2
extern T_P5   *PORT5;	// Port5アクセスポインタ
extern T_P7   *PORT7;	// Port7アクセスポインタ
extern T_P8   *PORT8;	// Port8アクセスポインタ
extern T_PB   *PORTB;   // PortBアクセスポインタ
extern T_WDT  *TIMER;	// ウォッチドッグタイマーアクセスポインタ
extern T_TIMA *TIMERA;	// タイマＡアクセスポインタ
extern T_TIMV *TIMERV;	// タイマＶ
extern T_INT  *INTERRUPT;	// 割り込み


extern void DispDigit(void);
extern _SINT SetTimer(_UDWORD time, void *func);
extern void BeepOn(_UDWORD time);
extern void BeepOff(void);

#endif
