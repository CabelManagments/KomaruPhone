#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_wifi.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    const char *name;
    const char *description;
    const char *url;
    int installed;
} komaru_app_t;

static komaru_app_t available_apps[] = {
    {"KomaruSettings", "Настройки системы", "local", 1},
    {"KomaruGallery", "Просмотр фото", "local", 1},
    {"KomaruBrowser", "Веб-браузер (coming soon)", "https://komaru.org/apps/browser", 0},
    {"KomaruNotes", "Заметки", "https://komaru.org/apps/notes", 0},
    {"KomaruChat", "Мессенджер", "https://komaru.org/apps/chat", 0},
    {"KomaruWeather", "Погода", "https://komaru.org/apps/weather", 0},
    {"KomaruTerminal", "Терминал", "local", 1},
    {NULL, NULL, NULL, 0}
};

static int selected = 0;

void komaru_appstore_run(void) {
    int running = 1;
    
    while(running) {
        komaru_display_clear();
        komaru_display_string("Komaru Store", 30, 5);
        
        int count = 0;
        for(int i = 0; available_apps[i].name != NULL; i++) {
            if(i == selected) {
                komaru_display_string(">", 5, 20 + count*20);
            }
            char line[64];
            snprintf(line, sizeof(line), "%s %s", 
                     available_apps[i].name,
                     available_apps[i].installed ? "[✓]" : "[ ]");
            komaru_display_string(line, 20, 20 + count*20);
            count++;
        }
        
        komaru_display_string("Power - установить", 20, 140);
        komaru_display_string("Vol+/- - навигация", 20, 160);
        
        int btn = komaru_buttons_read();
        if(btn & BTN_VOLUME_UP) {
            selected = (selected + 1) % count;
            usleep(200000);
        }
        if(btn & BTN_VOLUME_DOWN) {
            selected = (selected - 1 + count) % count;
            usleep(200000);
        }
        if(btn & BTN_POWER) {
            if(!available_apps[selected].installed) {
                komaru_display_clear();
                komaru_display_string("Скачивание...", 30, 60);
                char cmd[256];
                snprintf(cmd, sizeof(cmd), 
                         "wget %s -O /apps/%s",
                         available_apps[selected].url,
                         available_apps[selected].name);
                // system(cmd);
                available_apps[selected].installed = 1;
                usleep(2000000);
            } else {
                komaru_display_string("Уже установлено", 30, 60);
                usleep(1000000);
            }
        }
        
        komaru_display_update();
    }
}
