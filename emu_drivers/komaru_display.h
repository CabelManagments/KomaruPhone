#ifndef KOMARU_DISPLAY_H
#define KOMARU_DISPLAY_H

int komaru_display_init(void);
void komaru_display_clear(void);
void komaru_display_pixel(int x, int y, int on);
void komaru_display_char(char c, int x, int y);
void komaru_display_string(const char *text, int x, int y);
void komaru_display_update(void);
void komaru_display_box(int x, int y, int w, int h, int fill);

#endif
