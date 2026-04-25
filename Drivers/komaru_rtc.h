#ifndef KOMARU_RTC_H
#define KOMARU_RTC_H

int komaru_rtc_init(void);
void komaru_rtc_get_time(char *buffer, int size);
void komaru_rtc_set_time(int year, int month, int day, int hour, int min, int sec);

#endif
