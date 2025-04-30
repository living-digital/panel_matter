#if 1

#ifndef HTTP_WIFI_H
#define HTTP_WIFI_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "esp_err.h"
#include "esp_log.h"
// #include "bsp_board.h"
#include "app_httpd.h"
#include "app_wifi.h"
#include "esp_camera.h"
void http_wifi_init(void);
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

#endif
