#include "komaru_vibrator.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define VIBRATOR_GPIO 18  // PWM пин для вибрации
#define VIBRATOR_PATH "/sys/class/pwm/pwmchip0"

static int vibrator_enabled = 1;

void komaru_vibrator_init(void) {
    // Инициализация PWM для вибромотора
    FILE *fp = fopen(VIBRATOR_PATH "/export", "w");
    if(fp) {
        fprintf(fp, "%d", VIBRATOR_GPIO);
        fclose(fp);
    }
    
    fp = fopen(VIBRATOR_PATH "/pwm0/period", "w");
    if(fp) {
        fprintf(fp, "2000000");  // 2ms период
        fclose(fp);
    }
}

void komaru_vibrator_on(int ms) {
    if(!vibrator_enabled) return;
    
    FILE *fp = fopen(VIBRATOR_PATH "/pwm0/duty_cycle", "w");
    if(fp) {
        fprintf(fp, "1000000");  // 50% duty cycle
        fclose(fp);
    }
    
    fp = fopen(VIBRATOR_PATH "/pwm0/enable", "w");
    if(fp) {
        fprintf(fp, "1");
        fclose(fp);
    }
    
    usleep(ms * 1000);
    
    fp = fopen(VIBRATOR_PATH "/pwm0/enable", "w");
    if(fp) {
        fprintf(fp, "0");
        fclose(fp);
    }
}

void komaru_vibrator_set_enabled(int enabled) {
    vibrator_enabled = enabled;
}

void komaru_vibrator_pattern(int *pattern, int count) {
    for(int i = 0; i < count; i++) {
        komaru_vibrator_on(pattern[i]);
        usleep(50000);  // пауза между импульсами
    }
}
