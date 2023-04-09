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


typedef enum
{
		 LCD_STB_Shift  =1,
		 LCD_STB_Alpha  =5,
		 LCD_STB_M      =9,
		 LCD_STB_STO    =14,
		 LCD_STB_RCL    =19,
		 LCD_STB_STAT   =27,
		 LCD_STB_CMPLX  =35,
		 LCD_STB_MAT    =44,
		 LCD_STB_VCT    =49,
		 LCD_STB_D      =55,
		 LCD_STB_R      =59,
		 LCD_STB_FIX    =67,
		 LCD_STB_SCI    =72,
		 LCD_STB_Math   =78,
		 LCD_STB_Down   =84,
		 LCD_STB_Up     =86,
		 LCD_STB_Disp   =92,
	
}lcd_statusbar_e;

void LCD_Send_Data(u8 data);
void LCD_Send_Cmd(u8 cmd);
void LCD_Clear(int clear_data);
void LCD_Init(void);
void LCD_Set_Add(int page, int col);
void LCD_GRAM_Update(void);


void LCD_DrawPoint(u8 x,u8 y,u8 b);
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void LCD_Fill(u8 x0,u8 y0,u8 x1,u8 y1,u8 b);
void LCD_ClearGRAM(u8 b);
void LCD_DispBmp(u8 x0,u8 y0,u8 w,u8 h,u8 *pic);


void LCD_SetContrast(uint8_t percent);
void LCD_PowerSave(void);
void LCD_StatusBarSet(lcd_statusbar_e id,u8 b);
void LCD_StatusBarClear(void);

void LCD_ShowChar8x16(u16 left,u16 top,u8 chr,u16 b);
void LCD_ShowChar6x12(u16 left,u16 top,u8 chr,u16 b);
void LCD_ShowNum(u16 x, u16 y, s32 num,u8 sizey, u8 len,u16 b);
void LCD_ShowStr(u16 left,u16 top,u8 sizey,u8 *s,u16 b);

u32 mypow(u8 m,u8 n);

#endif