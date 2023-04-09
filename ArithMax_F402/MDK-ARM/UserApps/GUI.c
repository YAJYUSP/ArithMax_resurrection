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
				//���line0�����Ѿ�������Ļ��ʾ��Χ������ʾ��������
				if(line0len_disp==16 && line0len_memory>16)
				{
						//�����ʾ��껹δ����Ļ�ұ߽�
						if(line0_cursor.dispCursor_pos<16)
						{
								//��ʾ�����������ͬʱ����1B�����ý�����Ļ����
								line0_cursor.dispCursor_pos++;
								line0_cursor.memoryCursor_pos++;
						}
						//���⣬�����ʾ��꣨�Ͳ�����꣩���ô���Ļ�ұ߽�
						else if(line0_cursor.dispCursor_pos==16)
						{
								//���������껹δ��line0�ڴ��ұ߽�
								if(line0_cursor.memoryCursor_pos<line0len_memory)
										//�������+1����ʾ�������Ļ�ұ߽粻��
										line0_cursor.memoryCursor_pos++;
								//���line0��ǰ��ȡλ���Ҳ໹����16B�Ľ�ȡԣ��
								if(line0_cursor.intercept_pos<line0len_memory-16)
										//line0��ȡ�׵�ַ����1B������Ҫ���ҹ���1B����
										line0_cursor.intercept_pos++;
						}
				}
				//���⣬�����ʾ����δ��
				else
				{
						//����������ɷ����ǿ�ƴ���
						if(mode)
						{
								//�����ʾ��껹δ����Ļ��ʾ����
								if(line0_cursor.dispCursor_pos<line0len_disp)
								{
										//��ʾ�����������ͬʱ����1B�����ý�����Ļ����
										line0_cursor.dispCursor_pos++;
										line0_cursor.memoryCursor_pos++;
								}
						}
						//������������ַ������Զ�����
						else
						{
								//�����ʾ��껹δ����Ļ��ʾ���Ȼ�պôﵽ��Ļ��ʾ����
								if(line0_cursor.dispCursor_pos<=line0len_disp)
								{
										//��ʾ�����������ͬʱ����1B�����ý�����Ļ����
										line0_cursor.dispCursor_pos++;
										line0_cursor.memoryCursor_pos++;
								}
						}
				}
		}
		//scroll left
		else
		{
				//����������ɷ����ǿ�ƴ���
				if(mode)
				{
						//�����ʾ���λ�ò������
						if(line0_cursor.dispCursor_pos>0)
						{
								//��ʾ�����������ͬʱ����1B�����ý�����Ļ����
								line0_cursor.dispCursor_pos--;
								line0_cursor.memoryCursor_pos--;
						}
						//�����ʾ���λ�øպ������
						else if(line0_cursor.dispCursor_pos==0)
						{
								//�����ʱ�������û����㴦
								if(line0_cursor.memoryCursor_pos>0)
								{
										//�����������1B�����ý�����Ļ����
										line0_cursor.memoryCursor_pos--;
										//�����ʱ��Ļ������������һ��
										if(line0_cursor.intercept_pos>0)
												//����ع�
												line0_cursor.intercept_pos--;
								}
						}
				}
				
				//������������ַ�ɾ���Զ�����
				else
				{
						//�����ʾ���λ�ò������
						if(line0_cursor.dispCursor_pos>0)
						{
								//��ʾ�����������ͬʱ����1B�����ý�����Ļ����
								line0_cursor.dispCursor_pos--;
								line0_cursor.memoryCursor_pos--;
						}
						//�����ʾ���λ�ñ�ɾ����㣬����line0����������1�Σ�����з�ҳ
						if(line0_cursor.dispCursor_pos==0 && line0_cursor.intercept_pos>0)
						{
								//���ʣ��δ��ʾ���ַ������Ȳ����պõ���һ��ҳ
								if(line0_cursor.intercept_pos<=16)
								{
										//��ҳ��line0�ʼ�ĵط�
										line0_cursor.dispCursor_pos=line0_cursor.intercept_pos;
										line0_cursor.memoryCursor_pos=line0_cursor.intercept_pos;
										line0_cursor.intercept_pos=0;
								}
								//���ʣ��δ��ʾ���ַ������ȴ���һ��ҳ
								if(line0_cursor.intercept_pos>16)
								{
										//��ǰ��һ��ҳ
										line0_cursor.dispCursor_pos=16;
										line0_cursor.intercept_pos-=16;
								}
						}
					
				}
				
				

		}
		//������Ļ�����ʾ
		gui_updtCursor(1,line0_cursor.dispCursor_pos);
		//��ȡ��Ļ��ʾ�ַ���
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
