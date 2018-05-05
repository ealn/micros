

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include <CustomIOWrapper.h>
#include <LCD.h>

/**
 * main.c
 */
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_8| SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ); //SysClk=25MHz
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Check if the peripheral access is enabled.
    //
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA) &&
            !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB) &&
            !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE) &&
            !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) &&
            !SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0))
    {
    }

    TimerClockSourceSet(TIMER0_BASE,TIMER_CLOCK_SYSTEM);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);
    TimerUpdateMode(TIMER0_BASE,TIMER_A,TIMER_UP_LOAD_IMMEDIATE);
    TimerLoadSet(TIMER0_BASE,TIMER_A,25000);
    TimerEnable(TIMER0_BASE, TIMER_A);

    PIN_AS_OUTPUT(LED_SYSTEMLED);
    PIN_AS_OUTPUT(LCD_PIN_E);
    PIN_AS_OUTPUT(LCD_PIN_RS);
    PIN_AS_OUTPUT(LCD_PIN_DATA4);
    PIN_AS_OUTPUT(LCD_PIN_DATA5);
    PIN_AS_OUTPUT(LCD_PIN_DATA6);
    PIN_AS_OUTPUT(LCD_PIN_DATA7);
    PIN_AS_INPUT(BTN_BUTTON2);

    uint32_t btn = 0;
    uint8_t ledstatus = 0;

    uint32_t counter_lcd_task=0;
    uint32_t counter_btn_task=0;
    uint32_t counter_game_task=0;
    uint32_t counter_led_task=0;

    //uint32_t clock = SysCtlClockGet();

    OUTPUT_LOW(LCD_PIN_RS);
    OUTPUT_LOW(LCD_PIN_DATA4);
    OUTPUT_LOW(LCD_PIN_DATA5);
    OUTPUT_LOW(LCD_PIN_DATA6);
    OUTPUT_LOW(LCD_PIN_DATA7);
    OUTPUT_LOW(LCD_PIN_E);


    LCD_Init();

    while(1){
        // System tick = 1 ms
        while(TimerValueGet(TIMER0_BASE,TIMER_A) != 25000)
        {
        }
        TimerEnable(TIMER0_BASE, TIMER_A);

        counter_lcd_task++;
        counter_btn_task++;
        counter_game_task++;
        counter_led_task++;

        if(counter_lcd_task == 1)
        {
            counter_lcd_task=0;
            LCD_RunSM();
        }

        if(counter_btn_task == 100)
        {
            counter_btn_task=0;
            btn = READ_BUTTON(BTN_BUTTON2);
        }

        if(counter_game_task == 200)
        {
            counter_game_task=0;
            GAME_Run(btn);
        }

        if(counter_led_task == 500)
        {
            counter_led_task=0;

            if(ledstatus == 0)
            {
                OUTPUT_HIGH(LED_SYSTEMLED);
                ledstatus=1;
            }
            else
            {
                OUTPUT_LOW(LED_SYSTEMLED);
                ledstatus=0;
            }
        }
    }
}
