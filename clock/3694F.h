


// 3694Fのポート操作のための定義
#ifndef _3694F_H_
#define _3694F_H_

#include "typedefine.h"


//// ポート１ ////
#pragma pack 1
typedef struct {
                // プルアップコントロールレジスタ(H'FFD0～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE PUCR17 : 1;
								_UBYTE PUCR16 : 1;
								_UBYTE PUCR15 : 1;
								_UBYTE PUCR14 : 1;
								_UBYTE        : 1;
								_UBYTE PUCR12 : 1;
								_UBYTE PUCR11 : 1;
								_UBYTE PUCR10 : 1;
						}	BIT;
				}	PLUPCTRLR;
				
				// 隙間埋め草
				_UBYTE Blank101; _UBYTE Blank102; _UBYTE Blank103;
				
                // データレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE P17 : 1;
								_UBYTE P16 : 1;
								_UBYTE P15 : 1;
								_UBYTE P14 : 1;
								_UBYTE     : 1;
								_UBYTE P12 : 1;
								_UBYTE P11 : 1;
								_UBYTE P10 : 1;
						}	BIT;
				}	DATAR;
				
				// 隙間埋め草
				_UBYTE Blank201; _UBYTE Blank202; _UBYTE Blank203; _UBYTE Blank204;
				_UBYTE Blank205; _UBYTE Blank206; _UBYTE Blank207; _UBYTE Blank208;
				_UBYTE Blank209; _UBYTE Blank210; _UBYTE Blank211;
				
				// モードレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE IRQ3 : 1;
								_UBYTE IRQ2 : 1;
								_UBYTE IRQ1 : 1;
								_UBYTE IRQ0 : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
								_UBYTE TXD  : 1;
								_UBYTE TMOW : 1;
						}	BIT;
				}	MODER;

				// 隙間埋め草
				_UBYTE Blank301; _UBYTE Blank302; _UBYTE Blank303;
				
                // コントロールレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE PCR17 : 1;
								_UBYTE PCR16 : 1;
								_UBYTE PCR15 : 1;
								_UBYTE PCR14 : 1;
								_UBYTE       : 1;
								_UBYTE PCR12 : 1;
								_UBYTE PCR11 : 1;
								_UBYTE PCR10 : 1;
						}	BIT;
				}	CTRLR;
} T_P1;
#pragma unpack

//// ポート２ ////
#pragma pack 1
typedef struct {
				// データレジスタ(H'FFD5～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE     : 5;
								_UBYTE P22 : 1;
								_UBYTE P21 : 1;
								_UBYTE P20 : 1;
						}	BIT;
				}	DATAR;
				
				// 隙間埋め草
				_UBYTE Blank101; _UBYTE Blank102; _UBYTE Blank103; _UBYTE Blank104;
				_UBYTE Blank105; _UBYTE Blank106; _UBYTE Blank107; _UBYTE Blank108;
				_UBYTE Blank109; _UBYTE Blank110; _UBYTE Blank111; _UBYTE Blank112;
				_UBYTE Blank113; _UBYTE Blank114; _UBYTE Blank115;
				
                // コントロールレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE       : 5;
								_UBYTE PCR22 : 1;
								_UBYTE PCR21 : 1;
								_UBYTE PCR20 : 1;
						}	BIT;
				}	CTRLR;
} T_P2;
#pragma unpack


