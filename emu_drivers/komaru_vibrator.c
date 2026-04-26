#include "komaru_vibrator.h"
#include <stdio.h>
#include <unistd.h>

static int enabled = 1;

void komaru_vibrator_init(void) { }
void komaru_vibrator_on(int ms) { if(enabled) printf("Vibration %dms\n", ms); }
void komaru_vibrator_set_enabled(int e) { enabled = e; }
void komaru_vibrator_pattern(int *pattern, int count) {
    for(int i=0; i<count; i++) komaru_vibrator_on(pattern[i]);
}
