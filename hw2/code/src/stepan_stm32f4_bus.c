#include "stepan_stm32f4_bus.h"


void stp_bus_init(Bus_Line *Bus, GPIO_TypeDef *GPIO, uint16_t _pin_start, uint16_t _pin_end, uint8_t _init) {
    Bus->GPIO = GPIO;
    Bus->_pin_s = _pin_start;
    Bus->_pin_e = _pin_end;
    for (int i = Bus->_pin_s; i < Bus->_pin_e; ++i) {
        switch (_init) {
            case BUS_INIT_MODER: {
                stp_init_moder_gpio(Bus->GPIO, i, 0x1);
                break;
            }
            case BUS_INIT_IDR: {
                stp_init_idr_gpio(Bus->GPIO, i);
                break;
            }
        };
    }
}

void stp_bus_write_to_pins(Bus_Line *Bus, uint16_t pos, int16_t value) {
    stp_write_to_pin(Bus->GPIO, pos, value);
}

int16_t stp_bus_read_from_pins(Bus_Line *Bus, uint16_t pos) {
    return stp_read_from_pin(Bus->GPIO, pos);
}

void stp_bus_out(Bus_Line *Bus, uint8_t value) {
    const int _size_value = (Bus->_pin_e - Bus->_pin_s);
    for (int i = Bus->_pin_s, j = 0; i < Bus->_pin_e && j < _size_value; ++i, ++j) {
        if ((value & (1 << j)) == 0) {
            stp_bus_write_to_pins(Bus, i, 0);
        } else {
            stp_bus_write_to_pins(Bus, i, 1);
        }
    }
}

uint8_t stp_bus_read(Bus_Line *Bus) {
    uint8_t _num = 0x00;
    const int _size_value = (Bus->_pin_e - Bus->_pin_s) * 10;
    for (int i = Bus->_pin_s, j = 0; i < Bus->_pin_e && j < _size_value; ++i, ++j) {
        _num |= (stp_bus_read_from_pins(Bus, i) <<  j);
    }
    return _num;
}


