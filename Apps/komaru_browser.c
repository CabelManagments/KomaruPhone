#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_wifi.h"
#include "komaru_touch.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_URL 256
#define MAX_HTML 8192

static char current_url[MAX_URL] = "http://komaru.phone";
static char page_title[128] = "KomaruBrowser";
static int scroll_y = 0;
static int running = 1;

static const char *bookmarks[] = {
    "http://komaru.phone",
    "http://google.com",
    "http://github.com",
    "http://wikipedia.org",
    NULL
};

static void draw_address_bar(void) {
    komaru_display_box(0, 0, 128, 12, 1);
    komaru_display_string(current_url, 2, 2);
}

static void draw_content(void) {
    komaru_display_string(page_title, 2, 14);
    komaru_display_string("Press Power to exit", 2, 50);
    komaru_display_string("Vol+/- scroll", 2, 60);
}

static void draw_bookmarks(void) {
    komaru_display_string("Bookmarks", 40, 14);
    for(int i = 0; bookmarks[i] != NULL; i++) {
        if(i * 8 + 22 < 64) {
            komaru_display_string(bookmarks[i], 5, 22 + i * 8);
        }
    }
}

void komaru_browser_run(void) {
    running = 1;
    
    while(running) {
        komaru_display_clear();
        
        draw_address_bar();
        
        if(strlen(current_url) > 0) {
            draw_content();
        } else {
            draw_bookmarks();
        }
        
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_POWER) {
            running = 0;
        }
        if(btn & BTN_VOLUME_UP) {
            scroll_y += 5;
            if(scroll_y < 0) scroll_y = 0;
        }
        if(btn & BTN_VOLUME_DOWN) {
            scroll_y -= 5;
        }
        
        usleep(50000);
    }
}
