#include "komaru_dialog.h"
#include "komaru_display.h"
#include "komaru_buttons.h"
#include <stdio.h>
#include <string.h>

static const char *btn_ok[] = {"OK"};
static const char *btn_ok_cancel[] = {"OK", "Cancel"};
static const char *btn_yes_no[] = {"Yes", "No"};

int komaru_dialog_show(const char *title, const char *message, dialog_type_t type) {
    const char **buttons = NULL;
    int btn_count = 0;
    
    switch(type) {
        case DIALOG_OK:
            buttons = btn_ok;
            btn_count = 1;
            break;
        case DIALOG_OK_CANCEL:
            buttons = btn_ok_cancel;
            btn_count = 2;
            break;
        case DIALOG_YES_NO:
            buttons = btn_yes_no;
            btn_count = 2;
            break;
    }
    
    int selected = 0;
    int running = 1;
    dialog_result_t result = DIALOG_RETURN_CANCEL;
    
    while(running) {
        komaru_display_clear();
        
        // Рамка
        komaru_display_box(5, 5, 118, 54, 0);
        
        // Заголовок
        komaru_display_string(title, 55 - strlen(title)*3, 12);
        
        // Сообщение (перенос строк)
        char msg_buf[64];
        strncpy(msg_buf, message, 63);
        char *line = strtok(msg_buf, "\n");
        int y = 25;
        while(line && y < 50) {
            komaru_display_string(line, 55 - strlen(line)*3, y);
            y += 8;
            line = strtok(NULL, "\n");
        }
        
        // Кнопки
        int btn_w = 40;
        int start_x = (128 - (btn_count * btn_w + (btn_count-1) * 10)) / 2;
        for(int i = 0; i < btn_count; i++) {
            int x = start_x + i * (btn_w + 10);
            if(i == selected) {
                komaru_display_box(x, 45, btn_w, 12, 1);
                komaru_display_string(buttons[i], x + 5, 47);
            } else {
                komaru_display_box(x, 45, btn_w, 12, 0);
                komaru_display_string(buttons[i], x + 5, 47);
            }
        }
        
        komaru_display_update();
        
        int btn = komaru_buttons_read();
        if(btn & BTN_VOLUME_UP) {
            selected = (selected + 1) % btn_count;
            komaru_vibrator_on(20);
        }
        if(btn & BTN_VOLUME_DOWN) {
            selected = (selected - 1 + btn_count) % btn_count;
            komaru_vibrator_on(20);
        }
        if(btn & BTN_POWER) {
            if(type == DIALOG_OK) result = DIALOG_RETURN_OK;
            else if(type == DIALOG_OK_CANCEL) result = (selected == 0) ? DIALOG_RETURN_OK : DIALOG_RETURN_CANCEL;
            else if(type == DIALOG_YES_NO) result = (selected == 0) ? DIALOG_RETURN_YES : DIALOG_RETURN_NO;
            running = 0;
        }
    }
    
    return result;
}

void komaru_dialog_message(const char *title, const char *message) {
    komaru_dialog_show(title, message, DIALOG_OK);
}
