#include "komaru_gesture.h"

typedef struct {
    int active;
    int start_x, start_y;
    int last_x, last_y;
} touch_point_t;

static touch_point_t touches[5]; // поддержка до 5 пальцев

void komaru_gesture_init(void) {
    for(int i = 0; i < 5; i++) touches[i].active = 0;
}

void komaru_gesture_touch_start(int id, int x, int y) {
    if(id >= 0 && id < 5) {
        touches[id].active = 1;
        touches[id].start_x = x;
        touches[id].start_y = y;
        touches[id].last_x = x;
        touches[id].last_y = y;
    }
}

void komaru_gesture_touch_move(int id, int x, int y) {
    if(id >= 0 && id < 5 && touches[id].active) {
        int dx = x - touches[id].last_x;
        int dy = y - touches[id].last_y;
        // эвент скролла или свайпа
        touches[id].last_x = x;
        touches[id].last_y = y;
    }
}

void komaru_gesture_touch_end(int id) {
    if(id >= 0 && id < 5) {
        touches[id].active = 0;
    }
}
