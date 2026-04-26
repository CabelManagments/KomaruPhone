#include "komaru_sensors.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static sensor_data_t accel = {0};
static sensor_data_t gyro = {0};
static sensor_data_t magn = {0};

void komaru_sensors_init(void) {
    system("modprobe mpu6050 2>/dev/null");
}

static void read_sensor(const char *path, sensor_data_t *data) {
    FILE *fp = fopen(path, "r");
    if(fp) {
        fscanf(fp, "%f %f %f", &data->x, &data->y, &data->z);
        fclose(fp);
    }
}

void komaru_sensors_update(void) {
    read_sensor("/sys/class/iio_device/accel/data", &accel);
    read_sensor("/sys/class/iio_device/gyro/data", &gyro);
    read_sensor("/sys/class/iio_device/magn/data", &magn);
}

sensor_data_t komaru_sensors_get_accel(void) { return accel; }
sensor_data_t komaru_sensors_get_gyro(void) { return gyro; }
sensor_data_t komaru_sensors_get_magnet(void) { return magn; }

int komaru_sensors_get_rotation(void) {
    if(accel.x > 5) return 1;  // landscape
    if(accel.x < -5) return 2; // landscape reverse
    return 0;                   // portrait
}
