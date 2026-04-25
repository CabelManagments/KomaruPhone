#ifndef KOMARU_ANIMATION_H
#define KOMARU_ANIMATION_H

#include <stdint.h>

typedef enum {
    KOMARU_EASE_LINEAR,
    KOMARU_EASE_IN_OUT_QUAD,
    KOMARU_EASE_OUT_BACK,    // пружинка
    KOMARU_EASE_OUT_ELASTIC  // как в iOS
} komaru_easing_t;

typedef struct {
    int active;
    int start_x, start_y, start_w, start_h;
    int target_x, target_y, target_w, target_h;
    int current_x, current_y, current_w, current_h;
    unsigned long start_time;
    int duration_ms;
    komaru_easing_t easing;
    void (*on_complete)(void);
} komaru_anim_zoom_t;

void komaru_animation_zoom_start(komaru_anim_zoom_t *anim, int dur, komaru_easing_t ease);
int komaru_animation_zoom_update(komaru_anim_zoom_t *anim, unsigned long now);
float komaru_animation_ease(float t, komaru_easing_t easing);

#endif
