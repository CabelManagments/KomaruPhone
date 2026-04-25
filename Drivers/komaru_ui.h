#ifndef KOMARU_UI_H
#define KOMARU_UI_H

#include <stdint.h>

typedef struct {
    int x, y, w, h;
    const char *text;
    int pressed;
    void (*on_click)(void);
} komaru_button_t;

typedef struct {
    int x, y, w, h;
    int value;
    int min, max;
    void (*on_change)(int new_value);
} komaru_slider_t;

typedef struct {
    int x, y;
    const char *items[10];
    int count;
    int selected;
    void (*on_select)(int index);
} komaru_list_t;

void komaru_ui_init(void);
void komaru_ui_draw_button(komaru_button_t *btn);
int komaru_ui_handle_button(komaru_button_t *btn, int x, int y, int pressed);
void komaru_ui_draw_slider(komaru_slider_t *slider);
int komaru_ui_handle_slider(komaru_slider_t *slider, int x, int y, int pressed);
void komaru_ui_draw_list(komaru_list_t *list);
int komaru_ui_handle_list(komaru_list_t *list, int x, int y, int pressed);

#endif
