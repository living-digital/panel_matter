#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BASE_SCREEN_BG_COLOR,
    BASE_SCREEN_BG_IMAGE
} base_screen_bg_mode_t;

lv_obj_t *base_screen();

#ifdef __cplusplus
}
#endif
