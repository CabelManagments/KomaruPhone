#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char current_ssid[64] = "";
static int wifi_enabled = 0;

int komaru_wifi_init(void) {
    wifi_enabled = 1;
    strcpy(current_ssid, "KomaruNet");
    return 0;
}

int komaru_wifi_is_enabled(void) {
    return wifi_enabled;
}

void komaru_wifi_set_enabled(int enabled) {
    wifi_enabled = enabled;
    if(enabled) {
        system("ifconfig wlan0 up");
    } else {
        system("ifconfig wlan0 down");
    }
}

char* komaru_wifi_get_ssid(void) {
    return current_ssid;
}

int komaru_wifi_scan(char *networks[], int max_networks) {
    // Заглушка: возвращаем пару фейковых сетей
    if(max_networks >= 1) networks[0] = "KomaruNet";
    if(max_networks >= 2) networks[1] = "FreeWiFi";
    return 2;
}
