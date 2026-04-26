#include "komaru_services.h"
#include <string.h>
#include <stdio.h>

static komaru_service_t *service_list = NULL;

int komaru_services_init(void) {
    service_list = NULL;
    return 0;
}

void komaru_services_register(komaru_service_t *service) {
    service->next = service_list;
    service_list = service;
}

void komaru_services_start_all(void) {
    komaru_service_t *s = service_list;
    while(s) {
        if(s->start && !s->running) {
            s->start();
            s->running = 1;
        }
        s = s->next;
    }
}

void komaru_services_stop_all(void) {
    komaru_service_t *s = service_list;
    while(s) {
        if(s->stop && s->running) {
            s->stop();
            s->running = 0;
        }
        s = s->next;
    }
}

void komaru_services_start(const char *name) {
    komaru_service_t *s = service_list;
    while(s) {
        if(strcmp(s->name, name) == 0 && s->start && !s->running) {
            s->start();
            s->running = 1;
            break;
        }
        s = s->next;
    }
}

void komaru_services_stop(const char *name) {
    komaru_service_t *s = service_list;
    while(s) {
        if(strcmp(s->name, name) == 0 && s->stop && s->running) {
            s->stop();
            s->running = 0;
            break;
        }
        s = s->next;
    }
}
