#include "komaru_ui.h"
#include "komaru_display.h"
#include <string.h>

void komaru_ui_init(void) {
    // Инициализация UI-системы
}

void komaru_ui_draw_button(komaru_button_t *btn) {
    komaru_display_box(btn->x, btn->y, btn->w, btn->h, btn->pressed ? 0 : 1);
    komaru_display_string(btn->text, btn->x + 5, btn->y + (btn->h/2) - 3);
}

int komaru_ui_handle_button(komaru_button_t *btn, int x, int y, int pressed) {
    if(x >= btn->x && x <= btn->x + btn->w &&
       y >= btn->y && y <= btn->y + btn->h) {
        if(pressed) {
            btn->pressed = 1;
        } else if(btn->pressed) {
            btn->pressed = 0;
            if(btn->on_click) btn->on_click();
        }
        return 1;
    }
    btn->pressed = 0;
    return 0;
}

void komaru_ui_draw_slider(komaru_slider_t *slider) {
    // Фон
    komaru_display_box(slider->x, slider->y, slider->w, slider->h, 1);
    // Заполненная часть
    int fill_w = (slider->value - slider->min) * slider->w / (slider->max - slider->min);
    komaru_display_box(slider->x, slider->y, fill_w, slider->h, 0);
}

int komaru_ui_handle_slider(komaru_slider_t *slider, int x, int y, int pressed) {
    if(!pressed) return 0;
    if(x >= slider->x && x <= slider->x + slider->w &&
       y >= slider->y && y <= slider->y + slider->h) {
        int new_val = slider->min + (x - slider->x) * (slider->max - slider->min) / slider->w;
        if(new_val < slider->min) new_val = slider->min;
        if(new_val > slider->max) new_val = slider->max;
        if(new_val != slider->value) {
            slider->value = new_val;
            if(slider->on_change) slider->on_change(new_val);
        }
        return 1;
    }
    return 0;
}

void komaru_ui_draw_list(komaru_list_t *list) {
    for(int i = 0; i < list->count; i++) {
        int y = list->y + i * 20;
        if(i == list->selected) {
            komaru_display_string(">", list->x - 10, y);
        }
        komaru_display_string(list->items[i], list->x, y);
    }
}

int komaru_ui_handle_list(komaru_list_t *list, int x, int y, int pressed) {
    if(!pressed) return 0;
    for(int i = 0; i < list->count; i++) {
        int item_y = list->y + i * 20;
        if(y >= item_y && y <= item_y + 16) {
            list->selected = i;
            if(list->on_select) list->on_select(i);
            return 1;
        }
    }
    return 0;
}
