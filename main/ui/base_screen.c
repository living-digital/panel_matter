#include "base_screen.h"

lv_obj_t *base_screen_create_color(lv_color_t color)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(scr, color, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);
    return scr;
}

lv_obj_t *base_screen_create_image(const lv_img_dsc_t *img)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(scr, img, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);
    return scr;
}
