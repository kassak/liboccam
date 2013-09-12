#pragma once
#include <stdarg.h>

typedef enum occam_log_level_tag
{
   OCCAM_LOG_LEVEL_NONE = -1,
   OCCAM_LOG_LEVEL_FIRST = 0,

   OCCAM_LOG_LEVEL_TRACE = OCCAM_LOG_LEVEL_FIRST,
   OCCAM_LOG_LEVEL_DEBUG,
   OCCAM_LOG_LEVEL_INFO,
   OCCAM_LOG_LEVEL_WARN,
   OCCAM_LOG_LEVEL_ERROR,

   OCCAM_LOG_LEVEL_LAST = OCCAM_LOG_LEVEL_ERROR,
   OCCAM_LOG_LEVEL_COUNT
} occam_log_level_t;

typedef
   void (*occam_log_handler_t)(void * userdata,
             const occam_log_level_t level,
             const char * area,
             const char * fmt,
             va_list args);

typedef struct occam_logger_tag
{
   occam_log_handler_t handler;
   void *userdata;
} occam_logger_t;

static const char * const _occam_log_level_name[OCCAM_LOG_LEVEL_COUNT] = {
   "TRACE",
   "DEBUG",
   "INFO",
   "WARN",
   "ERROR"
};

//TODO: add some cases
#define OCCAM_CURRENT_FUNCTION __func__

static inline void occam_logv(const occam_logger_t * log, occam_log_level_t lvl,
   const char * area, const char * fmt, va_list args)
{
   if(log)
      log->handler(log->userdata, lvl, area, fmt, args);
}
static inline void occam_log(const occam_logger_t * log, occam_log_level_t lvl,
   const char * area, const char * fmt, ...)
{
   va_list args;
   va_start(args, fmt);
   occam_logv(log, lvl, area, fmt, args);
   va_end(args);
}

#define occam_current_log(LOG, LVL, FMT, ...) occam_log(LOG, LVL, OCCAM_CURRENT_FUNCTION, FMT, __VA_ARGS__)
#define occam_current_logs(LOG, LVL, FMT, ...) occam_log(LOG, LVL, OCCAM_CURRENT_FUNCTION, FMT)
#define occam_log_t(LOG, FMT, ...) occam_current_log(LOG, OCCAM_LOG_LEVEL_TRACE, FMT, __VA_ARGS__)
#define occam_log_d(LOG, FMT, ...) occam_current_log(LOG, OCCAM_LOG_LEVEL_DEBUG, FMT, __VA_ARGS__)
#define occam_log_i(LOG, FMT, ...) occam_current_log(LOG, OCCAM_LOG_LEVEL_INFO,  FMT, __VA_ARGS__)
#define occam_log_w(LOG, FMT, ...) occam_current_log(LOG, OCCAM_LOG_LEVEL_WARN,  FMT, __VA_ARGS__)
#define occam_log_e(LOG, FMT, ...) occam_current_log(LOG, OCCAM_LOG_LEVEL_ERROR, FMT, __VA_ARGS__)
#define occam_logs_t(LOG, FMT) occam_current_logs(LOG, OCCAM_LOG_LEVEL_TRACE, FMT)
#define occam_logs_d(LOG, FMT) occam_current_logs(LOG, OCCAM_LOG_LEVEL_DEBUG, FMT)
#define occam_logs_i(LOG, FMT) occam_current_logs(LOG, OCCAM_LOG_LEVEL_INFO,  FMT)
#define occam_logs_w(LOG, FMT) occam_current_logs(LOG, OCCAM_LOG_LEVEL_WARN,  FMT)
#define occam_logs_e(LOG, FMT) occam_current_logs(LOG, OCCAM_LOG_LEVEL_ERROR, FMT)

#define occam_log_level_name(LVL) (_occam_log_level_name[LVL])
