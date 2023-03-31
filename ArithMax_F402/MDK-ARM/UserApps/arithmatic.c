#include <main.h>
#include <string.h>
#include <stdlib.h>
#include "gui.h"
#include "arithmatic.h"
#include "arm_math.h"
#include "stack.h"


//init of user input stack and converted RPN stack
Stack Stack_usrInput;
Stack Stack_RPN;
void arithInit(void)
{
		Stack_Create(Stack_usrInput);
		Stack_Create(Stack_RPN);
}


////push corresponding element to input_stack when  key has been triggered
//uint8_t inputStack_push(Type input_type, OP input_opr, float num)
//{
//		Stack_Element elem0;
//		if(input_type==NUMBER)
//		{
//				elem0->type=NUMBER;
//				elem0->Number=num;
//				elem0->Operator=NOUSE;
//				Stack_Push(elem0,Stack_usrInput);
//				return 0;
//		}
//		else if(input_type==OPERATOR)
//		{
//				elem0->type=OPERATOR;
//				elem0->Number=0;
//				elem0->Operator=input_opr;
//				Stack_Push(elem0,Stack_usrInput);
//				return 0;
//		}
//		else
//				return 1;
//}



/******************************************************************************
* @brief  tell the char from num and operations
* @param  chr: char
* @retval 1:is a num
					2:is a dot
					3:others
******************************************************************************/
uint8_t charRecog(char chr)
{
		int num = (int)chr;
	
		if(num>=48 && num<=57)
				return 1;
		else if(num==46)
				return 2;
		
		return 0;
}


uint8_t input2RPN_conv(void)
{
		uint8_t Line0len=strlen(Line0);
	  uint8_t cnt=0;           //num of bytes have been already processed 
		uint8_t type_lastChr = 0;//type of char last read
	
		char* currNum = "";
		currNum = (char *)malloc(0);
		memset(currNum,0,sizeof(&currNum));
	
		uint8_t numLen = 0;
		OP operation = NOUSE;
	
		uint8_t errorFlag = 0;
		
	
		while(cnt<Line0len)
		{
				char currReadChr = Line0[cnt];
				//if current char is a num or dot,write it into currNum buf
				if(charRecog(currReadChr))
				{
						numLen = strlen(currNum);
						strcat_dynamic(&currReadChr,&currNum,numLen);			
						type_lastChr = 1;
						cnt++;
				}
				//if current char is a operator,convert previous read string to float
				//and push the float and operator to RPN stack
				else
				{
						printf("%s\n",currNum);
						printf("%.2f\n",atof(currNum));
						type_lastChr = 0;
						cnt++;
				}
		}
		
		
	
}

