#ifndef GPIO_H
#define GPIO_H

#include <bsp.h>

typedef GPIO_TypeDef* GPIO_t;
typedef uint16_t GPIO_Pin_t;

namespace hal {

enum class Mode {
    INPUT,
    OUTPUT_PUSH_PULL,
    OUTPUT_OPEN_DRAIN,
    ANALOG
};

enum class Pull {
    NOPULL,
    PULLUP,
    PULLDOWN
};

enum class Speed {
    LOW,
    MEDIUM,
    HIGH
};

class GPIOInit {
public:
    GPIOInit(Mode mode = Mode::OUTPUT_PUSH_PULL,
             Pull pull = Pull::NOPULL,
             Speed speed = Speed::LOW)
        : _speed(speed)
        , _pull(pull)
        , _mode(mode) {}
    Speed _speed;
    Pull _pull;
    Mode _mode;
};

class GPIO {

public:     
static void configure(GPIO_t instance, GPIO_Pin_t pin, GPIOInit init);
static bool readPin(GPIO_t instance, GPIO_Pin_t pin);
static void togglePin(GPIO_t instance, GPIO_Pin_t pin);
static void writePin(GPIO_t instance, GPIO_Pin_t pin, bool state);

private:
static void enableGPIOClock(GPIO_t instance);

};

}
#endif /* GPIO_H */
