#ifndef KOMARU_NOTIFY_H
#define KOMARU_NOTIFY_H

void komaru_notify_init(void);
void komaru_notify_show(const char *title, const char *message);
void komaru_notify_hide(void);
void komaru_notify_render(void);
void komaru_notify_update(void);

#endif
