#pragma once

typedef enum occam_log_level_tag
{
   OCCAM_LOG_LEVEL_DEBUG,
   OCCAM_LOG_LEVEL_INFO,
   OCCAM_LOG_LEVEL_WARN,
   OCCAM_LOG_LEVEL_ERROR,

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
   "DEBUG",
   "INFO",
   "WARN",
   "ERROR"
};

//TODO: add some cases
#define OCCAM_CURRENT_FUNCTION __func__

void occam_logv(occam_logger_t * log, occam_log_level_t lvl,
   const char * area, const char * fmt, va_list args)
{
   if(log)
      log->handler(log->userdata, lvl, area, fmt, args);
}
void occam_log(occam_logger_t * log, occam_log_level_t lvl,
   const char * area, const char * fmt, ...)
{
   va_list ap;
   va_start(args, fmt);
   occam_logv(log, lvl, area, fmt, args);
   va_end(args);
}

#define occam_current_log(LOG, LVL, FMT, ...) occam_log(LOG, LVL, OCCAM_CURRENT_FUNCTION, FMT, __VA_ARGS__)
#define occam_log_d(LOG, FMT, ...) occam_log(LOG, OCCAM_LOG_LEVEL_DEBUG, FMT, __VA_ARGS__)
#define occam_log_i(LOG, FMT, ...) occam_log(LOG, OCCAM_LOG_LEVEL_INFO,  FMT, __VA_ARGS__)
#define occam_log_w(LOG, FMT, ...) occam_log(LOG, OCCAM_LOG_LEVEL_WARN,  FMT, __VA_ARGS__)
#define occam_log_e(LOG, FMT, ...) occam_log(LOG, OCCAM_LOG_LEVEL_ERROR, FMT, __VA_ARGS__)

#define occam_log_level_name(LVL) (_occam_log_level_name[LVL])