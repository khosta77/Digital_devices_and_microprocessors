#ifndef STEPAN_STM32F4_USART_H_
#define STEPAN_STM32F4_USART_H_


#if 0
#define CPU_CLOCK SystemCoreClock
#define MY_BDR 115200

#define MYBRR (CPU_CLOCK / (16 * MY_BDR))

void GPIO_init() {
	// 1. Вкл. тактирование
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	// 2. назначили пины
	GPIOA->MODER |= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);
	// Альтернативные функции
	GPIOA->AFR[0] |= 0x77 << 8;
}

void USART_init() {
	// 1. Вкл тактирование
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// 2. Задали частоту работы
	USART2->BRR = MYBRR;
	// 3. Настроили на чтение и запись
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	// 4. Установили STOP бит
	USART2->CR2 |= (USART_CR2_STOP_1);
	// 5. Вкл USART
	USART2->CR1 |= USART_CR1_UE;
}

/* Чтение */
uint8_t readUSART() {
	uint8_t test_usart2_sr_1 = USART2->SR;
    if ((USART2->SR & USART_SR_RXNE) == USART_SR_RXNE) {
    	return USART2->DR;
    }
    return -1;
}

/* Запись */
uint8_t writeUSART(uint8_t data) {
	uint8_t test_usart2_sr_2 = USART2->SR;
    if ((USART2->SR & USART_SR_TXE) == USART_SR_TXE) {
    	USART2->DR = data;
    	return 0;
    }
    return -1;
}

int main(void) {
	SystemCoreClockUpdate();
	GPIO_init();
	USART_init();
	uint8_t temp = 0x21;
	while(1) {
		writeUSART(temp);
		for (int i = 0; i  < 50; i++);
		uint8_t temp_read = readUSART();
    	trace_printf("temp_read: %u\n", temp_read);
		if (temp_read != 255) {
			temp = ++temp % 254;
		}
	}
}
#endif

#if 0
void USART_init() {
    // 0. Настройка GPIOA
    RCC_INIT_GPIOA();
    GPIOA->MODER |= (GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1);
	GPIOA->AFR[0] |= 0x77 << 8;
	// 1. Вкл тактирование
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	// 2. Задали частоту работы
	USART2->BRR = MYBRR;
	// 3. Настроили на чтение и запись
	USART2->CR1 |= (USART_CR1_TE | USART_CR1_RE);
	// 4. Установили STOP бит
	USART2->CR2 |= (USART_CR2_STOP_1);
	// 5. Вкл USART
	USART2->CR1 |= USART_CR1_UE;
}

/* Чтение */
uint8_t readUSART() {
    if ((USART2->SR & USART_SR_RXNE) == USART_SR_RXNE) {
        return USART2->DR;
    }
    return -1;
}

/* Запись */
uint8_t writeUSART(uint8_t data) {
    if ((USART2->SR & USART_SR_TXE) == USART_SR_TXE) {
    	USART2->DR = data;
    	return 0;
    }
    return 1;
}


#endif

#endif // STEPAN_STM32F4_USART_H_
