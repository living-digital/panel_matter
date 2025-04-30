#ifndef _wav_play_h_
#define _wav_play_h_
#include "esp_vfs.h"
#include "esp_spiffs.h"
#include "driver/gpio.h"
#include "nvs_flash.h"
#include <stdint.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2s_std.h"
#include "driver/gpio.h"
#include "esp_check.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include "hal/i2s_hal.h"
#include "soc/i2s_periph.h"
void play_user_wav(char *file_name);
void i2s_driver_uninstall(void);
#endif
