#pragma once

typedef enum occam_log_level_tag
{
   OCCAM_LOG_LEVEL_DEBUG,
   OCCAM_LOG_LEVEL_INFO,
   OCCAM_LOG_LEVEL_WARN,
   OCCAM_LOG_LEVEL_ERROR,
} occam_log_level_t;

typedef
   void (*occam_log_handler)(void * userdata,
             const occam_log_level_t level,
             const char * const area,
             const char * const msg);

typedef struct occam_logger_tag
{
   occam_log_handler handler;
   void *userdata;
} occam_logger_t;

//TODO: add some cases
#define OCCAM_CURRENT_FUNCTION __FUNC__

#define occam_log(LOG, LVL, MSG) (LOG)->handler((LOG)->userdata, LVL, OCCAM_CURRENT_FUNCTION, MSG)
#define occam_log_d(LOG, MSG) occam_log(LOG, OCCAM_LOG_LEVEL_DEBUG, MSG)
#define occam_log_i(LOG, MSG) occam_log(LOG, OCCAM_LOG_LEVEL_INFO,  MSG)
#define occam_log_w(LOG, MSG) occam_log(LOG, OCCAM_LOG_LEVEL_WARN,  MSG)
#define occam_log_e(LOG, MSG) occam_log(LOG, OCCAM_LOG_LEVEL_ERROR, MSG)

