#include "stepan_stm32f4_flash.h"

static void stp_flash_write(uint32_t address, uint8_t data) {
    //// Запись данных в одну клетку
    // 1. Разрешаем программирование
    FLASH->CR |= FLASH_CR_PG;

    // 2. Записываем в ячейку данных один байт
    *(uint8_t *)address = data;

    // 3. Ждем пока запись завершится
    STP_FLASH_WHILE_BSY();
    
    // 4. Запрещаем программирование
    FLASH->CR &= ~FLASH_CR_PG;
}

static void stp_flash_write_buffer(uint32_t address, const uint8_t * dataBuffer, uint32_t size) {
    //// Запись данных в одну ячейку
	// 1. Разблокируем память для записи данных
    stp_flash_unlock();
    
    // 2. Подождем пока произойдет разблокировка
    STP_FLASH_WHILE_BSY();

    // 3. Цикл записи
    while (size >= sizeof(uint8_t)) {
    	stp_flash_write(address, *(const uint8_t *)dataBuffer);
        address += sizeof(uint8_t);
        dataBuffer += sizeof(uint8_t);
        size -= sizeof(uint8_t);
    }

    // 4. Заблокируем память. Признак хорошего тона
    stp_flash_lock();
}

void stp_flash_init() {
	//// Конфигурация FLASH
	// 1. Очистка флагов
    FLASH->ACR = 0;

    // 2. Установка задержки (5 секунд)
	FLASH->ACR |= FLASH_ACR_LATENCY_5WS;  // (5 <<  0);
	
    // 3. Включаем кэш команд
    FLASH->ACR |= FLASH_ACR_ICEN;  //(1 <<  9);
	
    // 4. Включаем кэш команд
    FLASH->ACR |= FLASH_ACR_DCEN;  //(1 << 10);
	
    // 5. PLL Выбран в качестве системных часов \
    // если не работает, убрать макрос.
    RCC->CFGR |= RCC_CFGR_SW_1;  //(2 <<  0);

    // 6. Ждем пока PLL включится
	while ((RCC->CFGR & 0x0F) != 0x0A);
}

void stp_flash_unlock() {
    //// Разблокировка памяти
    if (FLASH->CR & FLASH_CR_LOCK) {
        FLASH->KEYR = 0x45670123;
        FLASH->KEYR = 0xCDEF89AB;
    }
}

void stp_flash_lock() {
    //// Блокировка памяти
    FLASH->CR |= FLASH_CR_LOCK;
}

void stp_flash_erase(uint32_t sector) {
    //// Очистка сектора
    // 1. Разблокировка памяти для работы с ней
	stp_flash_unlock();

    // 2. Ждем пока она разблокируется
	STP_FLASH_WHILE_BSY();

    // 3. Защита от дурака, если передали большое число
    sector = sector & 0x0F;
    
    // 4. Очистка сектора
    FLASH->CR |= FLASH_CR_SER;	// Sector Erase Flag
    FLASH->CR |= (sector << 3);	// Sector Number to SNB[3:0]
    FLASH->CR |= FLASH_CR_STRT;	// Sector Erase Start

    // 5. Ждем пока сектор очистится
    STP_FLASH_WHILE_BSY();

    // 6. Выключаем флаг работы с сектором
    FLASH->CR &= ~FLASH_CR_SER;

    // 7. Блокируем память
    stp_flash_lock();
}

uint32_t stp_flash_sector_size(uint32_t sector) {
    //// получить какой то адрес сектора, честно хз за чем эта функция (Legacy)
    if (sector >= 0 && sector <= 3) {
        return (16 * 1024);
    } else if (sector == 4) {
        return (64 * 1024);
    } else if (sector >= 5 && sector <= 11) {
        return (128 * 1024);
    }
    return 0;
}

// Запись данных во flash
void stp_flash_write_8(uint32_t address, const uint8_t *dataBuffer, uint32_t size) {
	stp_flash_write_buffer(address, dataBuffer, size);
}

void stp_flash_write_16(uint32_t address, const uint16_t *dataBuffer, uint32_t size) {
    uint8_t buffer[(sizeof(uint16_t) * size)];
    memcpy(buffer, dataBuffer, (sizeof(uint16_t) * size));
    stp_flash_write_buffer(address, buffer, (sizeof(uint16_t) * size));
}

void stp_flash_write_32(uint32_t address, const uint32_t *dataBuffer, uint32_t size) {
	uint8_t buffer[(sizeof(uint32_t) * size)];
	memcpy(buffer, dataBuffer, (sizeof(uint32_t) * size));
	stp_flash_write_buffer(address, buffer, (sizeof(uint32_t) * size));
}

// Чтение данных из flash
void stp_flash_read_8(uint32_t address, uint8_t *buffer, uint32_t size) {
    memcpy(buffer, (uint8_t*) address, size);
}

void stp_flash_read_16(uint32_t address, uint16_t *buffer, uint32_t size) {
	uint8_t char_buffer[(sizeof(uint16_t) * size)];
	memcpy(char_buffer, (uint8_t*) address, (sizeof(uint16_t) * size));
	memcpy(buffer, char_buffer, (size * sizeof(uint16_t)));
}

void stp_flash_read_32(uint32_t address, uint32_t *buffer, uint32_t size) {
	uint8_t char_buffer[(sizeof(uint32_t) * size)];
	memcpy(char_buffer, (uint8_t*) address, (sizeof(uint32_t) * size));
	memcpy(buffer, char_buffer, (size * sizeof(uint32_t)));
}


