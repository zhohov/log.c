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

    log_level_t *current = log_level_info(level);
    printf("[%s] %s:%d %s\n", current->p_name, file, line, fmt);

    return 0;
}

