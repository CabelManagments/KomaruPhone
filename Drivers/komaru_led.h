#ifndef KOMARU_LED_H
#define KOMARU_LED_H

void komaru_led_init(void);
void komaru_led_set(int on);
void komaru_led_blink(int times, int delay_ms);
int komaru_led_get(void);

#endif
