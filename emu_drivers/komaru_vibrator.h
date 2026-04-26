#ifndef KOMARU_VIBRATOR_H
#define KOMARU_VIBRATOR_H

void komaru_vibrator_init(void);
void komaru_vibrator_on(int ms);
void komaru_vibrator_set_enabled(int enabled);
void komaru_vibrator_pattern(int *pattern, int count);

#endif
