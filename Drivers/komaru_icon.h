#ifndef KOMARU_ICON_H
#define KOMARU_ICON_H

#include <stdint.h>

// Банан 16x16
extern const uint8_t icon_banana_16x16[32];

// Кошка 16x16
extern const uint8_t icon_cat_16x16[32];

// Банан с ушами 32x32
extern const uint8_t icon_banana_cat_32x32[128];

void komaru_icon_draw(int x, int y, const uint8_t *icon, int w, int h);

#endif
