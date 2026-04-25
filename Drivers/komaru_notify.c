#include "komaru_notify.h"
#include "komaru_display.h"
#include <string.h>

static char current_msg[128] = "";
static int visible = 0;
static int timer = 0;

void komaru_notify_init(void) {}

void komaru_notify_show(const char *title, const char *message) {
    snprintf(current_msg, sizeof(current_msg), "%s: %s", title, message);
    visible = 1;
    timer = 100;
}

void komaru_notify_hide(void) {
    visible = 0;
}

void komaru_notify_render(void) {
    if(!visible) return;
    komaru_display_box(0, 0, 128, 16, 1);
    komaru_display_string(current_msg, 2, 4);
}

void komaru_notify_update(void) {
    if(visible && --timer <= 0) {
        visible = 0;
    }
}
