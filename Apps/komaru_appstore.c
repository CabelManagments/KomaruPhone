#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_wifi.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    char name[32];
    char desc[64];
    int installed;
} komaru_app_item_t;

static komaru_app_item_t apps[] = {
    {"KomaruBrowser", "Web browser", 1},
    {"KomaruNotes", "Notes app", 1},
    {"KomaruGallery", "Image viewer", 1},
    {"KomaruTerminal", "Terminal emulator", 0},
    {"KomaruChat", "Messenger", 0},
    {"KomaruWeather", "Weather app", 0},
    {NULL, "", 0}
};

static int selected = 0;

void komaru_appstore_run(void) {
    int running = 1;
    
    while(running) {
        komaru_display_clear();
        komaru_display_string("KomaruStore", 35, 2);
        
        int y = 14;
        for(int i = 0; apps[i].name[0] != '\0' && y < 60; i++) {
            if(i == selected) {
                komaru_display_string(">", 2, y);
            }
            char line[40];
            snprintf(line, sizeof(line), "%s %s", apps[i].name, apps[i].installed ? "[✓]" : "[ ]");
            komaru_display_string(line, 12, y);
            y += 8;
        }
        
        komaru_display_string("Vol+/- select", 5, 60);
        komaru_display_string("Power install", 70, 60);
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_VOLUME_UP) {
            selected++;
            if(apps[selected].name[0] == '\0') selected = 0;
        }
        if(btn & BTN_VOLUME_DOWN) {
            selected--;
            if(selected < 0) {
                for(selected = 0; apps[selected].name[0] != '\0'; selected++);
                selected--;
            }
        }
        if(btn & BTN_POWER) {
            if(!apps[selected].installed) {
                komaru_display_clear();
                komaru_display_string("Downloading...", 35, 30);
                komaru_display_update();
                usleep(1000000);
                apps[selected].installed = 1;
            } else {
                running = 0;
            }
        }
        if(btn & BTN_PROGRAM) {
            running = 0;
        }
        
        usleep(50000);
    }
}
