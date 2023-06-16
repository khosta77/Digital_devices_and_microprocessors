#include "stepan_stm32f4_gpio.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Инициализация
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* @breif stp_init_moder_gpio - Функция инициаллизации пина, на вывод
 * @param 
 *  GPIO - порт
 *  pin - пин
 *  mode  - мод, 0x1, 0x2, 0x3. Передавать 0x1
 * */
void stp_init_moder_gpio(GPIO_TypeDef *GPIO, uint16_t pin, uint16_t mode) {
    GPIO->MODER |= (mode << (2 * pin));
}

/* @breif stp_init_idr_gpio - Функция иницалищации пина на считывание(не аналоговое)
 * @param 
 *  GPIO - порт
 *  pin - пин 
 * */
void stp_init_idr_gpio(GPIO_TypeDef *GPIO, uint16_t pin) {
    GPIO->IDR |= (0x1 << pin);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////    Действие
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* @breif stp_write_to_pin - записать значение(0 или 1) в пин
 * @param 
 *  GPIO - порт
 *  pin - пин 
 *  value - значение 
 * */
void stp_write_to_pin(GPIO_TypeDef *GPIO, uint16_t pin, uint16_t value) {
    if(value) {
		GPIO->ODR |= (0x1 << pin);
    } else {
		GPIO->ODR &= ~(0x1 << pin); 
    }
}

/* @breif stp_read_from_pin - считывает логическую 1 с пина
 * @param
 *  GPIO - порт
 *  pin - пин
 * */
int16_t stp_read_from_pin(GPIO_TypeDef *GPIO, uint16_t pin) {
    return (((GPIO->IDR) >> pin) & 0x00000001);
}


