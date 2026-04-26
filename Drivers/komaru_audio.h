#ifndef KOMARU_AUDIO_H
#define KOMARU_AUDIO_H

int komaru_audio_init(void);
void komaru_audio_set_volume(int percent);
int komaru_audio_get_volume(void);
void komaru_audio_mute(void);
void komaru_audio_unmute(void);
int komaru_audio_is_muted(void);
void komaru_audio_beep(int freq, int ms);

#endif
