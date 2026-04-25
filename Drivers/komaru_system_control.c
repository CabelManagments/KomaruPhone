#include "komaru_system_control.h"
#include <stdio.h>
#include <stdlib.h>

void komaru_sys_set_brightness(int percent) {
    if(percent < 0) percent = 0;
    if(percent > 100) percent = 100;
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "echo %d > /sys/class/backlight/*/brightness", percent);
    system(cmd);
}

void komaru_sys_set_volume(int percent) {
    if(percent < 0) percent = 0;
    if(percent > 100) percent = 100;
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "amixer set Master %d%%", percent);
    system(cmd);
}
