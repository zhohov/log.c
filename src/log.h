#ifndef LOG_H
#define LOG_H

#include <stdio.h>

/*
 * #define	LOG_EMERG	0	system is unusable
 * #define	LOG_ALERT	1	action must be taken immediately
 * #define	LOG_CRIT	2	critical conditions
 * #define	LOG_ERR		3	error conditions
 * #define	LOG_WARNING	4	warning conditions
 * #define	LOG_NOTICE	5	normal but significant condition
 * #define	LOG_INFO	6	informational
 * #define	LOG_DEBUG	7	debug-level messages
 *
 * */

#define LOG_DEBUG 5 /* debug-level message */
#define LOG_INFO 4 /* informational message */
#define LOG_WARNING 3
#define LOG_ERROR 2
#define LOG_FATAL 1

#define log(level, fmt) log_message(level, fmt, __FILE__, __LINE__)
#define log_debug(fmt) log_message(LOG_DEBUG, fmt, __FILE__, __LINE__)
#define log_info(fmt) log_message(LOG_INFO, fmt, __FILE__, __LINE__)
#define log_warning(fmt) log_message(LOG_WARNING, fmt, __FILE__, __LINE__)
#define log_error(fmt) log_message(LOG_ERROR, fmt, __FILE__, __LINE__)
#define log_fatal(fmt) log_message(LOG_FATAL, fmt, __FILE__, __LINE__)

typedef struct
{
    const char *p_name;
    int p_code;
    const char *p_color;
} log_level_t;

static log_level_t log_levels[] = {
    { NULL },
    { "CRITICAL", LOG_FATAL, NULL },
    { "ERROR", LOG_ERROR, NULL },
    { "WARNING", LOG_WARNING, NULL },
    { "INFO", LOG_INFO, NULL },
    { "DEBUG", LOG_DEBUG, NULL },
    { NULL, -1, NULL },
};

/* default priority level for logs */
static int log_level = LOG_DEBUG;

static char *log_file = NULL;

/* get structure with current priority */
log_level_t *get_log_level(void);

/* Change current priority log level */
extern int set_log_level(int level);
extern int log_message(int level, char *fmt, const char *file, int line);

extern int set_file_path(char *path);
extern FILE *open_log_file(void);
extern int close_log_file(FILE *);

#endif /* LOG_H */

