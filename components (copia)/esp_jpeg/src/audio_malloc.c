/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdlib.h>
#include "sdkconfig.h"
#include "esp_heap_caps.h"
#include "esp_log.h"
#include "usb_cam.h"
#include "driver/gpio.h"

#include "iot_button.h"
#include "usb_stream.h"
#include <stdlib.h>
#include "esp_jpeg_dec.h"
#include "esp_event.h"
#include "esp_spi_flash.h"
#include "nvs_flash.h"
#include <stdlib.h>
#include "esp_log.h"
#include "esp_system.h"
static const char *TAG = "lcd_cam";

static EventGroupHandle_t s_evt_handle;
extern void usb_cam_init(void);

extern esp_lcd_panel_handle_t my_lcd_panel;
extern uint8_t *lcd_frame_buf;
static uint8_t draw_buf_index = 0;
SemaphoreHandle_t xGuiSemaphore;


#define DEMO_UVC_XFER_BUFFER_SIZE (88 * 1024) // Double buffer
#define DEMO_KEY_RESOLUTION "resolution"      // The key of the resolution stored in nvs
#define DEMO_SWITCH_BUTTON_IO 0               // The button to switch resolution
#define BIT0_FRAME_START (0x01 << 0)

typedef struct
{
    uint16_t width;
    uint16_t height;
} camera_frame_size_t;

typedef struct
{
    camera_frame_size_t camera_frame_size;
    uvc_frame_size_t *camera_frame_list;
    size_t camera_frame_list_num;
    size_t camera_currect_frame_index;
} camera_resolution_info_t;

static camera_resolution_info_t camera_resolution_info = {0};
static uint8_t *jpg_frame_buf = NULL;
 uint8_t *xfer_buffer_a = NULL;
 uint8_t *xfer_buffer_b = NULL;
 uint8_t *frame_buffer = NULL;
static uint16_t current_width = 0;
static uint16_t current_height = 0;


static void adaptive_jpg_frame_buffer(size_t length)
{
    if (jpg_frame_buf != NULL)
    {
        free(jpg_frame_buf);
    }

    jpg_frame_buf = (uint8_t *)heap_caps_aligned_alloc(16, length, MALLOC_CAP_SPIRAM);
    assert(jpg_frame_buf != NULL);
}

