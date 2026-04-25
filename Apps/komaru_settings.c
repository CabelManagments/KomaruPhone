#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_power.h"
#include "komaru_wifi.h"
#include "komaru_bluetooth.h"
#include "komaru_vibrator.h"
#include "komaru_system_control.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SETTINGS_MAIN,
    SETTINGS_DISPLAY,
    SETTINGS_SOUND,
    SETTINGS_NETWORK,
    SETTINGS_BATTERY,
    SETTINGS_ABOUT,
    SETTINGS_DEVELOPER
} settings_screen_t;

static settings_screen_t current_screen = SETTINGS_MAIN;
static int selected_item = 0;
static int running = 1;

static const char *main_items[] = {
    "Дисплей", "Звук", "Сеть", "Батарея", "О системе", "Режим разработчика", "Выйти"
};
static int main_count = 7;

static int brightness = 70;
static int auto_rotate = 1;
static int volume = 50;
static int vibrate_on_touch = 1;

void settings_save_all(void) {
    FILE *fp = fopen("/home/komaru/settings.conf", "w");
    if(fp) {
        fprintf(fp, "brightness=%d\n", brightness);
        fprintf(fp, "auto_rotate=%d\n", auto_rotate);
        fprintf(fp, "volume=%d\n", volume);
        fprintf(fp, "vibrate_on_touch=%d\n", vibrate_on_touch);
        fclose(fp);
    }
}

void settings_load_all(void) {
    FILE *fp = fopen("/home/komaru/settings.conf", "r");
    if(fp) {
        char line[64];
        while(fgets(line, sizeof(line), fp)) {
            if(strncmp(line, "brightness=", 11) == 0) brightness = atoi(line + 11);
            if(strncmp(line, "auto_rotate=", 12) == 0) auto_rotate = atoi(line + 12);
            if(strncmp(line, "volume=", 7) == 0) volume = atoi(line + 7);
            if(strncmp(line, "vibrate_on_touch=", 17) == 0) vibrate_on_touch = atoi(line + 17);
        }
        fclose(fp);
    }
    komaru_power_set_brightness(brightness);
    komaru_sys_set_volume(volume);
    komaru_vibrator_set_enabled(vibrate_on_touch);
}

static void draw_main_menu(void) {
    komaru_display_clear();
    komaru_display_string("Настройки", 40, 5);
    for(int i = 0; i < main_count; i++) {
        if(i == selected_item) komaru_display_string(">", 5, 20 + i*15);
        komaru_display_string(main_items[i], 20, 20 + i*15);
    }
}

static void draw_display_settings(void) {
    komaru_display_clear();
    komaru_display_string("Дисплей", 40, 5);
    char buf[32];
    snprintf(buf, sizeof(buf), "Яркость: %d%%", brightness);
    komaru_display_string(buf, 10, 30);
    snprintf(buf, sizeof(buf), "Автоповорот: %s", auto_rotate ? "Вкл" : "Выкл");
    komaru_display_string(buf, 10, 55);
    komaru_display_string("Vol+/- - изменить", 5, 110);
}

static void draw_sound_settings(void) {
    komaru_display_clear();
    komaru_display_string("Звук", 50, 5);
    char buf[32];
    snprintf(buf, sizeof(buf), "Громкость: %d%%", volume);
    komaru_display_string(buf, 10, 30);
    snprintf(buf, sizeof(buf), "Вибрация: %s", vibrate_on_touch ? "Вкл" : "Выкл");
    komaru_display_string(buf, 10, 55);
}

static void draw_network_settings(void) {
    komaru_display_clear();
    komaru_display_string("Сеть", 50, 5);
    char buf[32];
    snprintf(buf, sizeof(buf), "Wi-Fi: %s", komaru_wifi_is_enabled() ? "Вкл" : "Выкл");
    komaru_display_string(buf, 10, 30);
    snprintf(buf, sizeof(buf), "BT: %s", komaru_bluetooth_is_enabled() ? "Вкл" : "Выкл");
    komaru_display_string(buf, 10, 55);
}

static void draw_battery_settings(void) {
    komaru_display_clear();
    komaru_display_string("Батарея", 45, 5);
    char buf[32];
    snprintf(buf, sizeof(buf), "Заряд: %d%%", komaru_power_get_battery_level());
    komaru_display_string(buf, 10, 30);
    snprintf(buf, sizeof(buf), "Статус: %s", komaru_power_is_charging() ? "Зарядка" : "Батарея");
    komaru_display_string(buf, 10, 55);
}

static void draw_about(void) {
    komaru_display_clear();
    komaru_display_string("KomaruOS", 35, 10);
    komaru_display_string("Версия: 0.4", 15, 35);
    komaru_display_string("Открытая ОС", 15, 55);
    komaru_display_string("Свобода и кошки", 10, 75);
    komaru_display_string("(c) 2025", 40, 100);
}

