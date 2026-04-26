#include "komaru_bluetooth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int bt_enabled = 0;
static char bt_name[32] = "KomaruPhone";

int komaru_bluetooth_init(void) {
    FILE *fp = popen("hciconfig hci0 2>/dev/null | grep 'UP RUNNING'", "r");
    char buf[128];
    if(fgets(buf, sizeof(buf), fp)) bt_enabled = 1;
    pclose(fp);
    return 0;
}

int komaru_bluetooth_is_enabled(void) { return bt_enabled; }

void komaru_bluetooth_set_enabled(int enabled) {
    bt_enabled = enabled;
    if(enabled) {
        system("hciconfig hci0 up");
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "hciconfig hci0 name \"%s\"", bt_name);
        system(cmd);
        system("hciconfig hci0 piscan");
    } else {
        system("hciconfig hci0 down");
    }
}

void komaru_bluetooth_set_name(const char *name) {
    strncpy(bt_name, name, sizeof(bt_name) - 1);
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "hciconfig hci0 name \"%s\"", bt_name);
    system(cmd);
}

void komaru_bluetooth_scan(char *devices[], int *rssi, int max_devices) {
    system("hcitool scan > /tmp/bt_scan");
    FILE *fp = fopen("/tmp/bt_scan", "r");
    if(!fp) return;
    
    char line[256];
    int count = 0;
    while(fgets(line, sizeof(line), fp) && count < max_devices) {
        char mac[18], name[64];
        if(sscanf(line, "%17s %63[^\n]", mac, name) == 2) {
            devices[count] = malloc(strlen(name) + 1);
            strcpy(devices[count], name);
            rssi[count] = 0;
            count++;
        }
    }
    fclose(fp);
}

void komaru_bluetooth_send_file(const char *filename, const char *device_mac) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "obexftp -b %s -p %s", device_mac, filename);
    system(cmd);
}
