#ifndef KOMARU_DIALOG_H
#define KOMARU_DIALOG_H

typedef enum {
    DIALOG_OK,
    DIALOG_OK_CANCEL,
    DIALOG_YES_NO
} dialog_type_t;

typedef enum {
    DIALOG_RETURN_OK,
    DIALOG_RETURN_CANCEL,
    DIALOG_RETURN_YES,
    DIALOG_RETURN_NO
} dialog_result_t;

int komaru_dialog_show(const char *title, const char *message, dialog_type_t type);
void komaru_dialog_message(const char *title, const char *message);

#endif
