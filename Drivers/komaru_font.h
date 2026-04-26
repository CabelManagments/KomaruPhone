#ifndef KOMARU_FONT_H
#define KOMARU_FONT_H

#include <stdint.h>

extern const uint8_t font_5x7[96][5];
extern const uint8_t font_8x8[96][8];
extern const uint8_t font_8x16[96][16];

int komaru_font_width(void);
int komaru_font_height(void);
void komaru_font_set_size(int size); // 0=5x7, 1=8x8, 2=8x16
const uint8_t* komaru_font_get_char(char c);

#endif
