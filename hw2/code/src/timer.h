#ifndef TIMER_H_
#define TIMER_H_

#include "stepan_stm32f4_hal.h"


// Таймер
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);

void TIM2_for_blue_init();
void TIM3_for_grean_init();


#endif // TIMER_H_
