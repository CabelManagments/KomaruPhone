#include "komaru_buttons.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

static struct termios old_tio, new_tio;

int komaru_buttons_init(void) {
    tcgetattr(STDIN_FILENO, &old_tio);
    new_tio = old_tio;
    new_tio.c_lflag &= (~ICANON & ~ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
    return 0;
}

int komaru_buttons_read(void) {
    char c;
    if(read(STDIN_FILENO, &c, 1) != 1) return 0;
    
    int btn = 0;
    switch(c) {
        case 'p': case 'P': btn |= BTN_POWER; break;
        case 'u': case 'U': btn |= BTN_VOLUME_UP; break;
        case 'd': case 'D': btn |= BTN_VOLUME_DOWN; break;
        case 'r': case 'R': btn |= BTN_PROGRAM; break;
        case 'q': break;
    }
    return btn;
}

void komaru_buttons_cleanup(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
}
