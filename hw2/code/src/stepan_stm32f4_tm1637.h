#ifndef STEPAN_STM32F4_TM1637_H_
#define STERAN_STM32F4_TM1637_H_

#include "../system/include/cmsis/stm32f4xx.h"

/*  Для удобства можно перевернуть вывод на индикаторы
 * */
#define STP_TM1637_FLIP_OVER (1)

/*  Макрсо включения тактирования, надо будет редактировать, если другой GPIO выбран
 * */ // ----------------------------------------------------->
#define STP_TM1637_RCC_INIT() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)

#define STP_TM1637_GPIO_CLK (GPIOB)
#define STP_TM1637_PIN_CLK (5)
#define STP_TM1637_GPIO_DIO (GPIOB)
#define STP_TM1637_PIN_DIO (7)

/* Инициализация пинов */
#define STP_TM1637_CLK_MODER() (GPIOB->MODER |= GPIO_MODER_MODER5_0)
#define STP_TM1637_DIO_MODER() (GPIOB->MODER |= GPIO_MODER_MODER7_0)

/* Макрсоы действия */
#define STP_TM1637_CLK_HIGH() (GPIOB->ODR |= GPIO_ODR_OD5)
#define STP_TM1637_CLK_LOW()  (GPIOB->ODR &= ~GPIO_ODR_OD5)
#define STP_TM1637_DIO_HIGH() (GPIOB->ODR |= GPIO_ODR_OD7)
#define STP_TM1637_DIO_LOW()  (GPIOB->ODR &= ~GPIO_ODR_OD7)

/* массив чисел, если надо добавить новые значения, то схема ниже */
extern const char segmentMap[];


#define STP_TM1637_DELAY_START_STOP() { for (unsigned int i = 0; i < 2; ++i); }
#define STP_TM1637_DELAY_READ() { for (unsigned int i = 0; i < 5; ++i); }
#define STP_TM1637_DELAY_WRITE() { for (unsigned int i = 0; i < 3; ++i); }

/* Запустить действие на TM1637 */
#define STP_TM1637_START() { \
    STP_TM1637_CLK_HIGH(); \
    STP_TM1637_DIO_HIGH(); \
    STP_TM1637_DELAY_START_STOP(); \
    STP_TM1637_DIO_LOW(); \
}

/* Остановить действие на TM1637 */
#define STP_TM1637_STOP() { \
    STP_TM1637_CLK_LOW(); \
    STP_TM1637_DELAY_START_STOP(); \
    STP_TM1637_DIO_LOW(); \
    STP_TM1637_DELAY_START_STOP(); \
    STP_TM1637_CLK_HIGH(); \
    STP_TM1637_DELAY_START_STOP(); \
    STP_TM1637_DIO_HIGH(); \
}

/* Проверить коректность работы TM1637 */
#define STP_TM1637_READ() { \
    STP_TM1637_CLK_LOW(); \
    STP_TM1637_DELAY_READ(); \
    STP_TM1637_CLK_HIGH(); \
    STP_TM1637_DELAY_START_STOP(); \
    STP_TM1637_CLK_LOW(); \
}

void stp_tm1637_init();  
void stp_tm1637_display(int v, int displaySeparator);
void stp_tm1637_setBrightness(char brightness);



#endif // STEPAN_STM32F4_TIM1637_H_
