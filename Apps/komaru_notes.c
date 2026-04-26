#include "komaru_display.h"
#include "komaru_buttons.h"
#include "komaru_storage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NOTES_DIR "/home/komaru/notes"
#define MAX_NOTES 20
#define MAX_TITLE 32
#define MAX_CONTENT 1024

static char notes[MAX_NOTES][MAX_TITLE];
static int note_count = 0;
static int selected = 0;
static int editing = 0;
static char current_content[MAX_CONTENT] = "";
static int cursor_pos = 0;

static void load_notes(void) {
    system("mkdir -p " NOTES_DIR);
    FILE *fp = fopen(NOTES_DIR "/index.txt", "r");
    if(fp) {
        note_count = 0;
        while(fgets(notes[note_count], MAX_TITLE, fp) && note_count < MAX_NOTES) {
            notes[note_count][strcspn(notes[note_count], "\n")] = '\0';
            note_count++;
        }
        fclose(fp);
    }
    if(note_count == 0) {
        strcpy(notes[0], "Welcome");
        note_count = 1;
    }
}

static void save_note(int idx) {
    char path[256];
    snprintf(path, sizeof(path), NOTES_DIR "/%s.txt", notes[idx]);
    FILE *fp = fopen(path, "w");
    if(fp) {
        fprintf(fp, "%s", current_content);
        fclose(fp);
    }
}

static void load_note(int idx) {
    char path[256];
    snprintf(path, sizeof(path), NOTES_DIR "/%s.txt", notes[idx]);
    FILE *fp = fopen(path, "r");
    if(fp) {
        fread(current_content, 1, MAX_CONTENT - 1, fp);
        current_content[MAX_CONTENT - 1] = '\0';
        fclose(fp);
    } else {
        strcpy(current_content, "New note...");
    }
    cursor_pos = strlen(current_content);
}

void komaru_notes_run(void) {
    load_notes();
    load_note(selected);
    
    int running = 1;
    while(running) {
        komaru_display_clear();
        
        if(!editing) {
            // Список заметок
            komaru_display_string("Notes", 50, 2);
            for(int i = 0; i < note_count && i < 6; i++) {
                if(i == selected) {
                    komaru_display_string(">", 2, 14 + i * 8);
                }
                komaru_display_string(notes[i], 12, 14 + i * 8);
            }
            komaru_display_string("Vol+/- select", 5, 60);
            komaru_display_string("Power edit", 5, 68);
        } else {
            // Редактирование
            komaru_display_string(notes[selected], 2, 2);
            komaru_display_string("---", 2, 12);
            komaru_display_string(current_content, 2, 20);
            komaru_display_string("Power save", 5, 62);
        }
        
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(!editing) {
            if(btn & BTN_VOLUME_UP) {
                selected = (selected + 1) % note_count;
                load_note(selected);
            }
            if(btn & BTN_VOLUME_DOWN) {
                selected = (selected - 1 + note_count) % note_count;
                load_note(selected);
            }
            if(btn & BTN_POWER) {
                editing = 1;
            }
            if(btn & BTN_PROGRAM) {
                running = 0;
            }
        } else {
            if(btn & BTN_POWER) {
                save_note(selected);
                editing = 0;
            }
            if(btn & BTN_VOLUME_UP) {
                // добавить символ (заглушка)
                strcat(current_content, "a");
                cursor_pos++;
            }
        }
        
        usleep(50000);
    }
}
