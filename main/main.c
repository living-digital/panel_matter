// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// biblioteca principal de LVGL (LittlevGL)
#include "lvgl.h"
// configuraciones y la inicialización de parámetros específicos de la placa de hardware
#include "bsp_board.h"
// inicialización de la interfaz de LVGL
#include "lvgl_init.h"
// conexion wifi
#include "wifi_conect.h"


void app_main(void){

    const char * TAG = "MAIN";

    // conectamos a red wifi
    esp_err_t err;
    do {
        err = wifi_conect("MOVISTAR_606E", "111D3321BD3B5C34AA26",
                          "192.168.18.250", "192.168.18.1", "255.255.255.0");
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "Error al intentar conectar (%d). Reintentando...", err);
            vTaskDelay(pdMS_TO_TICKS(1000)); // Espera antes del siguiente intento
        }
    } while (err != ESP_OK);

    // inicialización del hardware y lvgl
    sys_int();
    lvgl_init();
    
    // Crear un label para mostrar "Hola Mundo"
    lv_obj_t *label = lv_label_create(lv_scr_act());  // Crea un label en la pantalla actual (pantalla principal)
    lv_label_set_text(label, wifi_conect_get_ip());  // Establece el texto del label

}
