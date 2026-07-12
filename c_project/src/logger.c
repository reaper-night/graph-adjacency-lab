#include "logger.h"
#include <stdarg.h>
#include <time.h>
#include <stdio.h>

static LogLevel current_level = LOG_LEVEL_INFO;

void logger_init(void) {
    current_level = LOG_LEVEL_INFO;
}

void logger_set_level(LogLevel level) {
    current_level = level;
}

void logger_cleanup(void) {
}

void logger_log(LogLevel level, const char *format, ...) {
    if (level < current_level) {
        return;
    }

    time_t now = time(NULL);
    struct tm tm_info;
    
#ifdef _WIN32
    localtime_s(&tm_info, &now);
#else
    localtime_r(&now, &tm_info);
#endif
    
    char time_buf[20];
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", &tm_info);

    const char *level_str;
    switch (level) {
        case LOG_LEVEL_DEBUG: level_str = "DEBUG"; break;
        case LOG_LEVEL_INFO:  level_str = "INFO";  break;
        case LOG_LEVEL_WARN:  level_str = "WARN";  break;
        case LOG_LEVEL_ERROR: level_str = "ERROR"; break;
        default:              level_str = "UNKNOWN";
    }

    printf("[%s] [%s] ", time_buf, level_str);
    
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    
    printf("\n");
}