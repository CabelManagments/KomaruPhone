#include "komaru_navbar.h"
#include "komaru_display.h"

#define NAVBAR_HEIGHT 40
#define BUTTON_WIDTH 60

static komaru_nav_callback_t nav_callback = NULL;
static int visible = 1;
static int screen_width = 128;
static int screen_height = 64;

void komaru_navbar_init(komaru_nav_callback_t callback) {
    nav_callback = callback;
}

void komaru_navbar_render(void) {
    if(!visible) return;
    
    int y = screen_height - NAVBAR_HEIGHT;
    
    // Фон панели
    komaru_display_box(0, y, screen_width, NAVBAR_HEIGHT, 1);
    
    // Кнопка "Назад" (◁)
    komaru_display_string("<", (BUTTON_WIDTH/2) - 5, y + 12);
    komaru_display_string("Назад", (BUTTON_WIDTH/2) - 12, y + 28);
    
    // Кнопка "Домой" (○)
    komaru_display_string("O", (screen_width/2) - 5, y + 12);
    komaru_display_string("Домой", (screen_width/2) - 12, y + 28);
    
    // Кнопка "Недавние" (□)
    komaru_display_string("□", screen_width - (BUTTON_WIDTH/2) - 5, y + 12);
    komaru_display_string("Прил", screen_width - 35, y + 28);
}

int komaru_navbar_handle_touch(int x, int y) {
    if(!visible) return 0;
    
    int screen_height = 64;
    int navbar_y = screen_height - NAVBAR_HEIGHT;
    
    if(y >= navbar_y && nav_callback) {
        // Нажатие на кнопку "Назад" (левая треть)
        if(x < BUTTON_WIDTH) {
            nav_callback(KOMARU_NAV_BACK);
            return 1;
        }
        // Нажатие на кнопку "Домой" (центр)
        else if(x > screen_width/2 - BUTTON_WIDTH/2 && 
                x < screen_width/2 + BUTTON_WIDTH/2) {
            nav_callback(KOMARU_NAV_HOME);
            return 1;
        }
        // Нажатие на кнопку "Недавние" (правая треть)
        else if(x > screen_width - BUTTON_WIDTH) {
            nav_callback(KOMARU_NAV_RECENTS);
            return 1;
        }
    }
    return 0;
}

void komaru_navbar_set_visible(int v) {
    visible = v;
}
