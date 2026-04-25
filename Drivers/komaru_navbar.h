#ifndef KOMARU_NAVBAR_H
#define KOMARU_NAVBAR_H

typedef enum {
    KOMARU_NAV_BACK,
    KOMARU_NAV_HOME,
    KOMARU_NAV_RECENTS
} komaru_nav_action_t;

typedef void (*komaru_nav_callback_t)(komaru_nav_action_t action);

void komaru_navbar_init(komaru_nav_callback_t callback);
void komaru_navbar_render(void);
int komaru_navbar_handle_touch(int x, int y);
void komaru_navbar_set_visible(int visible);

#endif
