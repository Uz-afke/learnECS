#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
#include "PWM.h"
#include "Timer.h"
#define LED_MODE_ON	 0								//quanjvbianliang
#define LED_MODE_BREATH  1								
#define LED_MODE_RUN  2	
#define LED_MODE_COUNT  3	

/*流水灯*/
#define LED_RUN_COUNT		4		
#define RUN_INTERVAL		200										//间隔ms，流水速度

/*呼吸灯*/
#define BREATH_INTERVAL		10										//间隔ms，呼吸快慢
volatile uint32_t sys_tick_ms = 0;

const uint8_t LED_RUNTable[LED_RUN_COUNT] = {0x01, 0x02, 0x04, 0x08};	


uint8_t LED_Mode = LED_MODE_ON;											
int16_t LED_Duty = 0;
int8_t LED_Dir = 1;	
uint8_t LED_Step = 0;	
uint16_t LED_Timer = 0;	



void Breath_Output(uint8_t Duty)
{
	PWM_SetCompare3(Duty);												//软件改占空比：改CCR
}

void LED_Update(void)
{
	if(LED_Mode ==LED_MODE_ON)
	{
			LED_AllOFF();		
			Breath_Output(0);		
			LED11_ON();													
	}												
		
		if(LED_Mode== LED_MODE_BREATH)									//1
		{
			LED11_OFF();												
			LED_AllOFF();												
			Breath_Output(LED_Duty);									
		}
		
		if(LED_Mode == LED_MODE_RUN)											//2
		{
			LED11_OFF();			
			Breath_Output(0);		
			LED_ShowMask(LED_RUNTable[LED_Step]);			
		}
	}



int main(void)
{
	
	uint32_t last_tick_ms = 0;
  uint16_t breath_acc = 0;
  uint16_t run_acc = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	LED_Init();
	Timer_Init();
	Key_Init();
	PWM_Init();
	
	
	
	while(1)
	{
		uint8_t KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			LED_Mode = (LED_Mode + 1) % LED_MODE_COUNT;  //取余进行模式切换
			LED_Duty = 0; 
			LED_Dir = 1;
			LED_Step = 0;
			LED_Timer = 0;
			LED_Update();
		}
		
		if (sys_tick_ms != last_tick_ms)		
		{
			uint32_t delta_ms = sys_tick_ms - last_tick_ms;
			last_tick_ms = sys_tick_ms;
			
			if (LED_Mode == LED_MODE_BREATH)							//呼吸灯模式：软件改占空比
			{
				breath_acc +=delta_ms;
				if (breath_acc >= BREATH_INTERVAL)				
				{
					 breath_acc = 0;	
					LED_Duty += LED_Dir*1;           
					if (LED_Duty >= 100)
						{
						LED_Duty = 100; LED_Dir = -1; 
						}	
					else if (LED_Duty <= 0)
						{
						LED_Duty = 0; LED_Dir = 1;
						}	
					Breath_Output((uint8_t)LED_Duty);
				}
			}
			else if (LED_Mode == LED_MODE_RUN)			
			{
				run_acc+=delta_ms;
				if (run_acc >= RUN_INTERVAL)	
				{
					run_acc =0;
					LED_Step = (LED_Step + 1) % LED_RUN_COUNT;			
					LED_Update();
				}
			}
		}
}
}
