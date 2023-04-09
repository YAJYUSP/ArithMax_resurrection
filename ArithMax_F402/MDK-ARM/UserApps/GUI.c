#include <main.h>
#include <string.h>
#include <stdlib.h>
#include "dynamic_string.h"
#include "matkeyboard.h"
#include "arithmatic.h"
#include "gui.h"
#include "st7565.h"

//GUI line0 string memory zone, max size LINE0_LEN_MAX
char *line0_memory = "";
//GUI line0 string displaying memory zone, 16 chars max could to be displayed
char line0_disp[17] = "";


//GUI cursor param struct
gui_cursor_t line0_cursor;


/*****************************************************************************
* @brief  initialing the gui display
* @param  none
* @retval none
******************************************************************************/
void gui_init(void)
{
		line0_cursor.cursor_displaying_flag = 1;
	  line0_cursor.memoryCursor_pos = 0;
		line0_cursor.dispCursor_pos = 0;
		line0_cursor.intercept_pos = 0;
	
		gui_displayStr_malloc();

}

/*****************************************************************************
* @brief  update the displayed cursor status on screen in tim10 every 500ms
* @param  none
* @retval none
******************************************************************************/
void gui_updtCursor_tim10_500ms(void)
{
		static uint8_t Cnt_LED = 0;
	  static uint8_t Cnt_Cursor = 0;
	
		if(line0_cursor.cursor_displaying_flag)
		{
				Cnt_Cursor++;
				if(Cnt_Cursor==50)
				{
						gui_updtCursor(1,line0_cursor.dispCursor_pos);
						LCD_GRAM_Update();
				}
				else if(Cnt_Cursor==100)
				{
						Cnt_Cursor=0;
						gui_updtCursor(0,line0_cursor.dispCursor_pos);
						LCD_GRAM_Update();
				}
		}
		else
		{
				Cnt_Cursor=0;
		}
}


/*****************************************************************************
* @brief  clear gui displaying info while pressing AC
* @param  none
* @retval none
******************************************************************************/
void gui_disp_all_clear(void)
{
		free(line0_memory);
		memset(line0_disp,0,17);
		gui_init();
		gui_line0_displayUpdt();
}


