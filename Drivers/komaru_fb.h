#ifndef KOMARU_FB_H
#define KOMARU_FB_H

int komaru_fb_init(void);
void komaru_fb_clear(void);
void komaru_fb_pixel(int x, int y, int r, int g, int b);
int komaru_fb_width(void);
int komaru_fb_height(void);
void komaru_fb_close(void);

#endif
