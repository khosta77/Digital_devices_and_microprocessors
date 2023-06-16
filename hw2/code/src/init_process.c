#include "init_process.h"

static void blue_board_launch() {
    if (!status_blue())
        return;
    blue_board_init();
    blue_board_loop();
}

static void grean_board_launch() {
    if (!status_grean())
        return;
    grean_board_init();
    grean_board_loop();
}

static void transmission_init() {
    parallel_init();
    serial_init();
}

void init() {
	SystemCoreClockUpdate();
    transmission_init();
    Work_mode_init();
    Button_init();
    led_init();
}

void process() {
    blue_board_launch();
    grean_board_launch();
}


