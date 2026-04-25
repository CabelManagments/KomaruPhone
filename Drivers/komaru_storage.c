#include "komaru_storage.h"
#include <sys/statvfs.h>

long long komaru_storage_get_free_space(const char *path) {
    struct statvfs stat;
    if(statvfs(path, &stat) != 0) return -1;
    return (long long)stat.f_bavail * stat.f_frsize;
}

long long komaru_storage_get_total_space(const char *path) {
    struct statvfs stat;
    if(statvfs(path, &stat) != 0) return -1;
    return (long long)stat.f_blocks * stat.f_frsize;
}
