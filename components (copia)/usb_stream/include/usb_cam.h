#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_err.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "usb_stream.h"//方案板usb摄像头的头文件
void usb_cam_start(void);