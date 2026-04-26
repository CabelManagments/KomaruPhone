#ifndef KOMARU_CAMERA_H
#define KOMARU_CAMERA_H

int komaru_camera_init(void);
int komaru_camera_take_photo(const char *filename);
int komaru_camera_record_video(const char *filename, int seconds);
void komaru_camera_release(void);

#endif
