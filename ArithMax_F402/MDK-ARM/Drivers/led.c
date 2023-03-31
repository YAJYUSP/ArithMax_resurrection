#include "led.h"

extern TIM_HandleTypeDef htim2;

void LED_G(uint8_t cp)
{
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,99-cp);
}

void LED_R(uint8_t cp)
{
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,99-cp);
}

void LED_B(uint8_t cp)
{
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,99-cp);
}


void LED_Grad(void)
{
		static uint8_t LEDG_Brightness = 0;
		static uint8_t LEDR_Brightness  = 33;
		static uint8_t LEDB_Brightness = 66;
	  static uint8_t cntSta[3] = {1};     //0¼Ó1¼õ
	
				if(cntSta[0])
						LEDG_Brightness++;
				else
						LEDG_Brightness--;
				
				if(cntSta[1])
						LEDR_Brightness++;
				else
						LEDR_Brightness--;
				
				if(cntSta[2])
						LEDB_Brightness++;
				else
						LEDB_Brightness--;
				
				if(LEDG_Brightness==99)
						cntSta[0]=0;
				else if(LEDG_Brightness==0)
						cntSta[0]=1;
				if(LEDR_Brightness==99)
						cntSta[1]=0;
				else if(LEDR_Brightness==0)
						cntSta[1]=1;
				if(LEDB_Brightness==99)
						cntSta[2]=0;
				else if(LEDB_Brightness==0)
						cntSta[2]=1;

				LED_G(LEDG_Brightness);
				LED_R(LEDR_Brightness);
				LED_B(LEDB_Brightness);
}