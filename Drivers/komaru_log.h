#ifndef KOMARU_LOG_H
#define KOMARU_LOG_H

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} log_level_t;

void komaru_log_init(void);
void komaru_log(log_level_t level, const char *tag, const char *fmt, ...);
void komaru_log_set_level(log_level_t level);
void komaru_log_dump(void);

#define LOG_D(tag, fmt, ...) komaru_log(LOG_DEBUG, tag, fmt, ##__VA_ARGS__)
#define LOG_I(tag, fmt, ...) komaru_log(LOG_INFO, tag, fmt, ##__VA_ARGS__)
#define LOG_W(tag, fmt, ...) komaru_log(LOG_WARN, tag, fmt, ##__VA_ARGS__)
#define LOG_E(tag, fmt, ...) komaru_log(LOG_ERROR, tag, fmt, ##__VA_ARGS__)

#endif
