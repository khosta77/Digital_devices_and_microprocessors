#include "serial_transmission.h"

const int serial_delay_in = 600;
const int serial_delay_freq = 800;

static void serial_init_transmitter() {
   RCC_D_SEND_GREAN();
   GPIO_D_SEND_GREAN->MODER |= (0x1 << (2 * PIN_D_SEND_GREAN));
   GPIO_D_SEND_GREAN->ODR |= (0x1 << PIN_D_SEND_GREAN);
   RCC_D_OUT_GREAN();
   GPIO_D_OUT_GREAN->MODER |= (0x1 << (2 * PIN_D_OUT_GREAN));
   GPIO_D_OUT_GREAN->ODR |= (0x1 << PIN_D_OUT_GREAN);
}

static void serial_init_receiver() {
   RCC_D_SEND_BLUE();
//   GPIO_D_SEND_BLUE->MODER |= (0x1 << (2 * PIN_D_SEND_BLUE));
   GPIO_D_SEND_BLUE->IDR |= (0x1 << PIN_D_SEND_BLUE);
   RCC_D_OUT_BLUE();
//   GPIO_D_OUT_BLUE->MODER |= (0x1 << (2 * PIN_D_OUT_BLUE));
   GPIO_D_OUT_BLUE->IDR |= (0x1 << PIN_D_OUT_BLUE);
}

void serial_init() {
    serial_init_transmitter();
    serial_init_receiver();
}

void serial_write(uint8_t *df, const uint16_t size) {
    // 0. Проверка на ноль
    if (size == 0)
        return;

    // 1. Ставим в ноль бит записи
    GPIO_D_SEND_GREAN->ODR &= ~(0x1 << PIN_D_SEND_GREAN);
    for (int t = 0; t < serial_delay_in; t++);

    // 2. Начинаем последовательную запись
    for (uint16_t i = 0; i < size; i++) {
        for (int j = 0; j < 8; j++) {
            if ((*(df + i) & (1 << j)) == 0)
                GPIO_D_OUT_GREAN->ODR &= ~(0x1 << PIN_D_OUT_GREAN);
            else
                GPIO_D_OUT_GREAN->ODR |= (0x1 << PIN_D_OUT_GREAN);
            for (int t = 0; t < serial_delay_freq; t++);
        }
    }

    // 3. Ставим в единицу бит записи, тем самым отключая запись
    GPIO_D_SEND_GREAN->ODR |= (0x1 << PIN_D_SEND_GREAN);
}

uint16_t serial_read(uint8_t *df) {
    // 0. Ожидание начала записи
    if (STATUS_POS_SEND(1))
        return 0x0;


    uint16_t size = 0x0;      // Размер массива
    uint8_t buffer_df[2048];  // Буферный массив
    for (int t = 0; t < serial_delay_in; t++);
    if (STATUS_POS_SEND(1))
        return 0x0;

    // 1. Проверяем открыти ли канал чтения
    for (; STATUS_POS_SEND(0); size++) {
        for (int i = 0; i < 8; i++) {
            if (STATUS_POS_OUT(1))
                buffer_df[size] |= (0x1 << i);
            else
                buffer_df[size] &= ~(0x1 << i);
            for (int t = 0; t < serial_delay_freq; t++);
        }
    }
    
    // 2. Переводим данные из одного массива в другой
    if (size == 0)
        return 0;
    memcpy(df, &buffer_df[0], (size * sizeof(uint8_t)));
    return size;
}