/******************************************************************************
* @brief  Update content of Line0 buffer according to key pressed
* @param  key_val: the key pressed
					key_update:key_val updating flag
* @retval none
******************************************************************************/
void gui_line0Updt_from_keypad(uint8_t key_val, uint8_t* key_update)
{
		if(*key_update)
		{
				*key_update=0;
				switch(key_val)
				{
						case KEY_0:
								dynamicStr_strcat("0",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_1:
								dynamicStr_strcat("1",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_2:
								dynamicStr_strcat("2",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_3:
								dynamicStr_strcat("3",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_4:
								dynamicStr_strcat("4",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_5:
								dynamicStr_strcat("5",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_6:
								dynamicStr_strcat("6",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_7:
								dynamicStr_strcat("7",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_8:
							  dynamicStr_strcat("8",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_9:
								dynamicStr_strcat("9",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
						case KEY_DOT:
								dynamicStr_strcat(".",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
						case KEY_PLUS:
								dynamicStr_strcat("+",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_MINUS:
								dynamicStr_strcat("-",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
					  case KEY_MUL:
								dynamicStr_strcat("*",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
						case KEY_DIVID:
								dynamicStr_strcat("/",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
						case KEY_LPARE:
								dynamicStr_strcat("(",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
						case KEY_RPARE:
								dynamicStr_strcat(")",&line0_memory,line0_cursor.memoryCursor_pos, LINE0_LEN_MAX);
								line0Cursor_scroll(1,0);
								
								break;
						case KEY_DEL:
								if(!dynamicStr_backspace(line0_cursor.memoryCursor_pos, &line0_memory))
								{
										line0Cursor_scroll(0,0);
										
								}
								break;
						case KEY_AC:
								gui_disp_all_clear();
								break;
								
						case KEY_LEFT:
								line0Cursor_scroll(0,1);
								
								break;
						case KEY_RIGHT:	
								line0Cursor_scroll(1,1);
							
								break;
						case KEY_EQUAL:
								//input2RPN_conv();
								break;
				}
		}
}




















/*****************************************************************************
* @brief  update the displayed cursor status on screen
* @param  en: cursor enable switch
					pos: x_coor of cursor to display
* @retval none
******************************************************************************/
static void gui_updtCursor(uint8_t en, uint8_t pos)
{
		static uint8_t last_pos = 0;

		if(pos==0)
		{
				LCD_DrawLine(0,1,0,10,en);
		}
	
		if(last_pos != pos)
		{
				if(last_pos==0)
						LCD_DrawLine(0,1,0,10,0);
				else
						LCD_DrawLine(6*last_pos-1,1,6*last_pos-1,10,0);
		}
		last_pos = pos;
		LCD_DrawLine(6*pos-1,1,6*pos-1,10,en);	
}


/******************************************************************************
* @brief  malloc GUI line string memory while initing
* @param  none
* @retval none
******************************************************************************/
static void gui_displayStr_malloc(void)
{
		line0_memory = (char *)malloc(0);

}


/*****************************************************************************
* @brief  update displayed line0 string content 
* @param  none
* @retval none
******************************************************************************/
static void gui_line0_displayUpdt(void)
{
		LCD_ShowStr(0,0,12,(uint8_t *)"                ",1);
		LCD_ShowStr(0,0,12,(uint8_t *)line0_disp,1);
		LCD_GRAM_Update();
}


/******************************************************************************
* @brief  when press key_left or key_right,update cursor position or diaplay map bias
* @param  dir:	0:cursor/roll left
								1:cursor/roll right
					mode:	0:auto roll
								1:scroll key trig
* @retval	none
******************************************************************************/
static void line0Cursor_scroll(uint8_t dir, uint8_t mode)
{
		//get line0 memory content and disp content length
		uint8_t line0len_memory = strlen(line0_memory);
		uint8_t line0len_disp = strlen(line0_disp);
	
	
		//scroll right
		if(dir)
		{
				//如果line0长度已经超出屏幕显示范围并且显示内容已满
				if(line0len_disp==16 && line0len_memory>16)
				{
						//如果显示光标还未达屏幕右边界
						if(line0_cursor.dispCursor_pos<16)
						{
								//显示光标与操作光标同时右移1B，不用进行屏幕滚动
								line0_cursor.dispCursor_pos++;
								line0_cursor.memoryCursor_pos++;
						}
						//此外，如果显示光标（和操作光标）正好达屏幕右边界
						else if(line0_cursor.dispCursor_pos==16)
						{
								//如果操作光标还未达line0内存右边界
								if(line0_cursor.memoryCursor_pos<line0len_memory)
										//操作光标+1，显示光标在屏幕右边界不动
										line0_cursor.memoryCursor_pos++;
								//如果line0当前截取位置右侧还能有16B的截取裕量
								if(line0_cursor.intercept_pos<line0len_memory-16)
										//line0截取首地址右移1B，代表将要向右滚动1B长度
										line0_cursor.intercept_pos++;
						}
				}
				//此外，如果显示内容未满
				else
				{
						//如果光标滚动由方向键强制触发
						if(mode)
						{
								//如果显示光标还未达屏幕显示长度
								if(line0_cursor.dispCursor_pos<line0len_disp)
								{
										//显示光标与操作光标同时右移1B，不用进行屏幕滚动
										line0_cursor.dispCursor_pos++;
										line0_cursor.memoryCursor_pos++;
								}
						}
						//如果光标滚动由字符输入自动触发
						else
						{
								//如果显示光标还未达屏幕显示长度或刚好达到屏幕显示长度
								if(line0_cursor.dispCursor_pos<=line0len_disp)
								{
										//显示光标与操作光标同时右移1B，不用进行屏幕滚动
										line0_cursor.dispCursor_pos++;
										line0_cursor.memoryCursor_pos++;
								}
						}
				}
		}
		//scroll left
		else
		{
				//如果光标滚动由方向键强制触发
				if(mode)
				{
						//如果显示光标位置不在零点
						if(line0_cursor.dispCursor_pos>0)
						{
								//显示光标与操作光标同时左移1B，不用进行屏幕滚动
								line0_cursor.dispCursor_pos--;
								line0_cursor.memoryCursor_pos--;
						}
						//如果显示光标位置刚好在零点
						else if(line0_cursor.dispCursor_pos==0)
						{
								//如果这时操作光标没在零点处
								if(line0_cursor.memoryCursor_pos>0)
								{
										//操作光标左移1B，不用进行屏幕滚动
										line0_cursor.memoryCursor_pos--;
										//如果这时屏幕被滚动过至少一次
										if(line0_cursor.intercept_pos>0)
												//向左回滚
												line0_cursor.intercept_pos--;
								}
						}
				}
				
				//如果光标滚动由字符删除自动触发
				else
				{
						//如果显示光标位置不在零点
						if(line0_cursor.dispCursor_pos>0)
						{
								//显示光标与操作光标同时左移1B，不用进行屏幕滚动
								line0_cursor.dispCursor_pos--;
								line0_cursor.memoryCursor_pos--;
						}
						//如果显示光标位置被删到零点，并且line0被滚动至少1次，则进行翻页
						if(line0_cursor.dispCursor_pos==0 && line0_cursor.intercept_pos>0)
						{
								//如果剩余未显示的字符串长度不足或刚好等于一整页
								if(line0_cursor.intercept_pos<=16)
								{
										//翻页到line0最开始的地方
										line0_cursor.dispCursor_pos=line0_cursor.intercept_pos;
										line0_cursor.memoryCursor_pos=line0_cursor.intercept_pos;
										line0_cursor.intercept_pos=0;
								}
								//如果剩余未显示的字符串长度大于一整页
								if(line0_cursor.intercept_pos>16)
								{
										//向前翻一整页
										line0_cursor.dispCursor_pos=16;
										line0_cursor.intercept_pos-=16;
								}
						}
					
				}
				
				

		}
		//更新屏幕光标显示
		gui_updtCursor(1,line0_cursor.dispCursor_pos);
		//截取屏幕显示字符串
		line0Buf_intercept(line0_cursor.intercept_pos);
		
		
		printf("intercept_pos=");
		printf("%d\n\n",line0_cursor.intercept_pos);
		
		printf("Line0_disp=");
		printf("%s\n\n",line0_disp);
	
		printf("strlen(Line0_disp)=");
		printf("%d\n\n\n",strlen(line0_disp));
	
		printf("strlen(Line0)=");
		printf("%d\n\n",strlen(line0_memory));
		
		printf("Line0CursorPos=");
		printf("%d\n\n",line0_cursor.dispCursor_pos);
		
		printf("Line0EditCursor=");
		printf("%d\n\n\n",line0_cursor.memoryCursor_pos);
}


/******************************************************************************
* @brief  Intercept 16bytes from Line0 memory buffer to display buffer
* @param  start_pos: Line0 source buffer interceptng start address
* @retval 0: success
					1: pos out of range
******************************************************************************/
static uint8_t line0Buf_intercept(uint8_t start_pos)
{
//		//if line0 length is shortter than 16
//		if(strlen(line0_memory)<=16)
//				start_pos=0;
		//if line0 length is long enough
		if(start_pos>=0 && start_pos <=MAPBIAS_MAX)
		{
				memcpy(line0_disp,line0_memory+start_pos,16);
				gui_line0_displayUpdt();
		}
}
