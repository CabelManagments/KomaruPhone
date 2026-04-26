#include "komaru_touch.h"
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int touch_fd = -1;
static touch_event_t last_event = {0};
static void (*touch_callback)(touch_event_t*) = NULL;
static int running = 1;

int komaru_touch_init(void) {
    const char *devices[] = {
        "/dev/input/event0", "/dev/input/event1",
        "/dev/input/event2", "/dev/input/touchscreen0"
    };
    
    for(int i = 0; i < 4; i++) {
        touch_fd = open(devices[i], O_RDONLY);
        if(touch_fd >= 0) {
            printf("Touch found on %s\n", devices[i]);
            break;
        }
    }
    
    return (touch_fd >= 0) ? 0 : -1;
}

void komaru_touch_register_callback(void (*cb)(touch_event_t*)) {
    touch_callback = cb;
}

static void* touch_thread(void *arg) {
    struct input_event ev;
    
    while(running) {
        if(read(touch_fd, &ev, sizeof(ev)) == sizeof(ev)) {
            switch(ev.type) {
                case EV_ABS:
                    if(ev.code == ABS_X) last_event.x = ev.value;
                    if(ev.code == ABS_Y) last_event.y = ev.value;
                    break;
                case EV_KEY:
                    if(ev.code == BTN_TOUCH) {
                        last_event.pressed = ev.value;
                        last_event.id = 0;
                    }
                    break;
                case EV_SYN:
                    if(touch_callback) {
                        touch_callback(&last_event);
                    }
                    break;
            }
        }
        usleep(10000);
    }
    return NULL;
}

void komaru_touch_start(void) {
    pthread_t thread;
    pthread_create(&thread, NULL, touch_thread, NULL);
}

void komaru_touch_stop(void) {
    running = 0;
    if(touch_fd >= 0) close(touch_fd);
}
