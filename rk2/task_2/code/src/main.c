#include "../system/include/cmsis/stm32f4xx.h"

#define PIN_ANALOG_READ_1 1
#define PIN_ANALOG_READ_2 2
#define PIN_LED_GREAN 12
#define S 1     // длительности импульса в циклах, по умолчанию

#define SIZE 2
uint32_t adc1[SIZE];

void GPIO_init() {
    //// Настройка GPIO
    // 0. Тактирование GPIO
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    // 1. Настраиваем нужный порт на аналоговый режим работы
	GPIOA->MODER |= (GPIO_MODER_MODE0_0 | GPIO_MODER_MODE0_1 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE1_1); 
}

void DMA2_Stream4_IRQHandler(void) {
	if((DMA2->HISR & (DMA_HISR_TCIF4 | DMA_HISR_HTIF4)) == (DMA_HISR_TCIF4 | DMA_HISR_HTIF4)) {
        // Очищаем регистры отвечающие за прерывание.
		DMA2->HIFCR = (DMA_HIFCR_CTCIF4 | DMA_HIFCR_CHTIF4);
	} 
}

void DMA_init() {
    // 0. Включаем DMA2
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    // 1. По таблице выбираем канал 0
    // Так как канал ноль, то бит устанавливать не обезательно
//    DMA2_Stream4->CR &= ~(0x7 << 25);
    
    // 2. Задаем откуда, куда и сколько данных передавать
	DMA2_Stream4->PAR |= (uint32_t)&ADC1->DR;
	DMA2_Stream4->M0AR |= (uint32_t)&adc1;
	DMA2_Stream4->NDTR = SIZE;

    // 3. Настройка
    // 3.1 DMA_SxCR_CIRC - Включаем круговой режим работы
    // 3.2 DMA_SxCR_MINC - Режим увеличения объема памяти
    // 3.3 DMA_SxCR_PSIZE_1 - Длина 32-bit
    // 3.4 DMA_SxCR_MSIZE_1 - Длина 32-bit
    // 3.5 DMA_SxCR_PL_1 - Высокий уровень приоритета, не обезательная скорее всего настройка, 
    //                     добавить если несколько будеь
    // 3.6 DMA_SxCR_TCIE - Прерывания
    DMA2_Stream4->CR = (DMA_SxCR_CIRC | DMA_SxCR_MINC | DMA_SxCR_PSIZE_1 | DMA_SxCR_MSIZE_1 | DMA_SxCR_TCIE);

    // 4. Прерывания
    NVIC_EnableIRQ(DMA2_Stream4_IRQn);
    NVIC_SetPriority(DMA2_Stream4_IRQn, 4);

    // 5. Запуск
	DMA2_Stream4->CR |= DMA_SxCR_EN;
}

void ADC_init(){
    // -1. Инициализировать GPIO
    GPIO_init();

    // 0. Включаем тактирование ADC1
    RCC->APB2ENR = RCC_APB2ENR_ADC1EN;

    // 1. Включаем режим сканирования
    ADC1->CR1 |= ADC_CR1_SCAN;

    // 2. Настройка
    // 2.1 ADC_CR2_ADON - Включение ADC
    // 2.2 ADC_CR2_CONT - Обработка в цикле
    // 2.3 ADC_CR2_EOCS - Завершение выбора преобразования, для DMA
    // 2.4 ADC_CR2_DMA - Работа с DMA
    // 2.5 ADC_CR2_DDS - Тоже для DMA что то
    ADC1->CR2 |= (ADC_CR2_ADON | ADC_CR2_CONT | ADC_CR2_EOCS | ADC_CR2_DMA | ADC_CR2_DDS);

    // 3. Назначаем пины с которых брать анлаоговый сигнал
	ADC1->SQR3 |= ((0 << 0) | (1 << 5));

    // 4. Колличество каналов с которых брать сигнал (L = (n - 1))
	ADC1->SQR1 |= (1 << 20);

    // 5. Включаем DMA
    DMA_init();

    // 6. Запускаем конвертацию
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

void TIM4_IRQHandler(void) {
    // 0. Снимаем маркер прервыания
	TIM4->SR &= ~TIM_SR_UIF;

    // 1. Выключаем таймер для его редактирования
	TIM4->CR1 &= ~TIM_CR1_CEN;
    
    TIM4->PSC = (adc1[0] * 100);
    TIM4->CCR1 = (adc1[1] / 100);

    // 3. Запускаем таймер
    TIM4->CR1 |= TIM_CR1_CEN;
}

void TIM4_init() {
    //// Настраиваем порт светодиода
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    // 0. ШИМ назначается на альтернативную функцию
    GPIOD->MODER |= (0x2 << (2 * PIN_LED_GREAN));
    GPIOD->AFR[1] |= (0x2 << 16);

    //// Настравиваем ШИМ на таймере
    // 0. включаем тактирование нужного таймера
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    // 1. Настраиваем период срабатывания таймера
    TIM4->PSC = 1;
    TIM4->ARR = 100;

    ////  Настраиваем "захват/сравнение
    // 2. Тут включается PWM1, строка OC1M"
    TIM4->CCMR1 |= 0x60;

    // 3. Установка длительности импульса в циклах
    TIM4->CCR1 = 1;

    // 4. Включение CC1
    TIM4->CCER |= 0x1;

    // *. Включаем прерывание
    TIM4->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM4_IRQn);
    NVIC_SetPriority(TIM4_IRQn, 2);

    // 5. Запускаем таймер
    TIM4->CR1 |= TIM_CR1_CEN;
}

void init() {
    ADC_init();
    TIM4_init();
}

int main(void) {
    init();
	while(1);
}


