#include "emu_drivers/komaru_display.h"
#include "emu_drivers/komaru_buttons.h"
#include "emu_drivers/komaru_power.h"
#include "emu_drivers/komaru_vibrator.h"
#include "emu_drivers/komaru_notify.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    komaru_display_init();
    komaru_buttons_init();
    komaru_vibrator_init();
    komaru_notify_init();
    
    komaru_notify_show("System", "Emulator ready");
    
    int running = 1;
    const int fps = 30;
    const int frame_delay = 1000 / fps;
    
    while(running) {
        komaru_display_clear();
        
        komaru_display_string("KomaruPhone v0.4", 15, 10);
        
        char buf[32];
        snprintf(buf, sizeof(buf), "Battery: %d%%", komaru_power_get_battery_level());
        komaru_display_string(buf, 15, 30);
        
        komaru_display_string("Press Power (Enter)", 5, 50);
        komaru_display_string("Vol +/- arrows", 10, 62);
        
        komaru_notify_render();
        komaru_display_update();
        komaru_notify_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_POWER) {
            printf("Power pressed — exiting\n");
            running = 0;
        }
        if(btn & BTN_VOLUME_UP) printf("Volume UP\n");
        if(btn & BTN_VOLUME_DOWN) printf("Volume DOWN\n");
        if(btn & BTN_PROGRAM) printf("Program button\n");
        
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) running = 0;
        }
        
        SDL_Delay(frame_delay);
    }
    
    return 0;
}
