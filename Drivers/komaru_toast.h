#ifndef KOMARU_TOAST_H
#define KOMARU_TOAST_H

void komaru_toast_show(const char *message, int duration_ms);
void komaru_toast_update(void);
void komaru_toast_render(void);

#endif
