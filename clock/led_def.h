#ifndef _LED_DEF_H_
#define _LED_DEF_H_

// 処理デジット指定
enum {
	DIGIT6,
	DIGIT5,
	DIGIT4,
	DIGIT3,
	DIGIT2,
	DIGIT1,
	DIGITS_NUM
};

// LEDステート
enum {
	STATE_LED_OFF,
	STATE_LED_ON,
	STATE_LED_BLINK
};

// LEDブリンク制御用
enum {
	LED_ENABLE,
	LED_DISABLE
};

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
				_SINT state;	// 点灯状態
} T_LED_INFO;
#pragma unpack

#endif
