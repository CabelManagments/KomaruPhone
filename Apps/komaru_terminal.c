#include "komaru_display.h"
#include "komaru_buttons.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static char command[64] = "";
static int cmd_len = 0;
static char output[512] = "";

static void execute_command(void) {
    if(strlen(command) == 0) return;
    
    FILE *fp = popen(command, "r");
    if(fp) {
        output[0] = '\0';
        char buf[64];
        while(fgets(buf, sizeof(buf), fp)) {
            strncat(output, buf, sizeof(output) - strlen(output) - 1);
        }
        pclose(fp);
    }
}

void komaru_terminal_run(void) {
    int running = 1;
    cmd_len = 0;
    command[0] = '\0';
    output[0] = '\0';
    
    while(running) {
        komaru_display_clear();
        komaru_display_string("Terminal", 45, 2);
        
        komaru_display_string("$", 2, 14);
        komaru_display_string(command, 10, 14);
        
        if(output[0] != '\0') {
            komaru_display_string(output, 2, 24);
        }
        
        komaru_display_string("Power exit", 70, 60);
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_POWER) {
            running = 0;
        }
        if(btn & BTN_PROGRAM) {
            execute_command();
        }
        
        usleep(50000);
    }
}
