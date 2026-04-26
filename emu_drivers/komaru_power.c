#include "komaru_power.h"
#include <stdio.h>

static int battery = 85;
static int charging = 1;

int komaru_power_init(void) { return 0; }
int komaru_power_get_battery_level(void) { return battery; }
int komaru_power_is_charging(void) { return charging; }
void komaru_power_set_brightness(int percent) { printf("Brightness: %d%%\n", percent); }
void komaru_power_shutdown(void) { printf("Shutdown\n"); }
void komaru_power_reboot(void) { printf("Reboot\n"); }
