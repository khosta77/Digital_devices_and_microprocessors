#ifndef GREAN_BOARD_H_
#define GREAN_BOARD_H_

#include "stepan_stm32f4_hal.h"

#include "parallel_transmission.h"
#include "serial_transmission.h"
#include "constant.h"
#include "timer.h"
#include "color.h"
#include "button.h"

void grean_board_init();
void grean_board_loop();

#endif // GREAN_BOARD_H_
