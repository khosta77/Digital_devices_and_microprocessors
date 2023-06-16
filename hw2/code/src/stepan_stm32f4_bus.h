#ifndef STEPAN_STM32F4_BUS_H_
#define STERAN_STM32F4_BUS_H_

#include "../system/include/cmsis/stm32f4xx.h"
#include "stepan_stm32f4_gpio.h"

#define BUS_INIT_MODER 0
#define BUS_INIT_IDR 1


typedef struct {
    GPIO_TypeDef *GPIO;
    int16_t _pin_s;
    int16_t _pin_e;
} Bus_Line;

void stp_bus_init(Bus_Line *Bus, GPIO_TypeDef *GPIO, uint16_t _pin_start, uint16_t _pin_end, uint8_t _init);
void stp_bus_write_to_pins(Bus_Line *Bus, uint16_t pos, int16_t value);
int16_t stp_bus_read_from_pins(Bus_Line *Bus, uint16_t pos);


// чтение
void stp_bus_out(Bus_Line *Bus, uint8_t value);
uint8_t stp_bus_read(Bus_Line *Bus);


#endif // STEPAN_STM32F4_BUS_H_
