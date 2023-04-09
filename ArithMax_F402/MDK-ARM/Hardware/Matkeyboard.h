#ifndef _MATKEYBOARD_H_
#define _MATKEYBOARD_H_

#include <main.h>

extern volatile uint8_t Key_updateFlag;
extern volatile uint8_t KeyVal;

/* CH451和CH452的常用命令码 */
#define CH452_NOP		    0x0000					// 空操作
#define CH452_RESET     0x0201					// 复位
#define CH452_LEVEL		  0x0100					// 加载光柱值,需另加7位数据
#define CH452_CLR_BIT	  0x0180					// 段位清0,需另加6位数据
#define CH452_SET_BIT	  0x01C0					// 段位置1,需另加6位数据
#define CH452_SLEEP		  0x0202					// 进入睡眠状态
#define CH452_LEFTMOV   0x0300		            // 设置移动方式-左移
#define CH452_LEFTCYC   0x0301		            // 设置移动方式-左循环
#define CH452_RIGHTMOV  0x0302		            // 设置移动方式-右移
#define CH452_RIGHTCYC  0x0303		            // 设置移动方式-右循环	
#define CH452_SELF_BCD	0x0380					// 自定义BCD码,需另加7位数据
#define CH452_SYSOFF    0x0400					// 关闭显示、关闭键盘
#define CH452_SYSON1    0x0401					// 开启显示
#define CH452_SYSON2    0x0403					// 开启显示、键盘
#define CH452_SYSON2W   0x0423					// 开启显示、键盘, 真正2线接口
#define CH452_NO_BCD    0x0500					// 设置默认显示方式,可另加3位扫描极限
#define CH452_BCD       0x0580					// 设置BCD译码方式,可另加3位扫描极限
#define CH452_TWINKLE   0x0600		            // 设置闪烁控制,需另加8位数据
#define CH452_GET_KEY	  0x0700					// 获取按键,返回按键代码
#define CH452_DIG0      0x0800					// 数码管位0显示,需另加8位数据
#define CH452_DIG1      0x0900		            // 数码管位1显示,需另加8位数据
#define CH452_DIG2      0x0a00		            // 数码管位2显示,需另加8位数据
#define CH452_DIG3      0x0b00		            // 数码管位3显示,需另加8位数据
#define CH452_DIG4      0x0c00		            // 数码管位4显示,需另加8位数据
#define CH452_DIG5      0x0d00					// 数码管位5显示,需另加8位数据
#define CH452_DIG6      0x0e00					// 数码管位6显示,需另加8位数据
#define CH452_DIG7      0x0f00		            // 数码管位7显示,需另加8位数据

// BCD译码方式下的特殊字符
#define		CH452_BCD_SPACE		0x10
#define		CH452_BCD_PLUS		0x11
#define		CH452_BCD_MINUS		0x12
#define		CH452_BCD_EQU			0x13
#define		CH452_BCD_LEFT		0x14
#define		CH452_BCD_RIGHT		0x15
#define		CH452_BCD_UNDER		0x16
#define		CH452_BCD_CH_H		0x17
#define		CH452_BCD_CH_L		0x18
#define		CH452_BCD_CH_P		0x19
#define		CH452_BCD_DOT			0x1A
#define		CH452_BCD_SELF		0x1E
#define		CH452_BCD_TEST		0x88
#define		CH452_BCD_DOT_X		0x80

// 有效按键代码
#define		CH452_KEY_MIN		0x40
#define		CH452_KEY_MAX		0x7F

// 2线接口的CH452定义
#define		CH452_I2C_ADDR0		0x40			// CH452的ADDR=0时的地址
#define		CH452_I2C_ADDR1		0x60			// CH452的ADDR=1时的地址,默认值
#define		CH452_I2C_MASK		0x3E			// CH452的2线接口高字节命令掩码

//按键对应值查找表，数值为读取到的按键值
#define KEY_NULL  0xFF
#define KEY_EQUAL 0x00
#define KEY_MINUS 0x01
#define KEY_DIVID 0x02
#define KEY_AC	  0x03
#define KEY_MPLUS 0x04
#define KEY_TANGE 0x05
#define KEY_LN    0x06
#define KEY_LOGAB 0x2E
#define KEY_X_N1  0x36
#define KEY_SETUP	0x2D
#define KEY_RIGHT 0x2C
#define KEY_DOWN  0x35
#define KEY_LEFT  0x2A
#define KEY_ALPHA 0x29
#define KEY_X_P3  0x34
#define KEY_SHIFT	0x28
#define KEY_ABS   0x33
#define KEY_LOG   0x0E
#define KEY_X_PN  0x16
#define KEY_X_P2  0x1E
#define KEY_RADIC 0x26
#define KEY_FRA_B	0x32//分数线
#define KEY_HYP   0x1D
#define KEY_COSIN 0x0D
#define KEY_SINE  0x15
#define KEY_DEGRE 0x25
#define KEY_NEG   0x31
#define KEY_S2D   0x0C
#define KEY_RPARE 0x14//右括号
#define KEY_LPARE 0x1C//左括号
#define KEY_ENG	  0x24
#define KEY_RCL   0x30
#define KEY_DEL   0x0B
#define KEY_MUL   0x0A
#define KEY_PLUS  0x09
#define KEY_ANS   0x08
#define KEY_M10_X 0x10
#define KEY_DOT   0x18
#define KEY_0     0x20
#define KEY_1 		0x21
#define KEY_2	 	  0x19
#define KEY_3 		0x11
#define KEY_4 		0x22
#define KEY_5     0x1A
#define KEY_6 		0x12
#define KEY_7   	0x23
#define KEY_8	    0x1B
#define KEY_9			0x13

#define SCL_SET HAL_GPIO_WritePin(MK_SCL_GPIO_Port, MK_SCL_Pin, GPIO_PIN_SET)
#define SCL_RST HAL_GPIO_WritePin(MK_SCL_GPIO_Port, MK_SCL_Pin, GPIO_PIN_RESET)
#define SDA_SET HAL_GPIO_WritePin(MK_SDA_GPIO_Port, MK_SDA_Pin, GPIO_PIN_SET)
#define SDA_RST HAL_GPIO_WritePin(MK_SDA_GPIO_Port, MK_SDA_Pin, GPIO_PIN_RESET)

void MK_Init(void);
void MK_IIC_Write(uint16_t data);
uint8_t MK_IIC_Read(void);
void CH452Init(void);




#endif