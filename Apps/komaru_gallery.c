#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_storage.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define GALLERY_DIR "/home/komaru/pics"
#define MAX_FILES 50
#define MAX_PATH 256

static char files[MAX_FILES][MAX_PATH];
static int file_count = 0;
static int selected = 0;

static void scan_images(void) {
    system("mkdir -p " GALLERY_DIR);
    DIR *dir = opendir(GALLERY_DIR);
    if(!dir) return;
    
    file_count = 0;
    struct dirent *entry;
    while((entry = readdir(dir)) && file_count < MAX_FILES) {
        if(strstr(entry->d_name, ".jpg") || strstr(entry->d_name, ".png")) {
            strcpy(files[file_count], entry->d_name);
            file_count++;
        }
    }
    closedir(dir);
}

static void draw_image_preview(int idx) {
    komaru_display_string(files[idx], 30, 20);
    komaru_display_string("[PREVIEW]", 40, 40);
}

void komaru_gallery_run(void) {
    scan_images();
    int running = 1;
    
    while(running) {
        komaru_display_clear();
        
        komaru_display_string("Gallery", 45, 2);
        
        if(file_count == 0) {
            komaru_display_string("No images", 40, 30);
            komaru_display_string("Put .jpg in", 35, 40);
            komaru_display_string(GALLERY_DIR, 20, 50);
        } else {
            draw_image_preview(selected);
            komaru_display_string("Vol+/- select", 5, 60);
        }
        
        komaru_display_string("Power exit", 70, 60);
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_VOLUME_UP) {
            selected = (selected + 1) % file_count;
        }
        if(btn & BTN_VOLUME_DOWN) {
            selected = (selected - 1 + file_count) % file_count;
        }
        if(btn & BTN_POWER) {
            running = 0;
        }
        
        usleep(50000);
    }
}
