#include "log.h"
#include <stdio.h>

int set_log_level(int level)
{
    if (level > log_level || level < 0) {
        return -1;
    }
    log_level = level;
    return 0;
}

log_level_t *log_level_info(int level)
{
    return &log_levels[level];
}

int log_message(int level, char *fmt, const char *file, int line)
{
    if (level > log_level) {
        return -1;
    }

    FILE *log;
    log_level_t *log_info = log_level_info(level);

    if (log_file != NULL) {
        if ((log = fopen(log_file, "a")) != NULL) {
            fprintf(log, "[%s] %s:%d\n", log_info->l_name, file, line);
        }
        fclose(log);
    }

    printf("[%s] %s:%d %s\n", log_info->l_name, file, line, fmt);
    return 0;
}

int set_log_file(char *path)
{
    log_file = path;
    return 0;
}

