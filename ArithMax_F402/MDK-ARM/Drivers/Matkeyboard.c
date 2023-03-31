#include "matkeyboard.h"

volatile uint8_t KeyVal = -1;
volatile uint8_t Key_updateFlag = 0;

static void SDA_IN(void)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		
		GPIO_InitStruct.Pin = MK_SDA_Pin;
		HAL_GPIO_Init(MK_SDA_GPIO_Port, &GPIO_InitStruct);	
}

static void SDA_OUT(void)
{
		GPIO_InitTypeDef GPIO_InitStruct = {0};
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;	
		
		GPIO_InitStruct.Pin = MK_SDA_Pin;
		HAL_GPIO_Init(MK_SDA_GPIO_Port, &GPIO_InitStruct);	
}

static void IIC_Start(void)
{
	SDA_OUT();
	
	SCL_SET;
	SDA_SET;
	delay_us(1);

	SDA_RST;
	delay_us(1);
	SCL_RST;	
	delay_us(1);
}

static void IIC_Stop(void)
{
	SDA_OUT();
	
	SCL_RST;
	SDA_RST;
	delay_us(1);
	SCL_SET;
	SDA_SET;	
	delay_us(1);
}

static uint8_t IIC_Wait_Ack(void)
{
	uint8_t waitTime = 0;
	SDA_IN();
	
	SCL_SET;	
	delay_us(1);
	
	while(HAL_GPIO_ReadPin(MK_SDA_GPIO_Port, MK_SDA_Pin))
	{
		waitTime++;
		if(waitTime > 250)
		{
			IIC_Stop();
			return 1;
		}
	}
	
	SCL_RST;
	return 0;
}

static void IIC_Ack(void)
{
	SCL_RST;
	SDA_OUT();
	
	SDA_RST;
	delay_us(1);
	SCL_SET;
	delay_us(1);
	SCL_RST;
}

static void IIC_NAck(void)
{
	SCL_RST;
	SDA_OUT();
	
	SDA_SET;
	delay_us(1);
	SCL_SET;
	delay_us(1);
	SCL_RST;
}

static void IIC_Send_Byte(uint8_t data)
{
		uint8_t t;
		SDA_OUT();
		SCL_RST;
		for(t = 0; t < 8; t++)
		{
				if((data & 0x80) >> 7)
				{
					SDA_SET;
				}
				else
				{
					SDA_RST;
				}
				data <<= 1;
				delay_us(1);
				SCL_SET;
				delay_us(1);
				SCL_RST;
				delay_us(1);
		}
}

static uint8_t IIC_Read_Byte(uint8_t ack)
{
		uint8_t i, receive = 0;
		SDA_IN();
		
		for(i = 0; i < 8; i++)
		{
				SCL_RST;
				delay_us(1);
				SCL_SET;
				delay_us(1);
				receive <<= 1;
				if(HAL_GPIO_ReadPin(MK_SDA_GPIO_Port, MK_SDA_Pin)) receive++;
				delay_us(1);
		}
		if(!ack)
				IIC_NAck();
		else
				IIC_Ack();
		
		return receive;
}


void MK_IIC_Write(uint16_t data)//向CH452写16位命令
{
		IIC_Start();
		IIC_Send_Byte((unsigned char)(data>>7) & CH452_I2C_MASK|CH452_I2C_ADDR1);
		SDA_SET;
		delay_us(1);
		SCL_SET;
		delay_us(1);
		SCL_RST;
		SDA_RST;	
		IIC_Send_Byte((unsigned char)data);
		IIC_Stop();
		delay_us(100);
}


uint8_t MK_IIC_Read(void)//从CH452读取按键值
{
		IIC_Start();
		IIC_Send_Byte((unsigned char)(CH452_GET_KEY>>7) & CH452_I2C_MASK|0x01|CH452_I2C_ADDR1);
		SCL_SET;
		delay_us(1);
		SCL_RST;
		delay_us(1);
		
		uint8_t data;
		data = IIC_Read_Byte(0);
		return data;
}


void CH452Init(void)
{
		MK_IIC_Write(CH452_RESET);
		MK_IIC_Write(CH452_SYSON2W);
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
		if(GPIO_Pin == GPIO_PIN_15)
		{
				KeyVal = MK_IIC_Read() - CH452_KEY_MIN;
			  Key_updateFlag = 1;
		}
		
		if(GPIO_Pin == GPIO_PIN_8)
		{
				printf("PWR_ON\r\n");
			  HAL_Delay(20);
		}
}

