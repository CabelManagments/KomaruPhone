#include "komaru_power.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int battery_percent = 100;
static int charging = 0;

// чтение из /sys/class/power_supply (заглушка, пока данные фейковые)
int komaru_power_init(void) {
    battery_percent = 85;
    charging = 1;
    return 0;
}

int komaru_power_get_battery_level(void) {
    // Вернуть % заряда
    return battery_percent;
}

int komaru_power_is_charging(void) {
    return charging;
}

void komaru_power_set_brightness(int percent) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "echo %d > /sys/class/backlight/*/brightness", percent);
    system(cmd);
}

void komaru_power_shutdown(void) {
    sync();
    system("poweroff");
}

void komaru_power_reboot(void) {
    sync();
    system("reboot");
}
