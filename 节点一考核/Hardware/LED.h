#include "stm32f10x.h"                  // Device header

#ifndef __LED_H
#define __LED_H

void LED_Init(void);
void LED_AllOFF(void);

void LED_ShowMask(uint8_t Mask);

void LED11_ON(void);
void LED11_OFF(void);

	
#endif
