#ifndef BLUE_BOARD_H_
#define BLUE_BOARD_H_

#include "stepan_stm32f4_hal.h"

#include "parallel_transmission.h"
#include "serial_transmission.h"
#include "constant.h"
#include "timer.h"
#include "color.h"
#include "button.h"

void blue_board_init();
void blue_board_loop();

#endif // BLUE_BOARD_H_
