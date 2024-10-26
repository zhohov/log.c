#include "log.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int get_current_time(char *buf, size_t size)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    if (local != NULL) {
        strftime(buf, size, "%H:%M:%S", local);
        return 0;
    }
    return -1;
}

char *trim_pathname(const char *pathname) {
    char *new_path = strstr(pathname, "src/");
    if (new_path != NULL) {
        return new_path;
    }
    return NULL;
}

char *fmt_pathname(const char *pathname, int line)
{
    char *new_path = trim_pathname(pathname);
    if (new_path != NULL) {
        size_t new_path_len = strlen(GRAY) + strlen(new_path) + strlen(RESET) + 4;
        char *path = malloc(new_path_len);
        if (path == NULL) {
            return NULL;
        }
        snprintf(path, new_path_len, "%s%s:%d%s", GRAY, new_path, line, RESET);
        return path;
    }
    return NULL;
}

int log_level_set(int level)
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
    if (level < log_level) {
        return -1;
    }

    FILE *log;
    char buf[128];
    
    log_level_t *log_info = log_level_info(level);
    get_current_time(buf, sizeof buf);

    if (log_file != NULL) {
        if ((log = fopen(log_file, "a")) != NULL) {
            fprintf(log, "%s [%s] %s:%d %s\n", buf, log_info->l_name, trim_pathname(file), line, fmt);
        }
        fclose(log);
    }

    printf("%s %s[%s]%s %s %s\n", buf, log_info->l_color, log_info->l_name, RESET, fmt_pathname(file, line), fmt);

    return 0;
}

int log_file_set(char *path)
{
    log_file = path;
    log_info("set path for log file");
    return 0;
}

