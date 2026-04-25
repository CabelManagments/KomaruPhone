#include "komaru_control_center.h"
#include "komaru_display.h"
#include "komaru_buttons.h"  // для яркости

static int visible = 0;
static int anim_y = -200;    // для выезда сверху
static komaru_slider_t brightness_slider = {30, 200, 260, 30, 0, 70};
static komaru_slider_t volume_slider = {30, 260, 260, 30, 0, 50};
static komaru_toggle_t wifi_toggle = {30, 100, 60, 60, 1, "Wi-Fi", NULL};
static komaru_toggle_t bt_toggle = {100, 100, 60, 60, 0, "BT", NULL};
static komaru_toggle_t dnd_toggle = {170, 100, 60, 60, 0, "DND", NULL};
static komaru_toggle_t dev_toggle = {240, 100, 60, 60, 0, "⚡️Разъёб", NULL};

static void draw_rounded_rect(int x, int y, int w, int h, int radius, int fill) {
    // упрощённая версия — рисуем просто прямоугольник
    (void)radius;
    komaru_display_box(x, y, w, h, fill);
}

static void draw_slider(komaru_slider_t *slider) {
    draw_rounded_rect(slider->x, slider->y, slider->w, slider->h, 8, 1);
    int fill_w = (slider->value * slider->w) / 100;
    komaru_display_box(slider->x, slider->y, fill_w, slider->h, 1);
}

static void draw_toggle(komaru_toggle_t *toggle) {
    draw_rounded_rect(toggle->x, toggle->y, toggle->w, toggle->h, 30, 1);
    if(toggle->active) {
        komaru_display_string(toggle->icon, toggle->x+10, toggle->y+20);
    } else {
        komaru_display_string(toggle->icon, toggle->x+10, toggle->y+20);
    }
}

void komaru_control_center_init(void) {
    brightness_slider.value = 70;
    volume_slider.value = 50;
}

void komaru_control_center_show(void) {
    visible = 1;
    anim_y = 0;   // мгновенно показываем, попозже добавим плавность
}

void komaru_control_center_hide(void) {
    visible = 0;
}

int komaru_control_center_is_visible(void) {
    return visible;
}

void komaru_control_center_handle_touch(int x, int y, int touched) {
    if(!visible) return;
    
    // проверка ползунков
    if(x >= brightness_slider.x && x <= brightness_slider.x+brightness_slider.w &&
       y >= brightness_slider.y && y <= brightness_slider.y+brightness_slider.h && touched) {
        int new_val = ((x - brightness_slider.x) * 100) / brightness_slider.w;
        if(new_val < 0) new_val = 0;
        if(new_val > 100) new_val = 100;
        brightness_slider.value = new_val;
        // TODO: реально менять яркость через sysfs
        // echo $new_val > /sys/class/backlight/*/brightness
    }
    
    if(x >= volume_slider.x && x <= volume_slider.x+volume_slider.w &&
       y >= volume_slider.y && y <= volume_slider.y+volume_slider.h && touched) {
        int new_val = ((x - volume_slider.x) * 100) / volume_slider.w;
        if(new_val < 0) new_val = 0;
        if(new_val > 100) new_val = 100;
        volume_slider.value = new_val;
        // TODO: amixer set Master $new_val%
    }
    
    // кнопки
    if(x >= wifi_toggle.x && x <= wifi_toggle.x+wifi_toggle.w &&
       y >= wifi_toggle.y && y <= wifi_toggle.y+wifi_toggle.h && touched)
        wifi_toggle.active = !wifi_toggle.active;
        
    if(x >= bt_toggle.x && x <= bt_toggle.x+bt_toggle.w &&
       y >= bt_toggle.y && y <= bt_toggle.y+bt_toggle.h && touched)
        bt_toggle.active = !bt_toggle.active;
        
    if(x >= dnd_toggle.x && x <= dnd_toggle.x+dnd_toggle.w &&
       y >= dnd_toggle.y && y <= dnd_toggle.y+dnd_toggle.h && touched)
        dnd_toggle.active = !dnd_toggle.active;
        
    if(x >= dev_toggle.x && x <= dev_toggle.x+dev_toggle.w &&
       y >= dev_toggle.y && y <= dev_toggle.y+dev_toggle.h && touched) {
        // вызываем KomaruDevTool
        system("/usr/bin/komaru_devtool");
    }
}

void komaru_control_center_render(void) {
    if(!visible) return;
    
    // Полупрозрачный фон (только рамка)
    draw_rounded_rect(0, anim_y, 320, 400, 20, 1);
    
    // Время и дата
    komaru_display_string("20:44", 20, anim_y+20);
    
    // Секция переключателей
    draw_toggle(&wifi_toggle);
    draw_toggle(&bt_toggle);
    draw_toggle(&dnd_toggle);
    draw_toggle(&dev_toggle);
    
    // Ползунки
    komaru_display_string("Яркость", 30, anim_y+180);
    draw_slider(&brightness_slider);
    
    komaru_display_string("Громкость", 30, anim_y+240);
    draw_slider(&volume_slider);
    
    // Кошка вместо звуков
    komaru_display_string("🐱", 270, anim_y+300);
}
