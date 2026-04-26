#include "komaru_config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONFIG_KEYS 32
#define MAX_KEY_LEN 32
#define MAX_VAL_LEN 128

typedef struct {
    char key[MAX_KEY_LEN];
    char val[MAX_VAL_LEN];
} config_entry_t;

static config_entry_t config[MAX_CONFIG_KEYS];
static int config_count = 0;

int komaru_config_load(const char *path) {
    FILE *fp = fopen(path, "r");
    if(!fp) return -1;
    
    char line[256];
    while(fgets(line, sizeof(line), fp) && config_count < MAX_CONFIG_KEYS) {
        char *eq = strchr(line, '=');
        if(eq) {
            *eq = '\0';
            strncpy(config[config_count].key, line, MAX_KEY_LEN - 1);
            strncpy(config[config_count].val, eq + 1, MAX_VAL_LEN - 1);
            config[config_count].val[strcspn(config[config_count].val, "\n")] = '\0';
            config_count++;
        }
    }
    fclose(fp);
    return 0;
}

int komaru_config_save(const char *path) {
    FILE *fp = fopen(path, "w");
    if(!fp) return -1;
    
    for(int i = 0; i < config_count; i++) {
        fprintf(fp, "%s=%s\n", config[i].key, config[i].val);
    }
    fclose(fp);
    return 0;
}

static config_entry_t* find_entry(const char *key) {
    for(int i = 0; i < config_count; i++) {
        if(strcmp(config[i].key, key) == 0) return &config[i];
    }
    return NULL;
}

int komaru_config_get_int(const char *key, int default_val) {
    config_entry_t *e = find_entry(key);
    if(e) return atoi(e->val);
    return default_val;
}

void komaru_config_set_int(const char *key, int val) {
    config_entry_t *e = find_entry(key);
    char buf[16];
    snprintf(buf, sizeof(buf), "%d", val);
    if(e) {
        strncpy(e->val, buf, MAX_VAL_LEN - 1);
    } else if(config_count < MAX_CONFIG_KEYS) {
        strncpy(config[config_count].key, key, MAX_KEY_LEN - 1);
        strncpy(config[config_count].val, buf, MAX_VAL_LEN - 1);
        config_count++;
    }
}

const char* komaru_config_get_string(const char *key, const char *default_val) {
    config_entry_t *e = find_entry(key);
    if(e) return e->val;
    return default_val;
}

void komaru_config_set_string(const char *key, const char *val) {
    config_entry_t *e = find_entry(key);
    if(e) {
        strncpy(e->val, val, MAX_VAL_LEN - 1);
    } else if(config_count < MAX_CONFIG_KEYS) {
        strncpy(config[config_count].key, key, MAX_KEY_LEN - 1);
        strncpy(config[config_count].val, val, MAX_VAL_LEN - 1);
        config_count++;
    }
}
