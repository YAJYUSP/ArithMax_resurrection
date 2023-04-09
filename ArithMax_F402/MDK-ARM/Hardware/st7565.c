#include <main.h>
#include "st7565.h"
#include "font.h"


uint8_t LCD_GRAM[96*4] ={0xFF};//GraphicRAM of the lcd





void LCD_Init(void)
{
		LCD_RST(0);
		HAL_Delay(2);
		LCD_RST(1);
		LCD_CS(0);//

		LCD_Send_Cmd(0xe2);//system reset
		HAL_Delay(20);   
		LCD_Send_Cmd(0xae);        
		LCD_Send_Cmd(0xf8);   
		LCD_Send_Cmd(0x00);
		LCD_Send_Cmd(0xa2);
		LCD_Send_Cmd(0xa0);
		LCD_Send_Cmd(0xc0);
		LCD_Send_Cmd(0xa6);
		LCD_Send_Cmd(0xa4);
		LCD_Send_Cmd(0xe0);
		LCD_Send_Cmd(0xac);
		LCD_Send_Cmd(0x00);
		LCD_Send_Cmd(0x21);
		LCD_Send_Cmd(0x81);
		LCD_Send_Cmd(0x1e);        
		LCD_Send_Cmd(0x2f);   
		LCD_Send_Cmd(0x40);
		LCD_Send_Cmd(0xaf);
		LCD_Send_Cmd(0xb0);
		LCD_Send_Cmd(0x12);
		LCD_Send_Cmd(0x04);
		LCD_Send_Cmd(0xe0);
		LCD_Send_Cmd(0xe0);
		HAL_Delay(5);
		LCD_StatusBarClear();
		LCD_ClearGRAM(0);
		LCD_GRAM_Update();

}

void LCD_GRAM_Update(void)
{
		unsigned char i,j,rx;
		for (i=0;i<4;i++)
		{
				LCD_Send_Cmd(0xee);
				LCD_Send_Cmd(0xb0|(3-i));
				LCD_Send_Cmd(0x12);
				LCD_Send_Cmd(0x04);
				LCD_Send_Cmd(0xe0); 
				for (j=0;j<96;j++)
						LCD_Send_Data(LCD_GRAM[i*96+j]);
		}
}


void LCD_SetContrast(uint8_t percent)
{
		LCD_Send_Cmd(0x81);
		LCD_Send_Cmd(percent);
}

void LCD_PowerSave(void)
{
		LCD_Send_Cmd(0xae);
		LCD_Send_Cmd(0x28);
		LCD_Send_Cmd(0xa5);
}

void LCD_StatusBarSet(lcd_statusbar_e id,u8 b)
{
		u8 rid = id+36;
		LCD_Send_Cmd(0xee);
		LCD_Send_Cmd(0xb8);
		LCD_Send_Cmd(0x10|(rid>>4));
		LCD_Send_Cmd(0x00|(rid&0x0f));
		LCD_Send_Cmd(0xe0);
		LCD_Send_Data(b);
}

void LCD_StatusBarClear(void)
{
		LCD_StatusBarSet(LCD_STB_Shift,0);
		LCD_StatusBarSet(LCD_STB_Alpha,0);
		LCD_StatusBarSet(LCD_STB_M,0);
		LCD_StatusBarSet(LCD_STB_STO,0);
		LCD_StatusBarSet(LCD_STB_RCL,0);
		LCD_StatusBarSet(LCD_STB_STAT,0);
		LCD_StatusBarSet(LCD_STB_CMPLX,0);
		LCD_StatusBarSet(LCD_STB_MAT,0);
		LCD_StatusBarSet(LCD_STB_VCT,0);
		LCD_StatusBarSet(LCD_STB_D,0);
		LCD_StatusBarSet(LCD_STB_R,0);
		LCD_StatusBarSet(LCD_STB_FIX,0);
		LCD_StatusBarSet(LCD_STB_SCI,0);
		LCD_StatusBarSet(LCD_STB_Math,0);
		LCD_StatusBarSet(LCD_STB_Down,0);
		LCD_StatusBarSet(LCD_STB_Up,0);
		LCD_StatusBarSet(LCD_STB_Disp,0);
}
	

void LCD_ShowChar8x16(u16 left,u16 top,u8 chr,u16 b)
{
		u16 x,y;
		u16 ptr;	
		ptr=(chr-0x20)*16;//整体下移1个像素
		for (y=0;y<16;y++)
		{
				for (x=0;x<8;x++)
				{
						if (((Font_Ascii_8X16E[ptr]>>x)&0x01)==0x01)
						LCD_DrawPoint(left+x,top+y,b); 
				}
				ptr++;
		}
}

void LCD_ShowChar6x12(u16 left,u16 top,u8 chr,u16 b)
{
		u16 x,y;
		u16 ptr;	
		ptr=(chr-0x20)*12;//整体下移1个像素
		for (y=0;y<12;y++)
		{ 
				for (x=0;x<6;x++)
				{
						if (((Font_Ascii_6X12E[ptr]>>x)&0x01)==0x01)
								LCD_DrawPoint(left+x,top+y,b); 
						else
								LCD_DrawPoint(left+x,top+y,!b); 
				}
				ptr++;
		}
}

