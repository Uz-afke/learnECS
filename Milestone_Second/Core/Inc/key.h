#include "main.h"
#ifndef __KEY_H
#define __KEY_H

void Key_Init(void);
void Key_Tick(void);
uint8_t Key_GetEvent(void);

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif