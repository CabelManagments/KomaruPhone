#include "komaru_display.h"
#include "komaru_buttons.h"
#include <dirent.h>
#include <string.h>

static char current_file[256] = "";
static int file_index = 0;
static char **files = NULL;
static int file_count = 0;

void gallery_load_images(void) {
    DIR *dir = opendir("/sdcard/DCIM");
    if(!dir) return;
    
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if(strstr(entry->d_name, ".jpg") || strstr(entry->d_name, ".png")) {
            file_count++;
        }
    }
    closedir(dir);
    
    // Проще сразу показать заглушку
}

void komaru_gallery_run(void) {
    komaru_display_clear();
    komaru_display_string("KomaruGallery", 20, 20);
    komaru_display_string("Нет фото", 40, 80);
    komaru_display_string("Нажмите Power", 20, 200);
    
    while(!(komaru_buttons_read() & BTN_POWER));
}
