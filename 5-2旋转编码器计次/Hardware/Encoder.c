#include "stm32f10x.h"                  // Device header

int16_t Encoder_Count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStrusture;
	GPIO_InitStrusture.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStrusture.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_InitStrusture.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrusture);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	EXTI_InitTypeDef EXTI_InitStrusture;
	EXTI_InitStrusture.EXTI_Line = EXTI_Line0 | EXTI_Line1;
	EXTI_InitStrusture.EXTI_LineCmd = ENABLE;
	EXTI_InitStrusture.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrusture.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStrusture);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1 ;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =2 ;
	NVIC_Init(&NVIC_InitStructure);
}


void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1 )== 0)
		{
			Encoder_Count --;
		}
		EXTI_ClearITPendingBit(EXTI_Line0);
	}

}

int16_t Encoder_Get(void)
{
	int16_t Temp;
	Temp =Encoder_Count;
	Encoder_Count = 0;
	return Temp;
	
}

void EXTI1_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line1) == SET)
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0 )== 0)
		{
			Encoder_Count ++;
		}
		EXTI_ClearITPendingBit(EXTI_Line1);
	}

}
