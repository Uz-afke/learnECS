#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "Buzzer.h"
#include "LightSensor.h"

uint8_t KeyNum;

int main(void)
{
	Buzzer_Init();
	LightSenser_Init();
	
	while(1)
	{
		if (LightSenser_Get() == 1)
		{
			Buzzer_ON();
		}
		else
		{
			Buzzer_OFF();
		}
			
	}
}