//// ポート５ ////
#pragma pack 1
typedef struct {
                // プルアップコントロールレジスタ(H'FFD1～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE        : 1;
								_UBYTE        : 1;
								_UBYTE PUCR55 : 1;
								_UBYTE PUCR54 : 1;
								_UBYTE PUCR53 : 1;
								_UBYTE PUCR52 : 1;
								_UBYTE PUCR51 : 1;
								_UBYTE PUCR50 : 1;
						}	BIT;
				}	PLUPCTRLR;
				
				// 隙間埋め草
				_UBYTE Blank101; _UBYTE Blank102; _UBYTE Blank103; _UBYTE Blank104;
				_UBYTE Blank105; _UBYTE Blank106;
				
                // データレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE P57 : 1;
								_UBYTE P56 : 1;
								_UBYTE P55 : 1;
								_UBYTE P54 : 1;
								_UBYTE P53 : 1;
								_UBYTE P52 : 1;
								_UBYTE P51 : 1;
								_UBYTE P50 : 1;
						}	BIT;
				}	DATAR;
				
				// 隙間埋め草
				_UBYTE Blank201; _UBYTE Blank202; _UBYTE Blank203; _UBYTE Blank204;
				_UBYTE Blank205; _UBYTE Blank206; _UBYTE Blank207; _UBYTE Blank208;
				
				// モードレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE      : 1;
								_UBYTE      : 1;
								_UBYTE WKP5 : 1;
								_UBYTE WKP4 : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
						}	BIT;
				}	MODER;

				// 隙間埋め草
				_UBYTE Blank301; _UBYTE Blank302; _UBYTE Blank303; _UBYTE Blank304;
				_UBYTE Blank305; _UBYTE Blank306;
				
                // コントロールレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE PCR57 : 1;
								_UBYTE PCR56 : 1;
								_UBYTE PCR55 : 1;
								_UBYTE PCR54 : 1;
								_UBYTE PCR53 : 1;
								_UBYTE PCR52 : 1;
								_UBYTE PCR51 : 1;
								_UBYTE PCR50 : 1;
						}	BIT;
				}	CTRLR;
} T_P5;
#pragma unpack

//// ポート７ ////
#pragma pack 1
typedef struct {
                // データレジスタ(H'FFDA～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE      : 1;
								_UBYTE P76  : 1;
								_UBYTE P75  : 1;
								_UBYTE P74  : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
								_UBYTE      : 1;
						}	BIT;
				}	DATAR;
				
				// 隙間埋め草
				_UBYTE Blank101; _UBYTE Blank102; _UBYTE Blank103; _UBYTE Blank104;
				_UBYTE Blank105; _UBYTE Blank106; _UBYTE Blank107; _UBYTE Blank108;
				_UBYTE Blank109; _UBYTE Blank110; _UBYTE Blank111; _UBYTE Blank112;
				_UBYTE Blank113; _UBYTE Blank114; _UBYTE Blank115;
				
                // コントロールレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE       : 1;
								_UBYTE PCR76 : 1;
								_UBYTE PCR75 : 1;
								_UBYTE PCR74 : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
						}	BIT;
				}	CTRLR;
} T_P7;
#pragma unpack

//// ポート８ ////
#pragma pack 1
typedef struct {
                // データレジスタ(H'FFDB～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE P87 : 1;
								_UBYTE P86 : 1;
								_UBYTE P85 : 1;
								_UBYTE P84 : 1;
								_UBYTE P83 : 1;
								_UBYTE P82 : 1;
								_UBYTE P81 : 1;
								_UBYTE P80 : 1;
						}	BIT;
				}	DATAR;
				
				// 隙間埋め草
				_UBYTE Blank101; _UBYTE Blank102; _UBYTE Blank103; _UBYTE Blank104;
				_UBYTE Blank105; _UBYTE Blank106; _UBYTE Blank107; _UBYTE Blank108;
				_UBYTE Blank109; _UBYTE Blank110; _UBYTE Blank111; _UBYTE Blank112;
				_UBYTE Blank113; _UBYTE Blank114; _UBYTE Blank115;
				
                // コントロールレジスタ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE PCR87 : 1;
								_UBYTE PCR86 : 1;
								_UBYTE PCR85 : 1;
								_UBYTE PCR84 : 1;
								_UBYTE PCR83 : 1;
								_UBYTE PCR82 : 1;
								_UBYTE PCR81 : 1;
								_UBYTE PCR80 : 1;
						}	BIT;
				}	CTRLR;
} T_P8;
#pragma unpack

//// ポートＢ ////
#pragma pack 1
typedef struct {
                // データレジスタ(H'FFDD～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE PB7 : 1;
								_UBYTE PB6 : 1;
								_UBYTE PB5 : 1;
								_UBYTE PB4 : 1;
								_UBYTE PB3 : 1;
								_UBYTE PB2 : 1;
								_UBYTE PB1 : 1;
								_UBYTE PB0 : 1;
						}	BIT;
				}	DATAR;
} T_PB;
#pragma unpack


