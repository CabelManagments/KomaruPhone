#include "komaru_audio.h"
#include <stdio.h>
#include <stdlib.h>

static int volume = 70;
static int muted = 0;

int komaru_audio_init(void) {
    system("amixer sset Master 70%");
    return 0;
}

void komaru_audio_set_volume(int percent) {
    if(percent < 0) percent = 0;
    if(percent > 100) percent = 100;
    volume = percent;
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "amixer sset Master %d%%", percent);
    system(cmd);
}

int komaru_audio_get_volume(void) { return volume; }

void komaru_audio_mute(void) {
    muted = 1;
    system("amixer sset Master mute");
}

void komaru_audio_unmute(void) {
    muted = 0;
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "amixer sset Master %d%%", volume);
    system(cmd);
}

int komaru_audio_is_muted(void) { return muted; }

void komaru_audio_beep(int freq, int ms) {
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "speaker-test -t sine -f %d -l 1 > /dev/null 2>&1 & sleep 0.1 && killall speaker-test", freq);
    system(cmd);
    usleep(ms * 1000);
}
