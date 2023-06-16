#ifndef BUTTON_H_
#define BUTTON_H_

#include "stepan_stm32f4_hal.h"


// Инициализируем кнопку
#define PIN_BUTTON 0 // GPIOA

void Button_init();
int btn_click();


#endif // BUTTON_H_