//// ウォッチドッグタイマー ////
#pragma pack 1
typedef struct {
                // タイマーコントロール・ステータスレジスタＷＤ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE BIT7 : 1;
								_UBYTE BIT6 : 1;
								_UBYTE BIT5 : 1;
								_UBYTE BIT4 : 1;
								_UBYTE BIT3 : 1;
								_UBYTE BIT2 : 1;
								_UBYTE BIT1 : 1;
								_UBYTE BIT0 : 1;
						}	BIT;
				}	TCSRWD;

                // タイマーカウンタＷＤ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE BIT7 : 1;
								_UBYTE BIT6 : 1;
								_UBYTE BIT5 : 1;
								_UBYTE BIT4 : 1;
								_UBYTE BIT3 : 1;
								_UBYTE BIT2 : 1;
								_UBYTE BIT1 : 1;
								_UBYTE BIT0 : 1;
						}	BIT;
				}	TCWD;

                // タイマーモードレジスタＷＤ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE BIT7 : 1;
								_UBYTE BIT6 : 1;
								_UBYTE BIT5 : 1;
								_UBYTE BIT4 : 1;
								_UBYTE BIT3 : 1;
								_UBYTE BIT2 : 1;
								_UBYTE BIT1 : 1;
								_UBYTE BIT0 : 1;
						}	BIT;
				}	TWWD;

                _UBYTE WDT;
} T_WDT;
#pragma unpack

//// タイマＡ(時計用タイムベース) ////
#pragma pack 1
typedef struct {
                // タイマーモードレジスタＡ(H'FFA6～)
				union {
						_UBYTE BYTE;
						union {
								struct {
										_UBYTE OUTPUT_SELECT          : 3;
										_UBYTE                        : 1;
										_UBYTE INTERNAL_CLOCK_SELECT3 : 1;
										_UBYTE OVERFLOW_PERIOD        : 3;
										#define INTERNAL_CLOCK_SELECT0_2 OVERFLOW_PERIOD
								} CLUSTER;
										
								struct {
										_UBYTE TMA7 : 1;
										_UBYTE TMA6 : 1;
										_UBYTE TMA5 : 1;
										_UBYTE      : 1;
										_UBYTE TMA3 : 1;
										_UBYTE TMA2 : 1;
										_UBYTE TMA1 : 1;
										_UBYTE TMA0 : 1;
								}	BIT;
						} STYLE;
				}	TMA;

                // タイマーカウンタＡ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE TCA7 : 1;
								_UBYTE TCA6 : 1;
								_UBYTE TCA5 : 1;
								_UBYTE TCA4 : 1;
								_UBYTE TCA3 : 1;
								_UBYTE TCA2 : 1;
								_UBYTE TCA1 : 1;
								_UBYTE TCA0 : 1;
						}	BIT;
				}	TCA;
} T_TIMA;
#pragma unpack

