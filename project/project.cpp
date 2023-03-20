#include <stdio.h>

#include <bsp.h>
#include <params.h>
#include <version.h>

#include <gpio.h>
#include <crc.h>
#include <swo.h>
#include <dummy.h>

void bsp_main()
{
    swo_init();
    hal::GPIO::configure(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin, hal::GPIOInit());
    printf(VERSION);
    while (1) {
        static size_t counter = 0;
        static float fl = 4.2;
        printf("Counter: %d\n", ++counter);
        printf("Float Counter: %f\n", ++fl);
        hal::GPIO::togglePin(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin);
        HAL_Delay(PARAMS_BLINK_RATE_MS);
    }
}
