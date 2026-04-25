#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_storage.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define NOTES_DIR "/home/komaru/notes"
#define MAX_NOTES 50
#define MAX_TITLE 64
#define MAX_CONTENT 4096

typedef struct {
    char title[MAX_TITLE];
    char content[MAX_CONTENT];
    int modified;
} note_t;

static note_t current_note;
static char note_list[MAX_NOTES][MAX_TITLE];
static int note_count = 0;

void notes_load_list(void) {
    DIR *dir = opendir(NOTES_DIR);
    if(!dir) {
        system("mkdir -p " NOTES_DIR);
        dir = opendir(NOTES_DIR);
    }
    
    struct dirent *entry;
    note_count = 0;
    while((entry = readdir(dir)) && note_count < MAX_NOTES) {
        if(strstr(entry->d_name, ".md")) {
            strncpy(note_list[note_count], entry->d_name, MAX_TITLE);
            note_list[note_count][strlen(entry->d_name)-3] = '\0';
            note_count++;
        }
    }
    closedir(dir);
}

void notes_save(note_t *note) {
    char path[256];
    snprintf(path, sizeof(path), NOTES_DIR "/%s.md", note->title);
    FILE *fp = fopen(path, "w");
    if(fp) {
        fprintf(fp, "%s", note->content);
        fclose(fp);
        note->modified = 0;
    }
}

void notes_load(note_t *note, const char *title) {
    char path[256];
    snprintf(path, sizeof(path), NOTES_DIR "/%s.md", title);
    FILE *fp = fopen(path, "r");
    if(fp) {
        fread(note->content, 1, MAX_CONTENT-1, fp);
        note->content[MAX_CONTENT-1] = '\0';
        fclose(fp);
    } else {
        strcpy(note->content, "# Новая заметка\n\nВведите текст...");
    }
    strcpy(note->title, title);
    note->modified = 0;
}

void notes_render_preview(note_t *note, int *scroll) {
    komaru_display_clear();
    komaru_display_string(note->title, 5, 5);
    komaru_display_string("---", 5, 20);
    
    // Показываем первые строки
    int y = 35 - *scroll;
    const char *p = note->content;
    char line[64];
    int line_len = 0;
    
    while(*p && y < 120) {
        if(*p == '\n' || line_len >= 60) {
            line[line_len] = '\0';
            komaru_display_string(line, 5, y);
            y += 12;
            line_len = 0;
        } else {
            line[line_len++] = *p;
        }
        p++;
    }
}

void komaru_notes_run(void) {
    int selected = 0;
    int scroll = 0;
    int editing = 0;
    int running = 1;
    
    notes_load_list();
    
    if(note_count == 0) {
        strcpy(current_note.title, "Welcome");
        strcpy(current_note.content, "# KomaruNotes\n\nДвойные скобки [[создают]] связи.");
        notes_save(&current_note);
        notes_load_list();
    }
    
    notes_load(&current_note, note_list[0]);
    
    while(running) {
        if(!editing) {
            // Режим просмотра
            notes_render_preview(&current_note, &scroll);
            komaru_display_string("Edit=Vol+", 5, 125);
        } else {
            // Режим редактирования (упрощённо)
            komaru_display_clear();
            komaru_display_string(">", 0, 20);
            komaru_display_string(current_note.content, 10, 20);
        }
        
        int btn = komaru_buttons_read();
        if(btn & BTN_VOLUME_UP) {
            if(editing) {
                // переключение заметок
                selected = (selected + 1) % note_count;
                notes_load(&current_note, note_list[selected]);
            } else {
                scroll += 10;
            }
        }
        if(btn & BTN_VOLUME_DOWN) {
            if(editing) {
                selected = (selected - 1 + note_count) % note_count;
                notes_load(&current_note, note_list[selected]);
            } else {
                scroll -= 10;
                if(scroll < 0) scroll = 0;
            }
        }
        if(btn & BTN_POWER) {
            if(editing) {
                notes_save(&current_note);
                editing = 0;
            } else {
                editing = 1;
            }
        }
        if(btn & BTN_PROG) {
            running = 0;
        }
        
        komaru_display_update();
        usleep(100000);
    }
}
