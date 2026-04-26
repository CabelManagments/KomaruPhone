#ifndef KOMARU_SERVICES_H
#define KOMARU_SERVICES_H

typedef struct komaru_service_t {
    char name[32];
    void (*start)(void);
    void (*stop)(void);
    int running;
    struct komaru_service_t *next;
} komaru_service_t;

int komaru_services_init(void);
void komaru_services_register(komaru_service_t *service);
void komaru_services_start_all(void);
void komaru_services_stop_all(void);
void komaru_services_start(const char *name);
void komaru_services_stop(const char *name);

#endif
