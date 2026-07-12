#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} LogLevel;

void logger_init(void);
void logger_set_level(LogLevel level);
void logger_cleanup(void);

void logger_log(LogLevel level, const char *format, ...);

#define LOG_DEBUG(...) logger_log(LOG_LEVEL_DEBUG, __VA_ARGS__)
#define LOG_INFO(...)  logger_log(LOG_LEVEL_INFO, __VA_ARGS__)
#define LOG_WARN(...)  logger_log(LOG_LEVEL_WARN, __VA_ARGS__)
#define LOG_ERROR(...) logger_log(LOG_LEVEL_ERROR, __VA_ARGS__)

#endif