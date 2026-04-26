#include "komaru_log.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

#define MAX_LOG_ENTRIES 100
#define MAX_LOG_LEN 256

static char log_buffer[MAX_LOG_ENTRIES][MAX_LOG_LEN];
static int log_head = 0;
static int log_count = 0;
static log_level_t current_level = LOG_INFO;

static const char* level_str[] = {"DEBUG", "INFO", "WARN", "ERROR"};

void komaru_log_init(void) {
    log_head = 0;
    log_count = 0;
}

void komaru_log(log_level_t level, const char *tag, const char *fmt, ...) {
    if(level < current_level) return;
    
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    
    char msg[MAX_LOG_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);
    
    snprintf(log_buffer[log_head], MAX_LOG_LEN, "[%02d:%02d:%02d] [%s] [%s] %s",
             t->tm_hour, t->tm_min, t->tm_sec, level_str[level], tag, msg);
    
    log_head = (log_head + 1) % MAX_LOG_ENTRIES;
    if(log_count < MAX_LOG_ENTRIES) log_count++;
    
    printf("%s\n", log_buffer[(log_head - 1 + MAX_LOG_ENTRIES) % MAX_LOG_ENTRIES]);
}

void komaru_log_set_level(log_level_t level) {
    current_level = level;
}

void komaru_log_dump(void) {
    int start = (log_head - log_count + MAX_LOG_ENTRIES) % MAX_LOG_ENTRIES;
    for(int i = 0; i < log_count; i++) {
        int idx = (start + i) % MAX_LOG_ENTRIES;
        printf("%s\n", log_buffer[idx]);
    }
}