static void draw_developer(void) {
    komaru_display_clear();
    komaru_display_string("Реж. разработчика", 20, 5);
    komaru_display_string("Осторожно!", 40, 30);
    komaru_display_string("Сброс системы", 35, 55);
    komaru_display_string("Power - подтвердить", 10, 110);
}

static void handle_main_input(int btn) {
    if(btn & BTN_VOLUME_UP) { selected_item = (selected_item + 1) % main_count; komaru_vibrator_on(20); }
    if(btn & BTN_VOLUME_DOWN) { selected_item = (selected_item - 1 + main_count) % main_count; komaru_vibrator_on(20); }
    if(btn & BTN_POWER) {
        komaru_vibrator_on(50);
        switch(selected_item) {
            case 0: current_screen = SETTINGS_DISPLAY; break;
            case 1: current_screen = SETTINGS_SOUND; break;
            case 2: current_screen = SETTINGS_NETWORK; break;
            case 3: current_screen = SETTINGS_BATTERY; break;
            case 4: current_screen = SETTINGS_ABOUT; break;
            case 5: current_screen = SETTINGS_DEVELOPER; break;
            case 6: running = 0; break;
        }
        selected_item = 0;
    }
}

static void handle_display_input(int btn) {
    if(btn & BTN_VOLUME_UP) { brightness += 5; if(brightness > 100) brightness = 100; komaru_power_set_brightness(brightness); komaru_vibrator_on(20); }
    if(btn & BTN_VOLUME_DOWN) { brightness -= 5; if(brightness < 0) brightness = 0; komaru_power_set_brightness(brightness); komaru_vibrator_on(20); }
    if(btn & BTN_PROG) { auto_rotate = !auto_rotate; komaru_vibrator_on(50); }
    if(btn & BTN_POWER) { settings_save_all(); current_screen = SETTINGS_MAIN; }
}

static void handle_sound_input(int btn) {
    if(btn & BTN_VOLUME_UP) { volume += 5; if(volume > 100) volume = 100; komaru_sys_set_volume(volume); komaru_vibrator_on(20); }
    if(btn & BTN_VOLUME_DOWN) { volume -= 5; if(volume < 0) volume = 0; komaru_sys_set_volume(volume); komaru_vibrator_on(20); }
    if(btn & BTN_PROG) { vibrate_on_touch = !vibrate_on_touch; komaru_vibrator_set_enabled(vibrate_on_touch); komaru_vibrator_on(50); }
    if(btn & BTN_POWER) { settings_save_all(); current_screen = SETTINGS_MAIN; }
}

static void handle_network_input(int btn) {
    if(btn & BTN_VOLUME_UP) { komaru_wifi_set_enabled(!komaru_wifi_is_enabled()); komaru_vibrator_on(30); }
    if(btn & BTN_VOLUME_DOWN) { komaru_bluetooth_set_enabled(!komaru_bluetooth_is_enabled()); komaru_vibrator_on(30); }
    if(btn & BTN_POWER) { settings_save_all(); current_screen = SETTINGS_MAIN; }
}

static void handle_battery_input(int btn) {
    if(btn & BTN_POWER) current_screen = SETTINGS_MAIN;
}

static void handle_about_input(int btn) {
    if(btn & BTN_POWER) current_screen = SETTINGS_MAIN;
}

static void handle_developer_input(int btn) {
    if(btn & BTN_POWER) {
        komaru_display_clear();
        komaru_display_string("Сброс системы...", 30, 40);
        komaru_display_update();
        usleep(2000000);
        komaru_power_reboot();
    }
    if(btn & BTN_PROG) current_screen = SETTINGS_MAIN;
}

void komaru_settings_run(void) {
    settings_load_all();
    running = 1;
    while(running) {
        switch(current_screen) {
            case SETTINGS_MAIN: draw_main_menu(); break;
            case SETTINGS_DISPLAY: draw_display_settings(); break;
            case SETTINGS_SOUND: draw_sound_settings(); break;
            case SETTINGS_NETWORK: draw_network_settings(); break;
            case SETTINGS_BATTERY: draw_battery_settings(); break;
            case SETTINGS_ABOUT: draw_about(); break;
            case SETTINGS_DEVELOPER: draw_developer(); break;
        }
        komaru_display_update();
        int btn = komaru_buttons_read();
        if(btn) {
            switch(current_screen) {
                case SETTINGS_MAIN: handle_main_input(btn); break;
                case SETTINGS_DISPLAY: handle_display_input(btn); break;
                case SETTINGS_SOUND: handle_sound_input(btn); break;
                case SETTINGS_NETWORK: handle_network_input(btn); break;
                case SETTINGS_BATTERY: handle_battery_input(btn); break;
                case SETTINGS_ABOUT: handle_about_input(btn); break;
                case SETTINGS_DEVELOPER: handle_developer_input(btn); break;
            }
        }
        usleep(100000);
    }
}
