#include "stm32f10x.h"                  // Device header

uint16_t CountSensor_Count;
void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStrusture;
	GPIO_InitStrusture.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStrusture.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStrusture.GPIO_Speed =  GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStrusture);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	EXTI_InitTypeDef EXTI_InitStrusture;
	EXTI_InitStrusture.EXTI_Line = EXTI_Line14;
	EXTI_InitStrusture.EXTI_LineCmd = ENABLE;
	EXTI_InitStrusture.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStrusture.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStrusture);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1 ;
	NVIC_Init(&NVIC_InitStructure);
}

uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14)==SET)
	{
		CountSensor_Count ++;
		EXTI_ClearITPendingBit(EXTI_Line14);
	}


}
