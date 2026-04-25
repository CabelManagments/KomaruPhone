#ifndef KOMARU_POWER_H
#define KOMARU_POWER_H

int komaru_power_init(void);
int komaru_power_get_battery_level(void);
int komaru_power_is_charging(void);
void komaru_power_set_brightness(int percent);
void komaru_power_shutdown(void);
void komaru_power_reboot(void);

#endif
