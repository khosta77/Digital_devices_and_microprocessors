#include "./stepan_stm32f4_tm1637.h"

/* массив чисел, если надо добавить новые значения, то схема ниже */
/*
 *   3
 *   -
 * 2| |4
 *  6-
 * 1| |5
 *  0-
 * Зеркально, если вверх ногами, как обычно, по плате.
 * 7|6543210
 * -+-------
 *
 * */
const char segmentMap[] = {
//   0     1     2     3     4     5     6     7     8     9
#if STP_TM1637_FLIP_OVER
    0x3f, 0x30, 0x5b, 0x79, 0x74, 0x6d, 0x6f, 0x38, 0x7f, 0x7d
#else // Поумолчанию
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
#endif
};


static void stp_tm1637_writeByte(unsigned char b) {
    for (int i = 0; i < 8; ++i) {
        STP_TM1637_CLK_LOW();

        if (b & 0x01)
            STP_TM1637_DIO_HIGH();
        else 
            STP_TM1637_DIO_LOW();
        STP_TM1637_DELAY_WRITE();
        b >>= 1;
    
        STP_TM1637_CLK_HIGH();
        STP_TM1637_DELAY_WRITE();
    }
}

/*  Инициализация, можно задать яроксть, но это излишне
 * */
void stp_tm1637_init(/*const char brightness*/) {  
    // Вкл перефирию 
    STP_TM1637_RCC_INIT();

    // Настраиваем перефирию
    STP_TM1637_CLK_MODER();
    STP_TM1637_DIO_MODER();

    // Устанавливаем яркость
    stp_tm1637_setBrightness(3);
    stp_tm1637_display(0, 0);
}

/* записать 4-рех значное число, положительное 
 * number - число
 * displaySeparator - двоеточие
 * */
void stp_tm1637_display(int number, int displaySeparator) {
    unsigned char digitArr[4];
    for (int i = 0; i < 4; ++i) {
        digitArr[i] = segmentMap[number % 10];
        if (i == 2 && displaySeparator)
            digitArr[i] |= 1 << 7;
        number /= 10;
    }

    STP_TM1637_START();
    stp_tm1637_writeByte(0x40);  // наверное биты отладки какие то
    STP_TM1637_READ();
    STP_TM1637_STOP();
    
    STP_TM1637_START();
    stp_tm1637_writeByte(0xc0);
    STP_TM1637_READ();

    for (int i = 0; i < 4; ++i) {
#if STP_TM1637_FLIP_OVER
        stp_tm1637_writeByte(digitArr[i]);
#else // Поумолчанию
        stp_tm1637_writeByte(digitArr[3 - i]);
#endif
        STP_TM1637_READ();
    }

    STP_TM1637_STOP();
}

/* Установить яркость */
void stp_tm1637_setBrightness(char brightness) {
    STP_TM1637_START();
    stp_tm1637_writeByte(0x87 + brightness);
    STP_TM1637_READ();
    STP_TM1637_STOP();
}


