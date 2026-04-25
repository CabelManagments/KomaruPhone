#ifndef KOMARU_DISPLAY_H
#define KOMARU_DISPLAY_H

#include <stdint.h>

int komaru_display_init(void);
void komaru_display_clear(void);
void komaru_display_print(const char *text, int row);
void komaru_display_print_center(const char *text, int row);

#endif /* KOMARU_DISPLAY_H */
