#include "komaru_rtc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int komaru_rtc_init(void) {
    return 0;
}

void komaru_rtc_get_time(char *buffer, int size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    snprintf(buffer, size, "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);
}

void komaru_rtc_set_time(int year, int month, int day, int hour, int min, int sec) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "date -s \"%04d-%02d-%02d %02d:%02d:%02d\"", year, month, day, hour, min, sec);
    system(cmd);
    system("hwclock -w");
}
