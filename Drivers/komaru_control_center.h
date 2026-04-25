#ifndef KOMARU_CONTROL_CENTER_H
#define KOMARU_CONTROL_CENTER_H

#include <stdint.h>

typedef struct {
    int x, y, w, h;
    int is_dragging;
    int value; // 0-100 для яркости/звука
} komaru_slider_t;

typedef struct {
    int x, y, w, h;
    int active;
    const char *icon; // текстовая иконка, потом картинка
    void (*on_toggle)(int active);
} komaru_toggle_t;

void komaru_control_center_init(void);
void komaru_control_center_show(void);
void komaru_control_center_hide(void);
int komaru_control_center_is_visible(void);
void komaru_control_center_handle_touch(int x, int y, int touched);
void komaru_control_center_render(void);

#endif
