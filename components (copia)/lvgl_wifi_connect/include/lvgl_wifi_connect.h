#if 1

#ifndef LVGL_INIT_H
#define LVGL_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "lv_port_disp.h"
#include "lv_port_fs.h"
#include "lv_port_indev.h"
#include "lvgl.h"
#include <stdio.h>
#include <dirent.h>

#include "esp_spiffs.h"
#include "esp_err.h"
#include "esp_log.h"

#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

#include "bsp_board.h"
#include "st7701.h"
#include "gt911.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
    void lvgl_init_wifi(void);
    void wifi_scan_init(void);
    void lv_port_disp_init1(void);
    esp_err_t lv_port_tick_init1(void);
    void lv_port_sem_take1(void);
    void lv_port_sem_give1(void);
    void lv_port_fs_init(void);
    void lv_port_indev_init(void);
#define WIFI_CONNECTED_BIT BIT0   
#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif

#endif
