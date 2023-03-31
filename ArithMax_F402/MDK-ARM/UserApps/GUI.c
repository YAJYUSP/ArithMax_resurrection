#include <main.h>
#include <string.h>
#include <stdlib.h>
#include "matkeyboard.h"
#include "arithmatic.h"
#include "gui.h"
#include "st7565.h"

char *Line0 = "";
char *Line1 = "";

char Line0_disp[17] = "";
char Line1_disp[17] = "";

uint8_t Line0CursorPos=0;//x coor of Line0Cursor(real Cursor shown on display,equal with String lenth on the left side of cursor in num)
uint8_t Line0EditCursor=0;//x coor of Line0EditCursor(string insert position in Line0 buffer,invisible)

uint8_t Line0CursorDispFlag=1;//Line0 cursor display switch

uint8_t Line0mapBias=0;//address bias of function mapLine02dispBuf

void dispstr_malloc(void)
{
		Line0 = (char *)malloc(0);
		Line1 = (char *)malloc(0);
}

void Line0DispUpdt(void)
{
		LCD_ShowStr(0,0,12,(uint8_t *)"                ",1);
		LCD_ShowStr(0,0,12,(uint8_t *)Line0_disp,1);
		LCD_Update();
}


void LCD_ShowCursor(uint8_t en, uint8_t pos)
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
* @brief  Update content of Line0 buffer according to key pressed
* @param  key_val: the key pressed
					key_update:key_val updating flag
