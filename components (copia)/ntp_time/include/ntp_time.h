#ifndef __NTP_TIME_H_
#define __NTP_TIME_H_

#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"

void ntp_time_init(void);
void sntp_task(void *param);
struct tm* get_time(void);
extern int app_year,app_mon,app_mday,app_hour,app_min,app_sec,app_week;

#endif