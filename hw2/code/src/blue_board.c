#include "blue_board.h"

void blue_board_init() {
    blick_c(RED);
    TIM2_for_blue_init();
}

void blue_board_loop() {
    uint8_t df_bus[SIZE];
    uint8_t df_con[SIZE];
    uint16_t size_bus = SIZE;
    uint16_t size_con = 0;
    
    for (uint16_t i = 0; i < size_bus; i++) {
        df_bus[i] = (i % 254);
    }

    uint32_t mrk_button_on = 0;
    uint32_t time_click = 0;

    while (1) {
        if (btn_click() == 1) {
            if (mrk_button_on == 0) {
                // Делаем действие при нажатии на кнопку
                blick_c(ORANGE);
                parallel_write(&df_bus[0], size_bus);
                blick_c(ORANGE);
                mrk_button_on = 1;
            }
            ++time_click;
        } else {
            time_click = 0;
            mrk_button_on = 0;
        }
        
        if (time_click >= LONG_CLICK) {
            // Делаем действие при ДОЛГОМ нажатии
            blick_c(GREAN);
            uint8_t buffer_df_con[SIZE];
            stp_flash_unlock();
            stp_flash_read_8(START_ADDRESS, buffer_df_con, SIZE);
            stp_flash_lock();
            for (uint16_t i = 0; i < SIZE; i++) {
                if (df_bus[i] != buffer_df_con[i]) {
                   blick_c(RED); 
                }
            }
        }
        size_con = serial_read(&df_con[0]);
        if (size_con != 0x0) {
            blick_c(RED);
            stp_flash_unlock();
            stp_flash_erase(3);
            stp_flash_write_8(START_ADDRESS, df_con, size_con);
            stp_flash_lock();
        }

    }
}


