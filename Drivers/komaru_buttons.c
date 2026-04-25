// komaru_buttons.c
#include <linux/gpio.h>

#define BTN_PWR 17
#define BTN_VOLUP 27
#define BTN_VOLDOWN 22
#define BTN_PROG 23

void button_init() {
    gpio_request(BTN_PWR, "btn_power");
    gpio_direction_input(BTN_PWR);
    
    gpio_request(BTN_VOLUP, "btn_volup");
    gpio_direction_input(BTN_VOLUP);
    // ... аналогично для остальных
}

int read_buttons() {
    int state = 0;
    state |= (gpio_get_value(BTN_PWR) ? 0 : 1) << 0;
    state |= (gpio_get_value(BTN_VOLUP) ? 0 : 1) << 1;
    state |= (gpio_get_value(BTN_VOLDOWN) ? 0 : 1) << 2;
    state |= (gpio_get_value(BTN_PROG) ? 0 : 1) << 3;
    return state;
}
