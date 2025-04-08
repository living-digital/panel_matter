#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BASE_SCREEN_BG_COLOR,
    BASE_SCREEN_BG_IMAGE
} base_screen_bg_mode_t;

lv_obj_t *base_screen_create_color(lv_color_t color);
lv_obj_t *base_screen_create_image(const lv_img_dsc_t *img);

#ifdef __cplusplus
}
#endif
