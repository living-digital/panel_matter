// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// biblioteca principal de LVGL (LittlevGL)
#include "lvgl.h"
// configuraciones y la inicialización de parámetros específicos de la placa de hardware
#include "bsp_board.h"
// inicialización de la interfaz de LVGL
#include "lvgl_init.h"

void app_main(void)
{
    // inicialización del hardware y lvgl
    sys_int();
    lvgl_init();
    
    // Crear un label para mostrar "Hola Mundo"
    lv_obj_t *label = lv_label_create(lv_scr_act());  // Crea un label en la pantalla actual (pantalla principal)
    lv_label_set_text(label, "Hola Mundo");  // Establece el texto del label

    // Centra el hola mundo
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