void LCD_ShowNum(u16 x, u16 y, s32 num,u8 sizey, u8 len,u16 b)
{           
		u8 t,temp;
		u8 enshow=0;
		t=0;
		if(num<0)
		{
			  if(sizey == 16)
						LCD_ShowChar8x16(x+8*t,y,'-',b);
				else if(sizey == 12)
						LCD_ShowChar6x12(x+6*t,y,'-',b);
				num=-num;
				t++;
		}               
		for(;t<len;t++)
		{
				temp=(num/mypow(10,len-t-1))%10;
				if(enshow==0&&t<(len-1))
				{
						if(temp==0)
						{
								if(sizey == 16)
										LCD_ShowChar8x16(x+8*t,y,' ',b);
								else if(sizey == 12)
										LCD_ShowChar6x12(x+6*t,y,' ',b);
								continue;
						}else enshow=1;         
				}
				if(sizey == 16)
						LCD_ShowChar8x16(x+8*t,y,temp+'0',b); 
				else if(sizey == 12)
						LCD_ShowChar6x12(x+6*t,y,temp+'0',b); 
		}
} 

void LCD_ShowStr(u16 left,u16 top,u8 sizey,u8 *s,u16 b)
{
		u16 x = 0; 
		while(*s)
		{
				if (*s<128)
				{
						if(sizey == 16)
						{
								LCD_ShowChar8x16(left+x,top,*s++,b);
						    x+=8;
						}
						else if(sizey == 12)
						{
								LCD_ShowChar6x12(left+x,top,*s++,b);
								x+=6;
						}
						
				}
				else
				{
						s+=2;
						x+=16;
				}
		}
}




void LCD_DispBmp(u8 x0,u8 y0,u8 w,u8 h,u8 *pic)
{
		u8 i,j,z,c;
		for(i=y0;i<=y0+h;i++)
		{
				for(j=x0;j<=x0+w;j+=8)
				{
						c=(*pic++);
						for (z=0;z<8;z++)
								if ((c<<z)&0x80)
										LCD_DrawPoint(j+z,i,1);
								else
										LCD_DrawPoint(j+z,i,0);
				}
		}
}

void LCD_DrawPoint(u8 x,u8 y,u8 b)
{
		u16 y_bit,y_byte;               
		if ((x<96)&&(y<32))
		{
				y_byte=y/8;
				y_bit=y%8;             
			
				if(b)
						LCD_GRAM[(y_byte)*96+x]|=(0x80>>y_bit); 
				else
						LCD_GRAM[(y_byte)*96+x]&=~(0x80>>y_bit);
		}
}


/******************************************************************************
  * @brief  Draw a line in the GRAM
	* @param  x(y): the x(y)-coordinate of start/end pixel , in a range of [0,127]
  * @retval None
******************************************************************************/
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
		uint16_t t;
		int xerr = 0, yerr = 0, delta_x, delta_y, distance;
		int incx, incy, uRow, uCol;
		delta_x = x2 - x1; //计算坐标增量
		delta_y = y2 - y1;
		uRow = x1;
		uCol = y1;
		if (delta_x > 0)
			incx = 1; //设置单步方向
		else if (delta_x == 0)
			incx = 0; //垂直线
		else
		{
			incx = -1;
			delta_x = -delta_x;
		}
		if (delta_y > 0)
			incy = 1;
		else if (delta_y == 0)
			incy = 0; //水平线
		else
		{
			incy = -1;
			delta_y = -delta_y;
		}
		if (delta_x > delta_y)
			distance = delta_x; //选取基本增量坐标轴
		else
			distance = delta_y;
		for (t = 0; t <= distance + 1; t++) //画线输出
		{
			LCD_DrawPoint(uRow, uCol, color); //画点
			xerr += delta_x;
			yerr += delta_y;
			if (xerr > distance)
			{
				xerr -= distance;
				uRow += incx;
			}
			if (yerr > distance)
			{
				yerr -= distance;
				uCol += incy;
			}
		}
}

void LCD_Fill(u8 x0,u8 y0,u8 x1,u8 y1,u8 b)
{
		u16 i,j;
		for(i=y0;i<=y1;i++)
		{
				for(j=x0;j<=x1;j++)
				{
						LCD_DrawPoint(j,i,b);
				}
		}
}

void LCD_ClearGRAM(u8 b)
{
		u16 i;
		for(i=0;i<384;i++)
		{
				LCD_GRAM[i]=b;
		}
}

/*******************************************************************************************/


static void LCD_Set_Add(int page, int col)
{
		LCD_Send_Cmd(0XB0 + page);
		LCD_Send_Cmd(0X10 + ((col & 0XF0) >> 4));//column HAdd
		LCD_Send_Cmd(0X00+ (col & 0X0F));				 //column LAdd
}

static u32 mypow(u8 m,u8 n)
{
		uint32_t result=1;	 
		while(n--)result*=m;    
		return result;
}

static void LCD_Send_Data(u8 data)
{	
		LCD_A0(1);
		LCD_RD(1);
		LCD_WR(0);
		delay_us(5);
		
		GPIOB->ODR=((GPIOB->ODR & 0xFF00)+data);//PB0-7 is data bits，PB15-8 maintains
		LCD_WR(1);
		delay_us(5);
}

static void LCD_Send_Cmd(u8 cmd)
{
		LCD_A0(0);
		LCD_RD(1);
		LCD_WR(0);
		delay_us(5);
		
		GPIOB->ODR=((GPIOB->ODR & 0xFF00)+cmd);//PB0-7 is data bits，PB15-8 maintains
		LCD_WR(1);
		delay_us(5);
}


