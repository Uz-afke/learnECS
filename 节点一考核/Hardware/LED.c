#include "stm32f10x.h"                  // Device header
#include "LED.h"
#define LED_RUN_PINS  (GPIO_Pin_1 | GPIO_Pin_3 |GPIO_Pin_5 |GPIO_Pin_7)
#define LED_LONG_PIN  (GPIO_Pin_11)

void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = LED_RUN_PINS | LED_LONG_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA ,&GPIO_InitStructure);
	
  LED_AllOFF();
	LED11_ON();
	
}

void LED_ShowMask(uint8_t Mask)										
{
	if (Mask & 0x01)
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_1);
		}	
	else             
		{
		GPIO_SetBits  (GPIOA, GPIO_Pin_1); 
		}
	if (Mask & 0x02) 
		{ 
			GPIO_ResetBits(GPIOA, GPIO_Pin_3); 
		}
	else             
		{
		GPIO_SetBits  (GPIOA, GPIO_Pin_3);
		}
	if (Mask & 0x04) 
		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_5); 
		}
	else  
    {
		GPIO_SetBits  (GPIOA, GPIO_Pin_5);
		}
	if (Mask & 0x08) 
		{
		GPIO_ResetBits(GPIOA, GPIO_Pin_7); 
		}
	else            
		{ 
		GPIO_SetBits  (GPIOA, GPIO_Pin_7); 
		}
}

void LED_AllOFF(void)
{
	GPIO_SetBits(GPIOA, LED_RUN_PINS);			
}

void LED11_ON(void)
{
	GPIO_ResetBits(GPIOA, LED_LONG_PIN);
}

void LED11_OFF(void)
{
	GPIO_SetBits(GPIOA, LED_LONG_PIN);	
}
