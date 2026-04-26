#include "emu_drivers/komaru_display.h"
#include "emu_drivers/komaru_buttons.h"
#include "emu_drivers/komaru_power.h"
#include "emu_drivers/komaru_vibrator.h"
#include "emu_drivers/komaru_notify.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    komaru_display_init();
    komaru_buttons_init();
    
    int running = 1;
    while(running) {
        komaru_display_clear();
        komaru_display_string("KomaruPhone v0.4", 2, 2);
        char buf[32];
        snprintf(buf, sizeof(buf), "Battery: %d%%", komaru_power_get_battery_level());
        komaru_display_string(buf, 2, 4);
        komaru_display_string("Press p=power u=vol+", 2, 6);
        komaru_display_string("d=vol- r=prog q=quit", 2, 7);
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_POWER) {
            komaru_display_string("Shutting down...", 2, 10);
            komaru_display_update();
            running = 0;
        }
        if(btn & BTN_VOLUME_UP) printf("Volume UP\n");
        if(btn & BTN_VOLUME_DOWN) printf("Volume DOWN\n");
        if(btn & BTN_PROGRAM) printf("Program button\n");
    }
    
    return 0;
}
