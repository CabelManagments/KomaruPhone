#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_power.h"
#include "komaru_notify.h"
#include "komaru_settings.h"
#include <unistd.h>
#include <sys/mount.h>

int main(void) {
    mount("proc", "/proc", "proc", 0, NULL);
    mount("sysfs", "/sys", "sysfs", 0, NULL);
    mount("devtmpfs", "/dev", "devtmpfs", 0, NULL);
    
    komaru_display_init();
    komaru_buttons_init();
    komaru_power_init();
    komaru_notify_init();
    
    komaru_display_clear();
    komaru_display_string("KomaruPhone v0.4", 20, 20);
    komaru_display_string("System ready", 35, 40);
    komaru_display_string("Press power", 40, 55);
    komaru_display_update();
    
    komaru_notify_show("System", "Welcome to KomaruOS");
    
    while(1) {
        int btn = komaru_buttons_read();
        if(btn & BTN_POWER) {
            komaru_display_clear();
            komaru_display_string("Shutting down...", 30, 30);
            komaru_display_update();
            komaru_power_shutdown();
            break;
        }
        
        komaru_notify_update();
        komaru_notify_render();
        komaru_display_update();
        usleep(100000);
    }
    
    return 0;
}
