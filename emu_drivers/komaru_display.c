#include "komaru_display.h"
#include <stdio.h>
#include <string.h>

#define WIDTH 30
#define HEIGHT 20

static char screen[HEIGHT][WIDTH+1];
static int initialized = 0;

int komaru_display_init(void) {
    initialized = 1;
    komaru_display_clear();
    return 0;
}

void komaru_display_clear(void) {
    for(int y = 0; y < HEIGHT; y++) {
        memset(screen[y], ' ', WIDTH);
        screen[y][WIDTH] = '\0';
    }
}

void komaru_display_string(const char *text, int x, int y) {
    if(!initialized || y < 0 || y >= HEIGHT) return;
    int i;
    for(i = 0; text[i] && x+i < WIDTH; i++) {
        screen[y][x+i] = text[i];
    }
}

void komaru_display_update(void) {
    if(!initialized) return;
    printf("\033[2J\033[H");
    for(int y = 0; y < HEIGHT; y++) {
        printf("%s\n", screen[y]);
    }
    printf("=== KomaruPhone v0.4 ===\n");
    printf("p=power u=vol+ d=vol- r=prog q=quit\n");
}

void komaru_display_box(int x, int y, int w, int h, int fill) {
    (void)x; (void)y; (void)w; (void)h; (void)fill; // заглушка
}

void komaru_display_pixel(int x, int y, int on) { (void)x; (void)y; (void)on; }
void komaru_display_char(char c, int x, int y) { (void)c; (void)x; (void)y; }
