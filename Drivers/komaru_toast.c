#include "komaru_toast.h"
#include "komaru_display.h"
#include <string.h>

static char current_msg[64] = "";
static int visible = 0;
static int timer = 0;

void komaru_toast_show(const char *message, int duration_ms) {
    strncpy(current_msg, message, 63);
    visible = 1;
    timer = duration_ms / 50;
}

void komaru_toast_update(void) {
    if(visible && --timer <= 0) {
        visible = 0;
    }
}

void komaru_toast_render(void) {
    if(!visible) return;
    int len = strlen(current_msg);
    int x = (128 - len * 6) / 2;
    komaru_display_box(x - 4, 40, len * 6 + 8, 14, 1);
    komaru_display_string(current_msg, x, 43);
}
