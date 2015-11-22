#ifndef _LED_DEF_H_
#define _LED_DEF_H_

// 処理デジット指定
#define DIGIT6     (0)
#define DIGIT5     (1)
#define DIGIT4     (2)
#define DIGIT3     (3)
#define DIGIT2     (4)
#define DIGIT1     (5)
#define DIGITS_NUM (6)

// LEDステート
#define STATE_LED_OFF   (0)
#define STATE_LED_ON    (1)
#define STATE_LED_BLINK (2)

// LEDブリンク制御用
#define LED_ENABLE  (1)
#define LED_DISABLE (0)

// LED表示文字情報
#pragma pack 1
typedef struct {
				_UBYTE value;	// 数値そのもの
				_UBYTE code;	// ASCIIコード
				struct {
						_UBYTE a  : 1;
						_UBYTE b  : 1;
						_UBYTE c  : 1;
						_UBYTE d  : 1;
						_UBYTE e  : 1;
						_UBYTE f  : 1;
						_UBYTE g  : 1;
				}	segment;	// セグメント(0:消灯, 1:点灯)
				int state;	// 点灯状態
} T_LED_INFO;
#pragma unpack

#endif
