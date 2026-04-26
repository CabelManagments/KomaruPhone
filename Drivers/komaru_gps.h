#ifndef KOMARU_GPS_H
#define KOMARU_GPS_H

typedef struct {
    float latitude, longitude;
    char lat_dir, lon_dir;
    float altitude;
    float time;
    int fix_quality;
    int satellites;
} gps_data_t;

int komaru_gps_init(void);
void komaru_gps_update(void);
gps_data_t komaru_gps_get_data(void);
int komaru_gps_has_fix(void);

#endif