* @retval none
******************************************************************************/
void Line0Key2mani(uint8_t key_val, uint8_t* key_update)
{
		if(*key_update)
		{
				*key_update=0;
				switch(key_val)
				{
						case KEY_0:
								strcat_dynamic("0",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_1:
								strcat_dynamic("1",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_2:
								strcat_dynamic("2",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_3:
								strcat_dynamic("3",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_4:
								strcat_dynamic("4",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_5:
								strcat_dynamic("5",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_6:
								strcat_dynamic("6",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_7:
								strcat_dynamic("7",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_8:
							  strcat_dynamic("8",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_9:
								strcat_dynamic("9",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_DOT:
								strcat_dynamic(".",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_PLUS:
								strcat_dynamic("+",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_MINUS:
								strcat_dynamic("-",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
					  case KEY_MUL:
								strcat_dynamic("*",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_DIVID:
								strcat_dynamic("/",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_LPARE:
								strcat_dynamic("(",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_RPARE:
								strcat_dynamic(")",&Line0,Line0EditCursor);
								Line0cursorScroll(1,0);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_DEL:
								if(!Line0Backspace(Line0EditCursor))
								{
										Line0cursorScroll(0,0);
										mapLine02dispBuf(Line0mapBias);
								}
								break;
						case KEY_LEFT:
								Line0cursorScroll(0,1);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_RIGHT:	
								Line0cursorScroll(1,1);
								mapLine02dispBuf(Line0mapBias);
								break;
						case KEY_EQUAL:
								input2RPN_conv();
								break;
				}
		}
}

/******************************************************************************
* @brief  when press key_left or key_right,update cursor position or diaplay map bias
* @param  dir:	0:cursor/roll left
								1:cursor/roll right
					mode:	0:auto roll
								1:scroll key trig
* @retval	none
******************************************************************************/
void Line0cursorScroll(uint8_t dir, uint8_t mode)
{
		uint8_t Line0len = strlen(Line0);
	
//		printf("Line0=");
//		printf("%s\n",Line0);
//		
//		printf("strlen(Line0_disp)=");
//		printf("%d\n",strlen(Line0_disp));
//		
//		printf("Line0CursorPos=");
//		printf("%d\n",Line0CursorPos);
//		
//		printf("Line0EditCursor=");
//		printf("%d\n",Line0EditCursor);
	
	
		if(dir)
		{
			
				if(strlen(Line0_disp)==16 && Line0len>16)
				{
						if(Line0CursorPos<16)
						{
								Line0CursorPos++;
								Line0EditCursor++;
						}
						else if(Line0CursorPos==16)
						{
								if(Line0EditCursor<Line0len)
										Line0EditCursor++;
								if(Line0len>16 && Line0mapBias<Line0len-16)
										Line0mapBias++;
						}
				}
				else
				{
						if(mode)
						{
								if(Line0CursorPos<strlen(Line0_disp))
								{
										Line0CursorPos++;
										Line0EditCursor++;
								}
						}
						else
						{
								if(Line0CursorPos<=strlen(Line0_disp))
								{
										Line0CursorPos++;
										Line0EditCursor++;
								}
						}
				}
		}
		else
		{
				if(Line0CursorPos>0)
				{
						Line0CursorPos--;
						Line0EditCursor--;
				}
				else if(Line0CursorPos==0)
				{
						if(Line0EditCursor>0)
								Line0EditCursor--;
						if(Line0len>16 && Line0mapBias>0)
								Line0mapBias--;
				}
		}
		LCD_ShowCursor(1,Line0CursorPos);
}


/******************************************************************************
* @brief  Intercept 16bytes from Line0 source buffer to display buffer
* @param  pos:Line0 source buffer address bias
* @retval 0:success
					1:pos out of range
******************************************************************************/
uint8_t mapLine02dispBuf(uint8_t pos)
{	
		if(strlen(Line0)<=16)
				pos=0;
	
		if(pos>=0 && pos <=MAPBIAS_MAX)
		{
				memcpy(Line0_disp,Line0+pos,16);
				Line0DispUpdt();
		}
}

/******************************************************************************
* @brief  Backspace in Line0 buffer at cursor pos
* @param  cursor: expected backspace position
* @retval 0:success
					1:Line0 empty 
******************************************************************************/
uint8_t Line0Backspace(uint8_t cursor)
{
		if(cursor>0)
		{
				//new Line0 buffer size
				uint8_t Line0_newsize = strlen(Line0);
			
				//copy the content on right side of old Line0 buffer to a cache
				uint8_t RightCacheSize = strlen(Line0)-cursor+1;
				char *RightCache = (char *)malloc(RightCacheSize);
				memset(RightCache,0,RightCacheSize);		//significant step
				memcpy(RightCache,Line0+cursor,RightCacheSize-1);

				//copy the content on left side of old Line0 buffer to a cache
				uint8_t LeftCacheSize = cursor;							//strlen of LeftCacheSize = cursor-1
				char *LeftCache = (char *)malloc(LeftCacheSize);
				memset(LeftCache,0,LeftCacheSize);				//significant step
				memcpy(LeftCache,Line0,LeftCacheSize-1);

				//release memory of old Line0 buffer
				free(Line0);		
				Line0 = (char *)malloc(Line0_newsize);		
				memset(Line0,0,Line0_newsize);		//important step
			
				memcpy(Line0,LeftCache,strlen(LeftCache));
				memcpy(Line0+strlen(LeftCache),RightCache,strlen(RightCache));	

				free(RightCache);
				free(LeftCache);
				RightCache = NULL;
				LeftCache = NULL;
				return 0;
		}
		else
				return 1;
}

///******************************************************************************
//* @brief  add string "str" to str0 buffer
//* @param  *str: pointer that point to "str"
//					cursor: expected string insert position
//* @retval 0:success
//				  1:str0 buffer full
//******************************************************************************/
//uint8_t strcat_dynamic(char *str, char **str0, uint8_t cursor)
//{
//		//new Line0 buffer size
//		uint8_t str0_newsize = strlen(*str0)+strlen(str)+1;
//		//if meet the requirment,continue the operations
//		if(str0_newsize <= LINE0_LEN_MAX)
//		{
//				//copy the content on right side of old Line0 buffer to a cache
//				uint8_t RightCacheSize = strlen(*str0)-cursor+1;
//				char *RightCache = (char *)malloc(RightCacheSize);
//				memset(RightCache,0,RightCacheSize);		//significant step
//				memcpy(RightCache,*str0+cursor,RightCacheSize-1);

//				//copy the content on left side of old Line0 buffer to a cache
//				uint8_t LeftCacheSize = cursor+1;					//cursor and left string len is equal in num
//				char *LeftCache = (char *)malloc(LeftCacheSize);
//				memset(LeftCache,0,LeftCacheSize);		//significant step
//				memcpy(LeftCache,*str0,LeftCacheSize-1);
//	
//				//release memory of old Line0 buffer
//				free(*str0);		
//			  *str0 = (char *)malloc(str0_newsize);		
//				memset(*str0,0,str0_newsize);		//important step
//			
//				memcpy(*str0,LeftCache,LeftCacheSize-1);			
//				memcpy(*str0+LeftCacheSize-1,str,strlen(str));	
//				memcpy(*str0+(LeftCacheSize-1)+strlen(str),RightCache,RightCacheSize-1);	
//			
//				free(RightCache);
//				free(LeftCache);
//			  RightCache = NULL;
//				LeftCache = NULL;
//				return 0;
//		}
//		return 1;
//}

/******************************************************************************
* @brief  add string "str" to str0 buffer
* @param  *str: pointer that point to "str"
					cursor: expected string insert position
* @retval 0:success
				  1:str0 buffer full
******************************************************************************/
uint8_t strcat_dynamic(char *str, char **str0, uint8_t cursor)
{
		//new Line0 buffer size
		uint8_t str0_newsize = strlen(*str0)+strlen(str)+1;
		//if meet the requirment,continue the operations
		if(str0_newsize <= LINE0_LEN_MAX)
		{				
				//copy the content on right side of old Line0 buffer to a cache
				uint8_t RightCacheSize = strlen(*str0)-cursor+1;
				char *RightCache = (char *)malloc(RightCacheSize);
				memset(RightCache,0,RightCacheSize);		//significant step
				memcpy(RightCache,*str0+cursor,RightCacheSize-1);
		
				//copy the content on left side of old Line0 buffer to a cache
				uint8_t LeftCacheSize = cursor+1;					//cursor and left string len is equal in num
				char *LeftCache = (char *)malloc(LeftCacheSize);
				memset(LeftCache,0,LeftCacheSize);		//significant step
				memcpy(LeftCache,*str0,LeftCacheSize-1);
	
				//release memory of old Line0 buffer
				free(*str0);		
			  *str0 = (char *)malloc(str0_newsize);		
				memset(*str0,0,str0_newsize);		//important step
			
				memcpy(*str0,LeftCache,LeftCacheSize-1);			
				memcpy(*str0+LeftCacheSize-1,str,strlen(str));	
				memcpy(*str0+(LeftCacheSize-1)+strlen(str),RightCache,RightCacheSize-1);	
			
				free(RightCache);
				RightCache = NULL;
				free(LeftCache);
				LeftCache = NULL;
				return 0;
		}
		return 1;
}