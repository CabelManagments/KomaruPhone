#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>

static int touch_fd = -1;
static int touch_x = 0;
static int touch_y = 0;
static int touch_pressed = 0;
static int screen_width = 128;
static int screen_height = 64;

typedef struct {
    int x;
    int y;
    int pressed;
    int id;
} touch_event_t;

#define MAX_TOUCHES 5
static touch_event_t touches[MAX_TOUCHES];

static void (*touch_callback)(touch_event_t *event) = NULL;

int komaru_touch_init(void) {
    // Пробуем найти устройство тачскрина
    const char *devices[] = {
        "/dev/input/event0", "/dev/input/event1",
        "/dev/input/event2", "/dev/input/touchscreen0"
    };
    
    for(int i = 0; i < 4; i++) {
        touch_fd = open(devices[i], O_RDONLY | O_NONBLOCK);
        if(touch_fd >= 0) {
            printf("Touch found on %s\n", devices[i]);
            break;
        }
    }
    
    if(touch_fd < 0) return -1;
    
    for(int i = 0; i < MAX_TOUCHES; i++) {
        touches[i].id = -1;
    }
    
    return 0;
}

void komaru_touch_register_callback(void (*cb)(touch_event_t*)) {
    touch_callback = cb;
}

void* komaru_touch_thread(void *arg) {
    struct input_event ev;
    
    while(1) {
        if(read(touch_fd, &ev, sizeof(ev)) == sizeof(ev)) {
            touch_event_t event = {0};
            event.id = 0;
            
            switch(ev.type) {
                case EV_ABS:
                    if(ev.code == ABS_X) {
                        touch_x = ev.value * screen_width / 4096;
                        if(touch_x < 0) touch_x = 0;
                        if(touch_x >= screen_width) touch_x = screen_width - 1;
                        event.x = touch_x;
                        event.y = touch_y;
                    }
                    if(ev.code == ABS_Y) {
                        touch_y = ev.value * screen_height / 4096;
                        if(touch_y < 0) touch_y = 0;
                        if(touch_y >= screen_height) touch_y = screen_height - 1;
                        event.x = touch_x;
                        event.y = touch_y;
                    }
                    if(ev.code == ABS_MT_POSITION_X) {
                        event.x = ev.value * screen_width / 4096;
                    }
                    if(ev.code == ABS_MT_POSITION_Y) {
                        event.y = ev.value * screen_height / 4096;
                    }
                    event.pressed = touch_pressed;
                    break;
                    
                case EV_KEY:
                    if(ev.code == BTN_TOUCH) {
                        touch_pressed = ev.value;
                        event.pressed = touch_pressed;
                        event.x = touch_x;
                        event.y = touch_y;
                    }
                    break;
                    
                case EV_SYN:
                    if(touch_callback) {
                        touch_callback(&event);
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
    pthread_create(&thread, NULL, komaru_touch_thread, NULL);
}

int komaru_touch_get_x(void) { return touch_x; }
int komaru_touch_get_y(void) { return touch_y; }
int komaru_touch_is_pressed(void) { return touch_pressed; }
