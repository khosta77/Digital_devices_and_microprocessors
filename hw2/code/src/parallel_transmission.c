#include "./parallel_transmission.h"

static Bus_Line bus_w;
static Bus_Line bus_r;

static void parallel_init_transmitter() {
    BUS_WT_RCC();
    stp_bus_init(&bus_w, BUS_WT_GPIO, BUS_WT_PIN_S, BUS_WT_PIN_E, 0);

    RCC_EN_BLUE();
    GPIO_EN_BLUE->MODER |= (0x1 << (2 * PIN_EN_BLUE));
    GPIO_EN_BLUE->ODR &= ~(0x1 << PIN_EN_BLUE);
    
    RCC_RD_BLUE();
//    GPIO_RD_BLUE->MODER |= (0x1 << (2 * PIN_RD_BLUE));
    GPIO_RD_BLUE->IDR |= (0x1 << PIN_RD_BLUE);

    stp_bus_out(&bus_w, 0);
}

static void parallel_init_receiver() {
    BUS_RD_RCC();
    stp_bus_init(&bus_r, BUS_RD_GPIO, BUS_RD_PIN_S, BUS_WT_PIN_E, 1);

    RCC_EN_GREAN();
//    GPIO_EN_GREAN->MODER |= (0x1 << (2 * PIN_EN_GREAN));
    GPIO_EN_GREAN->IDR |= (0x1 << PIN_EN_GREAN);
    
    GPIO_RD_GREAN->MODER |= (0x1 << (2 * PIN_RD_GREAN));
    GPIO_RD_GREAN->ODR &= ~(0x1 << PIN_RD_GREAN);
}

void parallel_init() {
    parallel_init_transmitter();
    parallel_init_receiver();
}

void parallel_write(uint8_t *df, const uint16_t size) {
    GPIO_EN_BLUE->ODR |= (0x1 << PIN_EN_BLUE);
    
    while (stp_read_from_pin(GPIO_RD_BLUE, PIN_RD_BLUE) != 1);
    
    for (uint16_t i = 0; (i < size); i++) {
        stp_bus_out(&bus_w, *(df + i));
        for (int t = 0; t < 60; t++);
    }
    
    GPIO_EN_BLUE->ODR &= ~(0x1 << PIN_EN_BLUE);
    for (int t = 0; t < 50; t++);
    stp_bus_out(&bus_w, 0);
}

uint16_t parallel_read(uint8_t *df) {
    if (stp_read_from_pin(GPIO_EN_GREAN, PIN_EN_GREAN) != 1)
        return 0x00;

    uint16_t size = 0x0;
    uint8_t buffer_df[2048];

    GPIO_RD_GREAN->ODR |= (0x1 << PIN_RD_GREAN);
    for (int t = 0; t < 20; t++);
    
    for (; stp_read_from_pin(GPIO_EN_GREAN, PIN_EN_GREAN) == 1; size++) {
        buffer_df[size] = stp_bus_read(&bus_r);
        for (int t = 0; t < 50; t++);
    }
    memcpy(df, &buffer_df[0], (size * sizeof(uint8_t)));

    GPIO_RD_GREAN->ODR &= ~(0x1 << PIN_RD_GREAN);
    return size;
}


