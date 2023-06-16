#include "stepan_stm32f4_hal.h"

void blick() {
    stp_write_to_pin(GPIOD, 12, 1);
    stupid_delay();
    stp_write_to_pin(GPIOD, 12, 0);
    stupid_delay();
}

void blick_c(uint16_t color) {
    stp_write_to_pin(GPIOD, color, 1);
    stupid_delay();
    stp_write_to_pin(GPIOD, color, 0);
    stupid_delay();
}

void stupid_delay() {
    for(int i = 0; i < 1000000; i++);
}

void delay(const int COUNT) {
    for (int i = 0; i < COUNT; i++);
}


