#ifndef STEPAN_STM32F4_GPIO_H_
#define STERAN_STM32F4_GPIO_H_

#include "../system/include/cmsis/stm32f4xx.h"

void stp_init_moder_gpio(GPIO_TypeDef *GPIO, uint16_t pin, uint16_t mode);
void stp_init_idr_gpio(GPIO_TypeDef *GPIO, uint16_t pin);
void stp_write_to_pin(GPIO_TypeDef *GPIO, uint16_t pin, uint16_t value);
int16_t stp_read_from_pin(GPIO_TypeDef *GPIO, uint16_t pin);

#endif // STEPAN_STM32F4_GPIO_H_
