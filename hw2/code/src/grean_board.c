#include "grean_board.h"

static void button_event(uint32_t *mrk_button_on, uint32_t *time_click, uint8_t *df, uint16_t *size) {
    if (btn_click()) {
        if (*mrk_button_on == 0) {
            // Делаем действие при нажатии на кнопку
            blick_c(ORANGE);
            serial_write(df, *size);
            blick_c(ORANGE);
            *mrk_button_on = 1;
        }
        ++*time_click;
    } else {
        *time_click = 0;
        *mrk_button_on = 0;
    }
}

static void time_up(uint32_t *time_click, uint8_t *df) {
    if (*time_click >= LONG_CLICK) {
        // Делаем действие при ДОЛГОМ нажатии
        blick_c(BLUE);
        uint8_t buffer_df_bus[SIZE];
        stp_flash_unlock();
        stp_flash_read_8(START_ADDRESS, buffer_df_bus, SIZE);
        stp_flash_lock();
        for (uint16_t i = 0; i < SIZE; i++) {
            if (*(df + i) != buffer_df_bus[i]) {
                blick_c(RED); 
            }
        }
    }
}

static void parallel_reads(uint8_t *df, uint16_t *size) {
    *size = parallel_read(df);
    if (*size != 0x0) {
        blick_c(RED);
        stp_flash_unlock();
        stp_flash_erase(3);
        stp_flash_write_8(START_ADDRESS, df, *size);
        stp_flash_lock();
    } 
}

void grean_board_init() {
    blick_c(BLUE);
    TIM3_for_grean_init();
}

void grean_board_loop() {
    uint8_t df_bus[SIZE];
    uint8_t df_con[SIZE];
    uint16_t size_bus = 0;
    uint16_t size_con = SIZE;

    for (uint16_t i = 0; i < size_bus; i++) {
        df_bus[i] = (i % 254);
    }

    uint32_t mrk_button_on = 0;
    uint32_t time_click = 0;

    while (1) {
        button_event(&mrk_button_on, &time_click, &df_con[0], &size_con);
/*
        if (btn_click()) {
            if (mrk_button_on == 0) {
                // Делаем действие при нажатии на кнопку
                blick_c(ORANGE);
                write_con(&df_con[0], size_con);
                blick_c(ORANGE);
                mrk_button_on = 1;
            }
            ++time_click;
        } else {
            time_click = 0;
            mrk_button_on = 0;
        }
*/
        time_up(&time_click, &df_con[0]);
/*
        if (time_click >= LONG_CLICK) {
            // Делаем действие при ДОЛГОМ нажатии
            blick_c(BLUE);
            uint8_t buffer_df_bus[SIZE];
            stp_flash_unlock();
            stp_flash_read_8(START_ADDRESS, buffer_df_bus, SIZE);
            stp_flash_lock();
            for (uint16_t i = 0; i < SIZE; i++) {
                if (df_con[i] != buffer_df_bus[i]) {
                   blick_c(RED); 
                }
            }
        }
*/
        parallel_reads(&df_bus[0], &size_bus);
/*
        size_bus = read_bus(&df_bus[0]);
        if (size_bus != 0x0) {
            blick_c(RED);
            stp_flash_unlock();
            stp_flash_erase(3);
            stp_flash_write_8(START_ADDRESS, df_bus, size_bus);
            stp_flash_lock();
        }
*/
    }
}


