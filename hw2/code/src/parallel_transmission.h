#ifndef PARALLEL_TRANSMISSION_H_
#define PARALLEL_TRANSMISSION_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "stepan_stm32f4_hal.h"
#include "stepan_stm32f4_bus.h"

#define RCC_EN_GREAN() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; }
#define GPIO_EN_GREAN GPIOA
#define PIN_EN_GREAN 7

#define RCC_RD_GREAN() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; }
#define GPIO_RD_GREAN GPIOA
#define PIN_RD_GREAN 6

#define RCC_EN_BLUE() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; }
#define GPIO_EN_BLUE GPIOA
#define PIN_EN_BLUE  5

#define RCC_RD_BLUE() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;}
#define GPIO_RD_BLUE GPIOA
#define PIN_RD_BLUE  4

#define BUS_RD_RCC() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN; }
#define BUS_RD_GPIO GPIOE
#define BUS_RD_PIN_S 7
#define BUS_RD_PIN_E 15

#define BUS_WT_RCC() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; }
#define BUS_WT_GPIO GPIOD
#define BUS_WT_PIN_S 0
#define BUS_WT_PIN_E 8

void parallel_init();
void parallel_write(uint8_t *df, const uint16_t size);
uint16_t parallel_read(uint8_t *df);

#endif // PARALLEL_TRANSMISSION_H_
