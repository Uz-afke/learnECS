#include "stm32f10x.h"                  // Device header
#include "delay.h"
int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIO_InitStucture;
	GPIO_InitStucture.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStucture.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStucture);
	
	
	
	while(1)
	{
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
		Delay_ms(100);
		GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_SET);
		Delay_ms(700);GPIO_WriteBit(GPIOB,GPIO_Pin_12,Bit_RESET);
	
	}
}
