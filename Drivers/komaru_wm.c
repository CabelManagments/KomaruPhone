#include "komaru_wm.h"
#include "komaru_display.h"
#include "komaru_touch.h"
#include "komaru_navbar.h"

#define MAX_RECENTS 10

static komaru_app_t *current_app = NULL;
static komaru_app_t *home_app = NULL;
static komaru_app_t *recents[MAX_RECENTS];
static int recents_count = 0;

void komaru_wm_init(void) {
    // Ничего особенного
}

static void on_nav_action(komaru_nav_action_t action) {
    switch(action) {
        case KOMARU_NAV_BACK:
            komaru_wm_go_back();
            break;
        case KOMARU_NAV_HOME:
            komaru_wm_go_home();
            break;
        case KOMARU_NAV_RECENTS:
            // Показать список недавних
            break;
    }
}

void komaru_wm_add_to_recents(komaru_app_t *app) {
    // Сдвигаем существующие
    for(int i = MAX_RECENTS - 1; i > 0; i--) {
        recents[i] = recents[i-1];
    }
    recents[0] = app;
    if(recents_count < MAX_RECENTS) recents_count++;
}

void komaru_wm_switch_to(komaru_app_t *app) {
    if(current_app == app) return;
    
    komaru_wm_add_to_recents(current_app);
    current_app = app;
    
    komaru_display_clear();
    if(current_app && current_app->on_draw) {
        current_app->on_draw();
    }
    komaru_navbar_render();
    komaru_display_update();
}

void komaru_wm_go_back(void) {
    if(recents_count > 0) {
        current_app = recents[0];
        // Сдвигаем список
        for(int i = 0; i < recents_count - 1; i++) {
            recents[i] = recents[i+1];
        }
        recents_count--;
        
        if(current_app && current_app->on_draw) {
            current_app->on_draw();
        }
        komaru_navbar_render();
        komaru_display_update();
    } else {
        komaru_wm_go_home();
    }
}

void komaru_wm_go_home(void) {
    current_app = home_app;
    if(home_app && home_app->on_draw) {
        home_app->on_draw();
    }
    komaru_navbar_render();
    komaru_display_update();
}

static void touch_callback(touch_event_t *event) {
    if(!current_app || !current_app->on_touch) return;
    
    // Навигационная панель имеет приоритет
    if(event->pressed && komaru_navbar_handle_touch(event->x, event->y)) {
        return;
    }
    
    current_app->on_touch(event->x, event->y, event->pressed);
}

void komaru_wm_run(komaru_app_t *home) {
    home_app = home;
    current_app = home;
    
    komaru_touch_register_callback(touch_callback);
    komaru_navbar_init(on_nav_action);
    komaru_touch_start();
    
    if(current_app && current_app->on_draw) {
        current_app->on_draw();
    }
    
    while(1) {
        usleep(16667); // 60 fps
    }
}
