#include "app.h"
#include "key.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"


#define KEY_DEBOUNCE_MS 20

volatile uint8_t Key_State = 0;
volatile uint16_t Key_Timer = 0;
uint8_t Key_Event = 0;

void Key_Init(void)
{
    Key_State = 0;
    Key_Timer = 0;
    Key_Event = 0;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin==GPIO_PIN_0) {
        if (Key_State ==0) {
            Key_State = 1;
            Key_Timer = 0;
        }
    }
}

void Key_Tick(void)
{
    if (Key_State == 1)
    {
        if (++Key_Timer >= KEY_DEBOUNCE_MS)
        {
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_RESET)
            {
                Key_Event = 1;
                Key_State = 2;
                Key_Timer = 0;
            }
            else
            {
                Key_State = 0;
            }
        }
    }
    else if (Key_State == 2)
    {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET)
        {
            Key_State = 0;
        }
    }
}

uint8_t Key_GetEvent(void)
{
    uint8_t event = Key_Event;
    Key_Event = 0;
    return event;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM6) {
    Key_Tick();
    if (Key_GetEvent())
        {
            State_UpdateMode();
        }

        State_Tick();
    }
}