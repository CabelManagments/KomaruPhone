#include "komaru_led.h"
#include <stdio.h>
#include <stdlib.h>

static int led_state = 0;

void komaru_led_init(void) {
    system("echo 0 > /sys/class/leds/led0/brightness 2>/dev/null");
}

void komaru_led_set(int on) {
    led_state = on;
    system(on ? "echo 1 > /sys/class/leds/led0/brightness" : "echo 0 > /sys/class/leds/led0/brightness");
}

void komaru_led_blink(int times, int delay_ms) {
    for(int i = 0; i < times; i++) {
        komaru_led_set(1);
        usleep(delay_ms * 1000);
        komaru_led_set(0);
        if(i < times - 1) usleep(delay_ms * 1000);
    }
}

int komaru_led_get(void) { return led_state; }
