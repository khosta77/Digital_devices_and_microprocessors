#ifndef STEPAN_STM32F4_FLASH_H_
#define STERAN_STM32F4_FLASH_H_

#include "../system/include/cmsis/stm32f4xx.h"

#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define STP_FLASH_WHILE_BSY()       { while (FLASH->SR & FLASH_SR_BSY){} }
#define STP_SIZE(data_type, size)	(sizeof(data_type) * size)
#define STP_SIZE_OF_ARRAY(array)	(sizeof(array) / sizeof(array[0]))
#define STP_CLEAR_ARRAY(array)		memset(array, 0, sizeof(array))

#define START_ADDRESS 	0x0800C000 	//	(FLASH_BASE + 48*1024)


/* по идеи и без будет работать и без*/
void stp_flash_init();

void stp_flash_unlock();
void stp_flash_lock();

void stp_flash_erase(uint32_t sector);
uint32_t stp_flash_sector_size(uint32_t sector);

void stp_flash_write_8(uint32_t address, const uint8_t *dataBuffer, uint32_t size);
void stp_flash_write_16(uint32_t address, const uint16_t *dataBuffer, uint32_t size);
void stp_flash_write_32(uint32_t address, const uint32_t *dataBuffer, uint32_t size);

void stp_flash_read_8(uint32_t address, uint8_t *buffer, uint32_t size);
void stp_flash_read_16(uint32_t address, uint16_t *buffer, uint32_t size);
void stp_flash_read_32(uint32_t address, uint32_t *buffer, uint32_t size);

/* // Пример использования
stp_flash_init();
stp_flash_erase(3);
const uint32_t SIZE = 254;
uint32|16|8_t arr1[SIZE];
for (uint32_t i = 0; i < SIZE; ++i)
    arr1[i] = (i + 1);


stp_flash_write_32|16|8(START_ADDRESS, arr1, STP_SIZE_OF_ARRAY(arr1));
uint32|16|8_t arr2[SIZE];
stp_flash_read_32|16|8(START_ADDRESS, arr2, STP_SIZE_OF_ARRAY(arr2));
for (uint32_t i = 0; i < SIZE; i++) {
	trace_printf("error %u %u %u\n", i, *(arr2 + i), *(arr1 + i));
...
stp_flash_lock();
 * */


#endif // STEPAN_STM32F4_FLASH_H_
