#ifndef KOMARU_BLUETOOTH_H
#define KOMARU_BLUETOOTH_H

int komaru_bluetooth_init(void);
int komaru_bluetooth_is_enabled(void);
void komaru_bluetooth_set_enabled(int enabled);
void komaru_bluetooth_set_name(const char *name);
void komaru_bluetooth_scan(char *devices[], int *rssi, int max_devices);
void komaru_bluetooth_send_file(const char *filename, const char *device_mac);

#endif
