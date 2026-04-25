#ifndef KOMARU_WM_H
#define KOMARU_WM_H

typedef struct komaru_app_t {
    const char *name;
    void (*on_draw)(void);
    void (*on_touch)(int x, int y, int pressed);
    void (*on_back)(void);
    void (*on_home)(void);
    struct komaru_app_t *next;
} komaru_app_t;

void komaru_wm_init(void);
void komaru_wm_run(komaru_app_t *home_screen);
void komaru_wm_switch_to(komaru_app_t *app);
void komaru_wm_go_back(void);
void komaru_wm_go_home(void);
void komaru_wm_add_to_recents(komaru_app_t *app);

#endif
