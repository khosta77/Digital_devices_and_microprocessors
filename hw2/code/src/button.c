#include "button.h"


void Button_init() {
    // 1. Включили тактирование GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // 2. Настройка перефирии
//    GPIOA->MODER |= (0x1 << (2 * PIN_BUTTON));
    GPIOA->IDR |= (0x1 << PIN_BUTTON);
}

int btn_click() {
    return ((GPIOA->IDR & (0x1 << PIN_BUTTON)) == 1);
}


