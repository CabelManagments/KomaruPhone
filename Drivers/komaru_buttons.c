// komaru_buttons.c
#include "komaru_buttons.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>      // <-- добавить
#include <sys/types.h>  // <-- добавить
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
// Добавить в конец файла

typedef struct {
    int pin;
    int last_state;
    unsigned long last_press_time;
    int long_press_triggered;
} button_t;

static button_t buttons[4] = {
    {PIN_POWER, 1, 0, 0},
    {PIN_VOLUP, 1, 0, 0},
    {PIN_VOLDOWN, 1, 0, 0},
    {PIN_PROG, 1, 0, 0}
};

#define DEBOUNCE_MS 50
#define LONG_PRESS_MS 1000

void komaru_buttons_debounce_loop(void (*on_press)(int, int)) {
    static unsigned long last_check = 0;
    unsigned long now = get_timestamp_ms(); // нужна функция времени
    
    if(now - last_check < DEBOUNCE_MS) return;
    last_check = now;
    
    for(int i = 0; i < 4; i++) {
        int current = gpio_read(buttons[i].pin);
        if(current != buttons[i].last_state) {
            buttons[i].last_state = current;
            if(current == 0) { // нажата
                buttons[i].last_press_time = now;
                buttons[i].long_press_triggered = 0;
            } else { // отпущена
                if(!buttons[i].long_press_triggered) {
                    if(on_press) on_press(i, 0); // короткое нажатие
                }
            }
        }
        
        // long press детект
        if(buttons[i].last_state == 0 && 
           (now - buttons[i].last_press_time) >= LONG_PRESS_MS &&
           !buttons[i].long_press_triggered) {
            buttons[i].long_press_triggered = 1;
            if(on_press) on_press(i, 1); // длинное нажатие
        }
    }
}
