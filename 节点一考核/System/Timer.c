#include "stm32f10x.h"                  // Device header
#include "Key.h"


uint8_t Timer_Div = 0;
extern volatile uint32_t sys_tick_ms; 
void Timer_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_InternalClockConfig(TIM2);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
	TIM_TimeBaseInitStructure.TIM_Period = 100-1; //ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1; //PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2,TIM_FLAG_Update);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //更新中断使能
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;   //中断控制器，配置中断通道
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2,ENABLE); //启动定时器
}
	
void TIM2_IRQHandler(void) //中断服务函数
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)    //中断发生
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);   //清除中断标志位
		     Key_Tick();	//执行消抖
		if (++ Timer_Div >= 10)  //如果计数超过1MS，把div置0，count加一
		{
			Timer_Div = 0;									
			sys_tick_ms ++;		
			
		}
		
	}


}
