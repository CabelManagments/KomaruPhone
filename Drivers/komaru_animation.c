#include "komaru_animation.h"
#include <math.h>
#include <stdlib.h>

float komaru_animation_ease(float t, komaru_easing_t easing) {
    switch(easing) {
        case KOMARU_EASE_LINEAR:
            return t;
            
        case KOMARU_EASE_IN_OUT_QUAD:
            return t < 0.5 ? 2*t*t : 1 - pow(-2*t+2, 2)/2;
            
        case KOMARU_EASE_OUT_BACK: {
            float c1 = 1.70158;
            float c3 = c1 + 1;
            return 1 + c3 * pow(t-1, 3) + c1 * pow(t-1, 2);
        }
        
        case KOMARU_EASE_OUT_ELASTIC: {
            float c4 = (2 * M_PI) / 3;
            return t == 0 ? 0 : t == 1 ? 1 : pow(2, -10 * t) * sin((t * 10 - 0.75) * c4) + 1;
        }
        
        default:
            return t;
    }
}

void komaru_animation_zoom_start(komaru_anim_zoom_t *anim, int dur, komaru_easing_t ease) {
    if(!anim->active) return;
    
    anim->duration_ms = dur;
    anim->easing = ease;
    anim->start_time = get_timestamp_ms();  // нужна функция времени
    anim->current_x = anim->start_x;
    anim->current_y = anim->start_y;
    anim->current_w = anim->start_w;
    anim->current_h = anim->start_h;
}

int komaru_animation_zoom_update(komaru_anim_zoom_t *anim, unsigned long now) {
    if(!anim->active) return 0;
    
    float progress = (float)(now - anim->start_time) / anim->duration_ms;
    if(progress >= 1.0) {
        // Анимация закончена
        anim->active = 0;
        if(anim->on_complete) anim->on_complete();
        return 0;
    }
    
    float eased = komaru_animation_ease(progress, anim->easing);
    
    // Интерполяция
    anim->current_x = anim->start_x + (anim->target_x - anim->start_x) * eased;
    anim->current_y = anim->start_y + (anim->target_y - anim->start_y) * eased;
    anim->current_w = anim->start_w + (anim->target_w - anim->start_w) * eased;
    anim->current_h = anim->start_h + (anim->target_h - anim->start_h) * eased;
    
    return 1; // анимация ещё идёт
}
