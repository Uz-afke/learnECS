#include "app.h"
#include <stdint.h>

#define LED_MODE_ALL_ON       0
#define LED_MODE_BLUE_BREATH  1
#define LED_MODE_GREEN_BREATH 2
#define LED_MODE_RED_BREATH   3
#define LED_MODE_COUNT        4
volatile uint32_t app_run_tick = 0;
volatile uint8_t LED_Mode = LED_MODE_ALL_ON;
volatile uint32_t LED_Duty = 0;
volatile uint8_t LED_DutyPercent =0;
static int8_t breath_dir = 1;
static uint32_t run_tick = 0;
static uint8_t runlight_step = 0;

static const uint32_t breath_channel[LED_MODE_COUNT] = {
    0,
    LED_BLUE_CH,
    LED_GREEN_CH,
    LED_RED_CH
};

static const uint32_t flow_channel[LED_MODE_COUNT][2] = {
    {0, 0},
    {LED_RED_CH, LED_GREEN_CH},
    {LED_BLUE_CH, LED_RED_CH},
    {LED_BLUE_CH, LED_GREEN_CH}
};
static void LED_Update(void)
{
    if (LED_Mode == LED_MODE_ALL_ON)
    {
        LED_AllOn();
        return;
    }

    LED_SetBright(flow_channel[LED_Mode][runlight_step], LED_MAX_BRIGHT);
    LED_SetBright(flow_channel[LED_Mode][1 - runlight_step], LED_OFF);
}
static void Breath_Output(void)
{
    LED_DutyPercent = (uint8_t)((LED_Duty * 100U) / 65535U);
    LED_SetBright(breath_channel[LED_Mode], LED_Duty);
}

void State_Init(void)
{
    LED_Mode = LED_MODE_ALL_ON;
    LED_Duty = 0;
    breath_dir = 1;
    run_tick = 0;
    runlight_step = 0;

    LED_AllOn();
}

void State_UpdateMode(void)
{
    LED_Mode =( LED_Mode +1)%LED_MODE_COUNT;
    LED_Duty = 0;
    breath_dir = 1;
    run_tick = 0;
    runlight_step = 0;
   if (LED_Mode == LED_MODE_ALL_ON)
    {
        LED_AllOn();
    }
    else
    {
        Breath_Output();
        LED_Update();
    }
}

void State_Tick(void)
{
    app_run_tick++;
    switch (LED_Mode) {
    case 0:
    break;
    case 1:
    case 2:
    case 3:
        run_tick ++;
        if (breath_dir == 1) {
        LED_Duty +=BREATH_STEP;
            if (LED_Duty >=65535) {
            LED_Duty=65535;
            breath_dir=-1;
            }
        }
        else {
            if (LED_Duty<=BREATH_STEP) {
            LED_Duty= 0;
            breath_dir=1;
            }
            else {
            LED_Duty -= BREATH_STEP;
            }
        }
        Breath_Output();
        if (run_tick >= RUN_SPEED_MS)
        {
            run_tick = 0;
            runlight_step = (runlight_step + 1) % 2;
            LED_Update();
        }
        break;

    }
}
