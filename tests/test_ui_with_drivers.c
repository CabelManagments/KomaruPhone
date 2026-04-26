#include <SDL2/SDL.h>
#include "../Drivers/komaru_display.h"
#include "../Drivers/komaru_buttons.h"
#include "../Drivers/komaru_power.h"
#include "../Drivers/komaru_wifi.h"
#include "../Drivers/komaru_bluetooth.h"
#include "../Drivers/komaru_vibrator.h"
#include "../Drivers/komaru_notify.h"

#define SCREEN_W 128
#define SCREEN_H 64

SDL_Window *win;
SDL_Renderer *ren;
SDL_Texture *fb_texture;

uint8_t framebuffer[SCREEN_W * SCREEN_H];

void komaru_display_pixel(int x, int y, int on) {
    if(x<0||x>=SCREEN_W||y<0||y>=SCREEN_H) return;
    if(on) framebuffer[y*SCREEN_W + x] = 255;
    else framebuffer[y*SCREEN_W + x] = 0;
}

void komaru_display_update_soft(void) {
    SDL_UpdateTexture(fb_texture, NULL, framebuffer, SCREEN_W);
    SDL_RenderCopy(ren, fb_texture, NULL, NULL);
    SDL_RenderPresent(ren);
}

int komaru_buttons_read(void) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    int btn = 0;
    if(state[SDL_SCANCODE_UP]) btn |= BTN_VOLUME_UP;
    if(state[SDL_SCANCODE_DOWN]) btn |= BTN_VOLUME_DOWN;
    if(state[SDL_SCANCODE_RETURN]) btn |= BTN_POWER;
    if(state[SDL_SCANCODE_SPACE]) btn |= BTN_PROGRAM;
    return btn;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow("KomaruPhone Emulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           SCREEN_W*4, SCREEN_H*4, 0);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    fb_texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, SCREEN_W, SCREEN_H);
    
    komaru_display_init();
    komaru_buttons_init();
    komaru_vibrator_init();
    komaru_notify_init();
    
    komaru_display_clear();
    komaru_display_string("KomaruPhone", 20, 10);
    komaru_display_string("Press Power", 20, 30);
    komaru_notify_show("System", "Emulator ready");
    
    int running = 1;
    SDL_Event e;
    while(running) {
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) running = 0;
        }
        
        komaru_display_clear();
        
        komaru_display_string("KomaruPhone", 20, 10);
        komaru_display_string("Press Power", 20, 30);
        
        char buf[32];
        snprintf(buf, sizeof(buf), "Bat: %d%%", komaru_power_get_battery_level());
        komaru_display_string(buf, 10, 50);
        
        komaru_notify_render();
        
        komaru_display_update_soft();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_POWER) {
            printf("Power pressed — shutting down emulator\n");
            running = 0;
        }
        
        SDL_Delay(50);
    }
    
    SDL_DestroyTexture(fb_texture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
