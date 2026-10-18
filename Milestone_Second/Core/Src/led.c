#include "led.h"
extern TIM_HandleTypeDef htim5;
#include "stm32f4xx_hal_tim.h"


void LED_Init(void)
{
    HAL_TIM_PWM_Start(&htim5, LED_BLUE_CH);
    HAL_TIM_PWM_Start(&htim5, LED_GREEN_CH);
    HAL_TIM_PWM_Start(&htim5, LED_RED_CH);

}

void LED_SetBright(uint32_t channel, uint32_t pwm_val)
{
    __HAL_TIM_SET_COMPARE(&htim5, channel, pwm_val);

}

void LED_AllOn()
{
    LED_SetBright(LED_BLUE_CH, LED_MAX_BRIGHT);
    LED_SetBright(LED_GREEN_CH, LED_MAX_BRIGHT);
    LED_SetBright(LED_RED_CH, LED_MAX_BRIGHT);
}
void LED_AllOff()
{
    LED_SetBright(LED_BLUE_CH, LED_OFF);
    LED_SetBright(LED_GREEN_CH, LED_OFF);
    LED_SetBright(LED_RED_CH, LED_OFF);
}