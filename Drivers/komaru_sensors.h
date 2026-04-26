#ifndef KOMARU_SENSORS_H
#define KOMARU_SENSORS_H

typedef struct { float x, y, z; } sensor_data_t;

void komaru_sensors_init(void);
void komaru_sensors_update(void);
sensor_data_t komaru_sensors_get_accel(void);
sensor_data_t komaru_sensors_get_gyro(void);
sensor_data_t komaru_sensors_get_magnet(void);
int komaru_sensors_get_rotation(void);

#endif
