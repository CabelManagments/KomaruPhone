#include "komaru_sensors.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct {
    float x, y, z;
} sensor_data_t;

static sensor_data_t accel = {0, 0, 0};
static sensor_data_t gyro = {0, 0, 0};
static sensor_data_t magnet = {0, 0, 0};
static int rotation = 0;  // 0=portrait, 1=landscape_left, 2=landscape_right

static void parse_sensor_file(const char *path, sensor_data_t *data) {
    FILE *fp = fopen(path, "r");
    if(fp) {
        fscanf(fp, "%f %f %f", &data->x, &data->y, &data->z);
        fclose(fp);
    }
}

void komaru_sensors_init(void) {
    // В реальности данные читаются из /sys/class/iio_device/
    // Пока заглушка с тестовыми значениями
}

void komaru_sensors_update(void) {
    // Реальное чтение
    parse_sensor_file("/sys/class/iio_device/accel/data", &accel);
    parse_sensor_file("/sys/class/iio_device/gyro/data", &gyro);
    parse_sensor_file("/sys/class/iio_device/magnet/data", &magnet);
    
    // Определяем ориентацию по акселерометру
    float ax = accel.x;
    float ay = accel.y;
    
    if(fabs(ax) > fabs(ay)) {
        if(ax > 0) rotation = 1;   // landscape left
        else rotation = 2;         // landscape right
    } else {
        rotation = 0;               // portrait
    }
}

float komaru_sensors_get_tilt(void) {
    return atan2f(accel.y, accel.x) * 180 / M_PI;
}

int komaru_sensors_get_rotation(void) {
    return rotation;
}

void komaru_sensors_get_accel(float *x, float *y, float *z) {
    *x = accel.x; *y = accel.y; *z = accel.z;
}
