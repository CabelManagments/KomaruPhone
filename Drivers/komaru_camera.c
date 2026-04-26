#include "komaru_camera.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int camera_ready = 0;

int komaru_camera_init(void) {
    FILE *fp = popen("v4l2-ctl --list-devices 2>/dev/null | grep -c /dev/video", "r");
    char buf[8];
    if(fgets(buf, sizeof(buf), fp)) {
        camera_ready = atoi(buf) > 0;
    }
    pclose(fp);
    return camera_ready ? 0 : -1;
}

int komaru_camera_take_photo(const char *filename) {
    if(!camera_ready) return -1;
    
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "fswebcam -r 640x480 --no-banner %s", filename);
    return system(cmd);
}

int komaru_camera_record_video(const char *filename, int seconds) {
    if(!camera_ready) return -1;
    
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "ffmpeg -f v4l2 -i /dev/video0 -t %d %s", seconds, filename);
    return system(cmd);
}

void komaru_camera_release(void) {
    camera_ready = 0;
}