//// タイマＶ ////
#pragma pack 1
typedef struct {
				// タイマコントロールレジスタV0(H'FFA0～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE CMIEB : 1;
								_UBYTE CMIEA : 1;
								_UBYTE OVIE  : 1;
								_UBYTE CCLR  : 2;
								_UBYTE CKS   : 3;
						}	BIT;
				}	TCRV0;
				
				// タイマコントロール/ステータスレジスタＶ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE CMFB : 1;
								_UBYTE CMFA : 1;
								_UBYTE OVF  : 1;
								_UBYTE      : 1;
								_UBYTE OS3  : 1;
								_UBYTE OS2  : 1;
								_UBYTE OS1  : 1;
								_UBYTE OS0  : 1;
						}	BIT;
				}	TCSRV;
				
				// タイムコンスタントレジスタＡ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE TCORA7 : 1;
								_UBYTE TCORA6 : 1;
								_UBYTE TCORA5 : 1;
								_UBYTE TCORA4 : 1;
								_UBYTE TCORA3 : 1;
								_UBYTE TCORA2 : 1;
								_UBYTE TCORA1 : 1;
								_UBYTE TCORA0 : 1;
						}	BIT;
				}	TCORA;
				
				// タイムコンスタントレジスタＢ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE TCORB7 : 1;
								_UBYTE TCORB6 : 1;
								_UBYTE TCORB5 : 1;
								_UBYTE TCORB4 : 1;
								_UBYTE TCORB3 : 1;
								_UBYTE TCORB2 : 1;
								_UBYTE TCORB1 : 1;
								_UBYTE TCORB0 : 1;
						}	BIT;
				}	TCORB;
				
				// タイマカウンタＶ
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE TCNTV7 : 1;
								_UBYTE TCNTV6 : 1;
								_UBYTE TCNTV5 : 1;
								_UBYTE TCNTV4 : 1;
								_UBYTE TCNTV3 : 1;
								_UBYTE TCNTV2 : 1;
								_UBYTE TCNTV1 : 1;
								_UBYTE TCNTV0 : 1;
						}	BIT;
				}	TCNTV;
				
				// タイムコントロールレジスタV1
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE TVEG1 : 1;
								_UBYTE TVEG0 : 1;
								_UBYTE TRGE  : 1;
								_UBYTE       : 1;
								_UBYTE ICKS0 : 1;
						}	BIT;
				}	TCRV1;
				
				// タイマモードレジスタＡ(たぶん間違ってる)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE TMA7 : 1;
								_UBYTE TMA6 : 1;
								_UBYTE TMA5 : 1;
								_UBYTE      : 1;
								_UBYTE TMA3 : 1;
								_UBYTE TMA2 : 1;
								_UBYTE TMA1 : 1;
								_UBYTE TMA0 : 1;
						}	BIT;
				}	TMA;
				
				// タイマカウンタＡ(たぶん間違ってる)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE TCA7 : 1;
								_UBYTE TCA6 : 1;
								_UBYTE TCA5 : 1;
								_UBYTE TCA4 : 1;
								_UBYTE TCA3 : 1;
								_UBYTE TCA2 : 1;
								_UBYTE TCA1 : 1;
								_UBYTE TCA0 : 1;
						}	BIT;
				}	TCA;
} T_TIMV;
#pragma unpack

//// 割り込み ////
#pragma pack 1
typedef struct {
				// 割り込みエッジセレクトレジスタ１(H'FFF2～)
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE NMIEG : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE IEG3  : 1;
								_UBYTE IEG2  : 1;
								_UBYTE IEG1  : 1;
								_UBYTE IEG0  : 1;
						}	BIT;
				}	IEGR1;
				
				// 割り込みエッジセレクトレジスタ２
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE WPEG5 : 1;
								_UBYTE WPEG4 : 1;
								_UBYTE WPEG3 : 1;
								_UBYTE WPEG2 : 1;
								_UBYTE WPEG1 : 1;
								_UBYTE WPEG0 : 1;
						}	BIT;
				}	IEGR2;
				
				// 割り込みイネーブルレジスタ１
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE IENDT : 1;
								_UBYTE IENTA : 1;
								_UBYTE IENWP : 1;
								_UBYTE       : 1;
								_UBYTE IEN3  : 1;
								_UBYTE IEN2  : 1;
								_UBYTE IEN1  : 1;
								_UBYTE IEN0  : 1;
						}	BIT;
				}	IENR1;
				
				// 隙間埋め草
				_UBYTE Blank101;

				// 割り込みフラグレジスタ１
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE IRRDT : 1;
								_UBYTE IRRTA : 1;
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE IRRI3 : 1;
								_UBYTE IRRI2 : 1;
								_UBYTE IRRI1 : 1;
								_UBYTE IRRI0 : 1;
						}	BIT;
				}	IRR1;
				
				// 隙間埋め草
				_UBYTE Blank201;

				// ウェイクアップ割り込みフラグレジスタ１
				union {
						_UBYTE BYTE;
						struct {
								_UBYTE       : 1;
								_UBYTE       : 1;
								_UBYTE IWPF5 : 1;
								_UBYTE IWPF4 : 1;
								_UBYTE IWPF3 : 1;
								_UBYTE IWPF2 : 1;
								_UBYTE IWPF1 : 1;
								_UBYTE IWPF0 : 1;
						}	BIT;
				}	IWPR;
} T_INT;
#pragma unpack


#endif
