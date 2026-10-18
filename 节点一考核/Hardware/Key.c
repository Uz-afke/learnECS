#include "stm32f10x.h"                  // Device header

#define KEY_DOU_TICKS		200  //消抖时间



volatile uint8_t Key_State = 0;

volatile uint16_t Key_Timer = 0;

volatile uint8_t Key_Event = 0;					

 void Key_Init(void)
 {
	 RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);	
	 GPIO_InitTypeDef GPIO_InitStructure;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOA,&GPIO_InitStructure);
	 
	 
	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12);	  //引脚映射
	
	 EXTI_InitTypeDef EXTI_InitStructure;	    //外部中断触发
	 EXTI_InitStructure.EXTI_Line = EXTI_Line12;	 
   EXTI_InitStructure.EXTI_LineCmd = ENABLE;		 
	 EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //中断模式
	 EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
	 EXTI_Init(&EXTI_InitStructure);
	 
	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
 }
	 
 void Key_Tick(void)
{
	if (Key_State == 1)		
	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 0)
		{
			if (++ Key_Timer >= KEY_DOU_TICKS)
				{
				Key_Event = 1;
				Key_State = 2;
				Key_Timer = 0;
				}
			}
			else
			{
				Key_Timer = 0;
			}
		
	}
	else if (Key_State == 2)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 1) 
			{
				if(++Key_Timer >=KEY_DOU_TICKS)
				{
			Key_State = 0; 
				Key_Timer=0;
				}
			}
			else
			{
			Key_Timer=0;
			}
	}
}

 uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;												
	 __disable_irq();
	if(Key_Event)
	{
	KeyNum = Key_Event;												
	Key_Event = 0;													
	}
	__enable_irq();
	return KeyNum;		
}
	
void EXTI15_10_IRQHandler(void) //中断服务函数
{
	if (EXTI_GetITStatus(EXTI_Line12) == SET)		//确定发生外部中断
	{
		EXTI_ClearITPendingBit(EXTI_Line12);
		if(Key_State == 0)
		{
			Key_State = 1;											 //
		Key_Timer = 0;												
		}
	}
}
