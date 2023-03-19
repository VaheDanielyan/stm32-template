#include <gpio.h>

bool hal::GPIO::
readPin(GPIO_t instance, GPIO_Pin_t pin)
{
    return HAL_GPIO_ReadPin(instance, pin) == GPIO_PIN_SET;
}

void hal::GPIO::
writePin(GPIO_t instance, GPIO_Pin_t pin, bool state)
{
    HAL_GPIO_WritePin(instance, pin, state ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void hal::GPIO::
togglePin(GPIO_t instance, GPIO_Pin_t pin)
{
    HAL_GPIO_TogglePin(instance, pin);
}

void hal::GPIO::
configure(GPIO_t instance, GPIO_Pin_t pin, hal::GPIOInit init)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    // Reset State
    HAL_GPIO_WritePin(instance, pin, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = pin;
    using hal::GPIO;
    switch (init._mode) {
        case Mode::INPUT: {
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            break;
        }
        case Mode::OUTPUT_PUSH_PULL: {
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
            break;
        }
        case Mode::OUTPUT_OPEN_DRAIN: {
            GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
            break;
        }
        case Mode::ANALOG: {
            GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
            break;
        }
        default: break;
    }
    switch (init._pull) {
        case Pull::NOPULL: {
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            break;
        }
        case Pull::PULLUP: {
            GPIO_InitStruct.Pull = GPIO_PULLUP;
            break;
        }
        case Pull::PULLDOWN: {
            GPIO_InitStruct.Pull = GPIO_PULLDOWN;
            break;
        }
        default: break;
    }
    switch(init._speed) {
        case Speed::LOW: {
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
            break;
        }
        case Speed::MEDIUM: {
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
            break;
        }
        case Speed::HIGH: {
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            break;
        }
        default: break;
    }
    HAL_GPIO_Init(instance, &GPIO_InitStruct);
}

void hal::GPIO::
enableGPIOClock(GPIO_t instance) 
{

#ifdef GPIOA
    if (instance == GPIOA) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    }
#endif
#ifdef GPIOB
    else if (instance == GPIOB) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    }
#endif
    else if (instance == GPIOC) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    }
#ifdef GPIOD
    else if (instance == GPIOD) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    }
#endif
#ifdef GPIOE
    else if (instance == GPIOE) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    }
#endif
#ifdef GPIOF
    else if (instance == GPIOF) {
        __HAL_RCC_GPIOF_CLK_ENABLE();
    }
#endif
#ifdef GPIOG
    else if (instance == GPIOG) {
        __HAL_RCC_GPIOG_CLK_ENABLE();
    }
#endif
#ifdef GPIOH
    else if (instance == GPIOH) {
        __HAL_RCC_GPIOH_CLK_ENABLE();
    }
#endif
#ifdef GPIOI
    else if (instance == GPIOI) {
        __HAL_RCC_GPIOI_CLK_ENABLE();
    }
#endif
#ifdef GPIOJ
    else if (instance == GPIOJ) {
        __HAL_RCC_GPIOJ_CLK_ENABLE();
    }
#endif
#ifdef GPIOK
    else if (instance == GPIOK) {
        __HAL_RCC_GPIOK_CLK_ENABLE();
    }
#endif
    else {
        void(0);
    }
}

