#include "base_screen.h"
#include "ui_styles.h"  

lv_obj_t * base_screen() {
    // Crear el objeto de la pantalla
    lv_obj_t * pantalla = lv_obj_create(lv_scr_act());

    // Configurar el estilo de fondo con el color de fondo del tema
    lv_obj_add_style(pantalla, &style_fondo, 0);

    // Asegurarse de que el objeto de la pantalla ocupe toda la pantalla
    lv_obj_set_size(pantalla, lv_disp_get_hor_res(NULL), lv_disp_get_ver_res(NULL));

    // padding
    lv_style_set_pad_all(&style_fondo, 5);

    return pantalla;
}
