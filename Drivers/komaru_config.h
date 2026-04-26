#ifndef KOMARU_CONFIG_H
#define KOMARU_CONFIG_H

int komaru_config_load(const char *path);
int komaru_config_save(const char *path);
int komaru_config_get_int(const char *key, int default_val);
void komaru_config_set_int(const char *key, int val);
const char* komaru_config_get_string(const char *key, const char *default_val);
void komaru_config_set_string(const char *key, const char *val);

#endif
