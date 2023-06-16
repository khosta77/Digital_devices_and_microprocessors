#ifndef SERIAL_TRANSMISSION_H_
#define SERIAL_TRANSMISSION_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "stepan_stm32f4_gpio.h"
#include "stepan_stm32f4_hal.h"


// Последовательный интефейс
// d_out на зеленой плате
#define RCC_D_OUT_GREAN() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
#define GPIO_D_OUT_GREAN  GPIOC
#define PIN_D_OUT_GREAN  2

// d_send на зеленой плате
#define RCC_D_SEND_GREAN() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
#define GPIO_D_SEND_GREAN GPIOC
#define PIN_D_SEND_GREAN 3

// d_out на голубой плате
#define RCC_D_OUT_BLUE() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
#define GPIO_D_OUT_BLUE GPIOC
#define PIN_D_OUT_BLUE  6

// d_send на голубой плате
#define RCC_D_SEND_BLUE() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; }
#define GPIO_D_SEND_BLUE GPIOC
#define PIN_D_SEND_BLUE 7

#define STATUS_POS_OUT(marker)  ((GPIO_D_OUT_BLUE->IDR & (0x1 << PIN_D_OUT_BLUE)) == marker)
#define STATUS_POS_SEND(marker) ((GPIO_D_SEND_BLUE->IDR & (0x1 << PIN_D_SEND_BLUE)) == marker)

extern const int serial_delay_in;
extern const int serial_delay_freq;

void serial_init();
void serial_write(uint8_t *df, const uint16_t size);
uint16_t serial_read(uint8_t *df);

#endif // SERIAL_TRANSMISSION_H_ 
