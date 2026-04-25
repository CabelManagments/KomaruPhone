#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int bt_enabled = 0;
static char bt_device_name[32] = "KomaruPhone";

int komaru_bluetooth_init(void) {
    // Проверка, есть ли bluetooth адаптер
    FILE *fp = popen("hciconfig", "r");
    char buf[128];
    if(fgets(buf, sizeof(buf), fp)) {
        bt_enabled = 1;
    }
    pclose(fp);
    
    if(bt_enabled) {
        system("hciconfig hci0 up");
        char cmd[128];
        snprintf(cmd, sizeof(cmd), "hciconfig hci0 name \"%s\"", bt_device_name);
        system(cmd);
    }
    return 0;
}

int komaru_bluetooth_is_enabled(void) {
    return bt_enabled;
}

void komaru_bluetooth_set_enabled(int enabled) {
    bt_enabled = enabled;
    if(enabled) {
        system("hciconfig hci0 up");
    } else {
        system("hciconfig hci0 down");
    }
}

void komaru_bluetooth_scan(char *devices[], int max_devices) {
    if(!bt_enabled) return;
    
    system("hcitool scan > /tmp/bt_scan.txt");
    FILE *fp = fopen("/tmp/bt_scan.txt", "r");
    char line[256];
    int count = 0;
    
    while(fgets(line, sizeof(line), fp) && count < max_devices) {
        if(strstr(line, "\t")) {
            // парсим MAC и имя
            devices[count] = strdup(line);
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
