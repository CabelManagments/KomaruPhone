#ifndef KOMARU_BUTTONS_H
#define KOMARU_BUTTONS_H

#define BTN_POWER     (1 << 0)
#define BTN_VOLUME_UP (1 << 1)
#define BTN_VOLUME_DOWN (1 << 2)
#define BTN_PROGRAM   (1 << 3)

int komaru_buttons_init(void);
int komaru_buttons_read(void);

#endif
