#ifndef KOMARU_TOUCH_H
#define KOMARU_TOUCH_H

typedef struct {
    int x, y;
    int pressed;
    int id;
} touch_event_t;

int komaru_touch_init(void);
void komaru_touch_register_callback(void (*cb)(touch_event_t*));
void komaru_touch_start(void);
void komaru_touch_stop(void);

#endif
