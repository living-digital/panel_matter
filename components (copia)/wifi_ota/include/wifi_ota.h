#if 1

#ifndef LVGL_INIT_H
#define LVGL_INIT_H

#ifdef __cplusplus
extern "C" {
#endif
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_err.h"
#include "driver/i2c.h"
#include "freertos/event_groups.h"
extern EventGroupHandle_t tcp_event_group; // wifi建立成功信号量
#define HASH_LEN 32 /* SHA-256 digest length */
#define CONFIG_EXAMPLE_GPIO_DIAGNOSTIC 4
#define BUFFSIZE 1024
static char ota_write_data[BUFFSIZE + 1] = { 0 };
#define CONFIG_EXAMPLE_OTA_RECV_TIMEOUT 5000

void wifi_ota_init();
void ota_start_task(void *pvParameter);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

#endif 