static void _get_value_from_nvs(char *key, void *value, size_t *size)
{
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("memory", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        // ESP_LOGE(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    }
    else
    {
        err = nvs_get_blob(my_handle, key, value, size);
        switch (err)
        {
        case ESP_OK:
            break;
        case ESP_ERR_NVS_NOT_FOUND:
            // ESP_LOGI(TAG, "%s is not initialized yet!", key);
            break;
        default:
            // ESP_LOGE(TAG, "Error (%s) reading!\n", esp_err_to_name(err));
        }

        nvs_close(my_handle);
    }
}

static esp_err_t _set_value_to_nvs(char *key, void *value, size_t size)
{
    nvs_handle_t my_handle;
    esp_err_t err = nvs_open("memory", NVS_READWRITE, &my_handle);
    if (err != ESP_OK)
    {
        // ESP_LOGE(TAG, "Error (%s) opening NVS handle!\n", esp_err_to_name(err));
        return ESP_FAIL;
    }
    else
    {
        err = nvs_set_blob(my_handle, key, value, size);
        if (err != ESP_OK)
        {
            // ESP_LOGE(TAG, "NVS set failed %s", esp_err_to_name(err));
        }

        err = nvs_commit(my_handle);
        if (err != ESP_OK)
        {
            // ESP_LOGE(TAG, "NVS commit failed");
        }

        nvs_close(my_handle);
    }

    return err;
}

static esp_err_t _usb_stream_init(void)
{
    uvc_config_t uvc_config = {
        .frame_interval = FRAME_INTERVAL_FPS_15,
        .xfer_buffer_size = DEMO_UVC_XFER_BUFFER_SIZE,
        .xfer_buffer_a = xfer_buffer_a,
        .xfer_buffer_b = xfer_buffer_b,
        .frame_buffer_size = DEMO_UVC_XFER_BUFFER_SIZE,
        .frame_buffer = frame_buffer,
        .frame_cb = &camera_frame_cb,
        .frame_cb_arg = NULL,
        .frame_width = FRAME_RESOLUTION_ANY,
        .frame_height = FRAME_RESOLUTION_ANY,
        .flags = FLAG_UVC_SUSPEND_AFTER_START,
    };

    esp_err_t ret = uvc_streaming_config(&uvc_config);
    if (ret != ESP_OK)
    {
        // ESP_LOGE(TAG, "uvc streaming config failed");
    }
    return ret;
}

static size_t _find_current_resolution(camera_frame_size_t *camera_frame_size)
{
    if (camera_resolution_info.camera_frame_list == NULL)
    {
        return -1;
    }

    size_t i = 0;
    while (i < camera_resolution_info.camera_frame_list_num)
    {
        if (camera_frame_size->width >= camera_resolution_info.camera_frame_list[i].width && camera_frame_size->height >= camera_resolution_info.camera_frame_list[i].height)
        {
            /* Find next resolution
               If current resolution is the min resolution, switch to the max resolution*/
            camera_frame_size->width = camera_resolution_info.camera_frame_list[i].width;
            camera_frame_size->height = camera_resolution_info.camera_frame_list[i].height;
            break;
        }
        else if (i == camera_resolution_info.camera_frame_list_num - 1)
        {
            camera_frame_size->width = camera_resolution_info.camera_frame_list[i].width;
            camera_frame_size->height = camera_resolution_info.camera_frame_list[i].height;
            break;
        }
        i++;
    }

    return i;
}

static void switch_button_press_down_cb(void *arg, void *data)
{

    if (camera_resolution_info.camera_frame_list == NULL || xEventGroupWaitBits(s_evt_handle, BIT0_FRAME_START, false, false, pdMS_TO_TICKS(10)) != pdTRUE)
    {
        return;
    }
    // ESP_LOGI(TAG, "old resolution is %d*%d", camera_resolution_info.camera_frame_size.width, camera_resolution_info.camera_frame_size.height);
    if (++camera_resolution_info.camera_currect_frame_index >= camera_resolution_info.camera_frame_list_num)
    {
        camera_resolution_info.camera_currect_frame_index = 0;
    }
    camera_resolution_info.camera_frame_size.width = camera_resolution_info.camera_frame_list[camera_resolution_info.camera_currect_frame_index].width;
    camera_resolution_info.camera_frame_size.height = camera_resolution_info.camera_frame_list[camera_resolution_info.camera_currect_frame_index].height;
    // ESP_LOGI(TAG, "currect resolution is %d*%d", camera_resolution_info.camera_frame_size.width, camera_resolution_info.camera_frame_size.height);

    /* Save the new camera resolution to nsv */
    usb_streaming_control(STREAM_UVC, CTRL_SUSPEND, NULL);
    ESP_ERROR_CHECK(uvc_frame_size_reset(camera_resolution_info.camera_frame_size.width,
                                         camera_resolution_info.camera_frame_size.height,
                                         FPS2INTERVAL(30)));
    ESP_ERROR_CHECK(_set_value_to_nvs(DEMO_KEY_RESOLUTION, &camera_resolution_info.camera_frame_size, sizeof(camera_frame_size_t)));
    usb_streaming_control(STREAM_UVC, CTRL_RESUME, NULL);
}

static esp_err_t _switch_button_init(void)
{
    button_config_t button_config = {
        .type = BUTTON_TYPE_GPIO,
        .gpio_button_config = {
            .gpio_num = DEMO_SWITCH_BUTTON_IO,
            .active_level = 0,
        },
    };

    button_handle_t button_handle = iot_button_create(&button_config);
    assert(button_handle != NULL);
    esp_err_t ret = iot_button_register_cb(button_handle, BUTTON_PRESS_DOWN, switch_button_press_down_cb, NULL);
    if (ret != ESP_OK)
    {
        // ESP_LOGE(TAG, "button register callback fail");
    }
    return ret;
}

static void _stream_state_changed_cb(usb_stream_state_t event, void *arg)
{
    switch (event)
    {
    case STREAM_CONNECTED:
    {
        /* Get camera resolution in nvs*/
        size_t size = sizeof(camera_frame_size_t);
        _get_value_from_nvs(DEMO_KEY_RESOLUTION, &camera_resolution_info.camera_frame_size, &size);
        size_t frame_index = 0;
        uvc_frame_size_list_get(NULL, &camera_resolution_info.camera_frame_list_num, NULL);
        if (camera_resolution_info.camera_frame_list_num)
        {
            // ESP_LOGI(TAG, "UVC: get frame list size = %u, current = %u", camera_resolution_info.camera_frame_list_num, frame_index);
            uvc_frame_size_t *_frame_list = (uvc_frame_size_t *)malloc(camera_resolution_info.camera_frame_list_num * sizeof(uvc_frame_size_t));

            camera_resolution_info.camera_frame_list = (uvc_frame_size_t *)realloc(camera_resolution_info.camera_frame_list, camera_resolution_info.camera_frame_list_num * sizeof(uvc_frame_size_t));
            if (NULL == camera_resolution_info.camera_frame_list)
            {
                // ESP_LOGE(TAG, "camera_resolution_info.camera_frame_list");
            }
            uvc_frame_size_list_get(_frame_list, NULL, NULL);
            for (size_t i = 0; i < camera_resolution_info.camera_frame_list_num; i++)
            {
                if (_frame_list[i].width <= 480 && _frame_list[i].height <= 480)
                {
                    camera_resolution_info.camera_frame_list[frame_index++] = _frame_list[i];
                    // ESP_LOGI(TAG, "\tpick frame[%u] = %ux%u", i, _frame_list[i].width, _frame_list[i].height);
                }
                else
                {
                    // ESP_LOGI(TAG, "\tdrop frame[%u] = %ux%u", i, _frame_list[i].width, _frame_list[i].height);
                }
            }
            camera_resolution_info.camera_frame_list_num = frame_index;
            if (camera_resolution_info.camera_frame_size.width != 0 && camera_resolution_info.camera_frame_size.height != 0)
            {
                camera_resolution_info.camera_currect_frame_index = _find_current_resolution(&camera_resolution_info.camera_frame_size);
            }
            else
            {
                camera_resolution_info.camera_currect_frame_index = 0;
            }

            if (-1 == camera_resolution_info.camera_currect_frame_index)
            {
                // ESP_LOGE(TAG, "fine current resolution fail");
                break;
            }
            ESP_ERROR_CHECK(uvc_frame_size_reset(camera_resolution_info.camera_frame_list[camera_resolution_info.camera_currect_frame_index].width,
                                                 camera_resolution_info.camera_frame_list[camera_resolution_info.camera_currect_frame_index].height, FPS2INTERVAL(30)));
            camera_frame_size_t camera_frame_size = {
                .width = camera_resolution_info.camera_frame_list[camera_resolution_info.camera_currect_frame_index].width,
                .height = camera_resolution_info.camera_frame_list[camera_resolution_info.camera_currect_frame_index].height,
            };
            ESP_ERROR_CHECK(_set_value_to_nvs(DEMO_KEY_RESOLUTION, &camera_frame_size, sizeof(camera_frame_size_t)));

            if (_frame_list != NULL)
            {
                free(_frame_list);
            }
            /* Wait USB Camera connected */
            usb_streaming_control(STREAM_UVC, CTRL_RESUME, NULL);
            xEventGroupSetBits(s_evt_handle, BIT0_FRAME_START);
        }
        else
        {
            ESP_LOGW(TAG, "UVC: get frame list size = %u", camera_resolution_info.camera_frame_list_num);
        }
        // ESP_LOGI(TAG, "Device connected");
        break;
    }
    case STREAM_DISCONNECTED:
        xEventGroupClearBits(s_evt_handle, BIT0_FRAME_START);
        // ESP_LOGI(TAG, "Device disconnected");
        break;
    default:
        // ESP_LOGE(TAG, "Unknown event");
        break;
    }
}

void usbcam_to_lcd(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        /* NVS partition was truncated and needs to be erased */
        ESP_ERROR_CHECK(nvs_flash_erase());
        /* Retry nvs_flash_init */
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    /* Create event group */
    s_evt_handle = xEventGroupCreate();
    if (s_evt_handle == NULL)
    {
        // ESP_LOGE(TAG, "line-%u event group create failed", __LINE__);
        assert(0);
    }
    usb_cam_init();
    _switch_button_init();

    ESP_ERROR_CHECK(_usb_stream_init());

    ESP_ERROR_CHECK(usb_streaming_state_register(&_stream_state_changed_cb, NULL));
    usb_cam_start();
}

// #define audio_malloc  malloc
// #define audio_free    free
// #define audio_strdup  strdup
// #define audio_calloc  calloc
// #define audio_realloc realloc

void *audio_calloc_inner(size_t n, size_t size)
{
    void *data = NULL;
#if CONFIG_SPIRAM_BOOT_INIT
    data = heap_caps_calloc_prefer(n, size, 2, MALLOC_CAP_DEFAULT | MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT, MALLOC_CAP_DEFAULT | MALLOC_CAP_SPIRAM);
#else
    data = heap_caps_calloc(n, size, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#endif

#ifdef ENABLE_AUDIO_MEM_TRACE
    ESP_LOGI("AUIDO_MEM", "calloc_inner:%p, size:%d, called:0x%08x", data, size, (intptr_t)__builtin_return_address(0) - 2);
#endif
    return data;
}

void *audio_calloc(size_t n, size_t size)
{
    return calloc(n, size);
}

// void* realloc(void* ptr, size_t size)
// {
//     return heap_caps_realloc_default(ptr, size);
// }

void audio_free(void *ptr)
{
    free(ptr);
}
