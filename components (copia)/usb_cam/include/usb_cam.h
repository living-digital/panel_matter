#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "usb_stream.h"
#include "esp_timer.h"
#include "usb_stream.h"//方案板usb摄像头的头文件

void usb_cam_start(void);
void usb_cam_init(void);
void camera_frame_cb(uvc_frame_t *frame, void *ptr);
