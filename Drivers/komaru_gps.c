#include "komaru_gps.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

static int gps_fd = -1;
static gps_data_t last_data = {0};

int komaru_gps_init(void) {
    gps_fd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY);
    if(gps_fd < 0) return -1;
    
    struct termios tty;
    tcgetattr(gps_fd, &tty);
    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    tcsetattr(gps_fd, TCSANOW, &tty);
    
    return 0;
}

void komaru_gps_update(void) {
    char buf[256];
    int bytes = read(gps_fd, buf, sizeof(buf) - 1);
    if(bytes <= 0) return;
    buf[bytes] = '\0';
    
    char *token = strtok(buf, "\n");
    while(token) {
        if(strncmp(token, "$GPGGA", 6) == 0) {
            sscanf(token, "$GPGGA,%f,%f,%c,%f,%c,%d,%d,%f,%f",
                &last_data.time, &last_data.latitude, &last_data.lat_dir,
                &last_data.longitude, &last_data.lon_dir, &last_data.fix_quality,
                &last_data.satellites, &last_data.altitude);
        }
        token = strtok(NULL, "\n");
    }
}

gps_data_t komaru_gps_get_data(void) { return last_data; }

int komaru_gps_has_fix(void) { return last_data.fix_quality > 0; }
