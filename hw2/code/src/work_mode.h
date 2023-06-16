#ifndef WORK_MODE_H_
#define WORK_MODE_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "stepan_stm32f4_hal.h"

#define RCC_WORK_MODE_IN_GREAN() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; }
#define GPIO_WORK_MODE_IN_GREAN GPIOB
#define PIN_WORK_MODE_IN_GREAN  1

#define RCC_WORK_MODE_OUT_GREAN() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; }
#define GPIO_WORK_MODE_OUT_GREAN GPIOB
#define PIN_WORK_MODE_OUT_GREAN 0

#define RCC_WORK_MODE_IN_BLUE() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
#define GPIO_WORK_MODE_IN_BLUE GPIOC
#define PIN_WORK_MODE_IN_BLUE  1

#define RCC_WORK_MODE_OUT_BLUE() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
#define GPIO_WORK_MODE_OUT_BLUE GPIOC
#define PIN_WORK_MODE_OUT_BLUE 0

void Work_mode_init();
int status_blue();
int status_grean();

#endif // WORK_MODE_H_
