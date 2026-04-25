#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int camera_initialized = 0;

int komaru_camera_init(void) {
    // gst-launch-1.0 или v4l2-ctl проверка
    camera_initialized = 1;
    return 0;
}

int komaru_camera_take_photo(const char *filename) {
    if(!camera_initialized) return -1;
    
    char cmd[256];
    snprintf(cmd, sizeof(cmd), 
             "fswebcam -r 640x480 --no-banner %s", filename);
    return system(cmd);
}

void komaru_camera_release(void) {
    camera_initialized = 0;
}
