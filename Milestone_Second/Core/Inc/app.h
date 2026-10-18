#ifndef __APP_H
#define __APP_H

#include "main.h"
#include "led.h"
  
#define BREATH_STEP 100    //呼吸步长
#define RUN_SPEED_MS 300    //流水快慢
extern volatile uint32_t LED_Duty;
extern volatile uint8_t LED_DutyPercent;
void State_Init(void);
void State_Tick(void);
void State_UpdateMode(void);
#endif