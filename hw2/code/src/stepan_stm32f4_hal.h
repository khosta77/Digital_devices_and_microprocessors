#ifndef STEPAN_STM32F4_HAL_H_
#define STERAN_STM32F4_HAL_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include "stepan_stm32f4_gpio.h"
#include "stepan_stm32f4_flash.h"

#define RCC_INIT_GPIOA() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define RCC_INIT_GPIOB() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)
#define RCC_INIT_GPIOC() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define RCC_INIT_GPIOD() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)
#define RCC_INIT_GPIOE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN)
#define RCC_INIT_GPIOF() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN)
#define RCC_INIT_GPIOG() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN)
#define RCC_INIT_GPIOH() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN)
#define RCC_INIT_GPIOI() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN)

#define GREAN  12
#define ORANGE 13
#define RED    14
#define BLUE   15

void blick();
void blick_c(uint16_t color);
void stupid_delay();
void delay(const int COUNT);

#endif // STEPAN_STM32F4_HAL_H_
