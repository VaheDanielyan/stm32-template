#include <bsp.h>
#include <params.h>

/* HAL */
#include <gpio.h>

/* Utils */
#include <crc.h>

/* Drivers */
#include <dummy.h>

void bsp_main()
{
    hal::GPIO::configure(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin, hal::GPIOInit());
    while (1) {
        hal::GPIO::togglePin(LED_BUILTIN_GPIO_Port, LED_BUILTIN_Pin);
        HAL_Delay(PARAMS_BLINK_RATE_MS);
    }
}
