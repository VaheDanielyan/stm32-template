#include <bsp.h>
#include <params.h>

/* HAL */
#include <gpio.h>

/* Utils */
#include <crc.h>
#include <swo.h>

/* Drivers */
#include <dummy.h>

#include <stdio.h>

void bsp_main()
{
    swo_init();
    hal::GPIO::configure(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin, hal::GPIOInit());
    while (1) {
        static size_t counter = 0;
        printf("Counter: %d\n", ++counter);
        hal::GPIO::togglePin(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin);
        HAL_Delay(PARAMS_BLINK_RATE_MS);
    }
}
