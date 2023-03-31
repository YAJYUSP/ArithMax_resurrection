#ifndef _ST7565_H_
#define _ST7565_H_

#include <stdint.h>
#include <main.h>
#define u8 uint8_t
#define u16 uint16_t
#define s32 int32_t
#define u32 uint32_t

#define LCD_RST(x) HAL_GPIO_WritePin(LCD_RST_GPIO_Port,LCD_RST_Pin,x)
#define LCD_CS(x) HAL_GPIO_WritePin(LCD_CS_GPIO_Port,LCD_CS_Pin,x)
#define LCD_RD(x) HAL_GPIO_WritePin(LCD_RD_GPIO_Port,LCD_RD_Pin,x)
#define LCD_WR(x) HAL_GPIO_WritePin(LCD_WR_GPIO_Port,LCD_WR_Pin,x)
#define LCD_A0(x) HAL_GPIO_WritePin(LCD_A0_GPIO_Port,LCD_A0_Pin,x)

#define LCD_STB_Shift   1
#define LCD_STB_Alpha   5
#define LCD_STB_M       9
#define LCD_STB_STO     14
#define LCD_STB_RCL     19
#define LCD_STB_STAT    27
#define LCD_STB_CMPLX   35
#define LCD_STB_MAT     44
#define LCD_STB_VCT     49
#define LCD_STB_D       55
#define LCD_STB_R       59
#define LCD_STB_G       62
#define LCD_STB_FIX     67
#define LCD_STB_SCI     72
#define LCD_STB_Math    78
#define LCD_STB_Down    84
#define LCD_STB_Up      86
#define LCD_STB_Disp    92

void LCD_Send_Data(u8 data);
void LCD_Send_Cmd(u8 cmd);
void LCD_Clear(int clear_data);
void LCD_Init(void);
void LCD_Set_Add(int page, int col);
void LCD_Update(void);

void LCD_DrawPoint(u8 x,u8 y,u8 b);
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void LCD_Fill(u8 x0,u8 y0,u8 x1,u8 y1,u8 b);
void LCD_ClearGRAM(u8 b);
void LCD_DispBmp(u8 x0,u8 y0,u8 w,u8 h,u8 *pic);


void LCD_SetContrast(uint8_t percent);
void LCD_PowerSave(void);
void LCD_StatusBarSet(u8 id,u8 b);

void LCD_ShowChar8x16(u16 left,u16 top,u8 chr,u16 b);
void LCD_ShowChar6x12(u16 left,u16 top,u8 chr,u16 b);
void LCD_ShowNum(u16 x, u16 y, s32 num,u8 sizey, u8 len,u16 b);
void LCD_ShowStr(u16 left,u16 top,u8 sizey,u8 *s,u16 b);

u32 mypow(u8 m,u8 n);

#endif