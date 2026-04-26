#include "komaru_wifi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int wifi_enabled = 0;
static char current_ssid[64] = "";
static char current_ip[16] = "";

int komaru_wifi_init(void) {
    FILE *fp = popen("ifconfig wlan0 2>/dev/null | grep inet | awk '{print $2}'", "r");
    if(fp) {
        if(fgets(current_ip, sizeof(current_ip), fp)) {
            current_ip[strcspn(current_ip, "\n")] = 0;
            wifi_enabled = 1;
        }
        pclose(fp);
    }
    return 0;
}

int komaru_wifi_is_enabled(void) { return wifi_enabled; }

void komaru_wifi_set_enabled(int enabled) {
    wifi_enabled = enabled;
    if(enabled) {
        system("ifconfig wlan0 up");
        system("wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf");
        system("dhclient wlan0");
    } else {
        system("ifconfig wlan0 down");
        system("killall wpa_supplicant");
    }
}

char* komaru_wifi_get_ssid(void) {
    FILE *fp = popen("iwgetid -r", "r");
    if(fp) {
        if(fgets(current_ssid, sizeof(current_ssid), fp)) {
            current_ssid[strcspn(current_ssid, "\n")] = 0;
        }
        pclose(fp);
    }
    return current_ssid;
}

char* komaru_wifi_get_ip(void) { return current_ip; }

int komaru_wifi_scan(char *networks[], int max_networks) {
    system("iwlist wlan0 scan > /tmp/wifi_scan");
    FILE *fp = fopen("/tmp/wifi_scan", "r");
    if(!fp) return 0;
    
    char line[256];
    int count = 0;
    while(fgets(line, sizeof(line), fp) && count < max_networks) {
        if(strstr(line, "ESSID:")) {
            char *start = strchr(line, '"');
            char *end = strrchr(line, '"');
            if(start && end && start != end) {
                int len = end - start - 1;
                networks[count] = malloc(len + 1);
                strncpy(networks[count], start + 1, len);
                networks[count][len] = '\0';
                count++;
            }
        }
    }
    fclose(fp);
    return count;
}

void komaru_wifi_connect(const char *ssid, const char *password) {
    FILE *fp = fopen("/etc/wpa_supplicant.conf", "a");
    if(fp) {
        fprintf(fp, "\nnetwork={\n");
        fprintf(fp, "    ssid=\"%s\"\n", ssid);
        fprintf(fp, "    psk=\"%s\"\n", password);
        fprintf(fp, "}\n");
        fclose(fp);
    }
    system("wpa_cli reconfigure");
    sleep(3);
    system("dhclient wlan0");
}
