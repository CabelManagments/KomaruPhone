#ifndef KOMARU_WIFI_H
#define KOMARU_WIFI_H

int komaru_wifi_init(void);
int komaru_wifi_is_enabled(void);
void komaru_wifi_set_enabled(int enabled);
char* komaru_wifi_get_ssid(void);
char* komaru_wifi_get_ip(void);
int komaru_wifi_scan(char *networks[], int max_networks);
void komaru_wifi_connect(const char *ssid, const char *password);

#endif
