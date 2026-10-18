#include <stdint.h>
#ifndef __LED_H
#define  __LED_H
#include "main.h"


#define LED_BLUE_CH  TIM_CHANNEL_1
#define LED_GREEN_CH  TIM_CHANNEL_2
#define LED_RED_CH  TIM_CHANNEL_3
#define LED_MAX_BRIGHT 65535
#define LED_OFF 0

void LED_Init(void);
void LED_SetBright(uint32_t channel,uint32_t pwm_val);
void LED_AllOn(void);
void LED_AllOff(void);

#endif
