#include "timer.h"

void TIM2_IRQHandler(void) {
    TIM2->SR &= ~TIM_SR_UIF;
    GPIOD->ODR ^= GPIO_ODR_OD15;
}

void TIM3_IRQHandler(void) {
    TIM3->SR &= ~TIM_SR_UIF;
    GPIOD->ODR ^= GPIO_ODR_OD12;
}

void TIM2_for_blue_init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->ARR = 8000;
	TIM2->PSC = 50;
	TIM2->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority(TIM2_IRQn, 2);
	TIM2->CR1 |= TIM_CR1_CEN;
}

void TIM3_for_grean_init() {
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	TIM3->ARR = 8000;
	TIM3->PSC = 50;
	TIM3->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_SetPriority(TIM3_IRQn, 2);
	TIM3->CR1 |= TIM_CR1_CEN;
}


