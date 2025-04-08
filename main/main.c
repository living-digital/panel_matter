#include <stdio.h>
#include <string.h>

// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

// biblioteca principal de LVGL (LittlevGL)
#include "lvgl.h"
// configuraciones y la inicialización de parámetros específicos de la placa de hardware
#include "bsp_board.h"
// inicialización de la interfaz de LVGL
#include "lvgl_init.h"
// Pantallas y elementos para LVGL
#include "ui/ui_styles.h"
#include "ui/base_screen.h"
#include "ui/card.h"
// conexión wifi
#include "wifi_conect.h"

void app_main(void) {
    const char *TAG = "MAIN";

    // conectamos a red wifi
    esp_err_t err;
    do {
        err = wifi_conect("MOVISTAR_606E", "111D3321BD3B5C34AA26",
                          "192.168.18.250", "192.168.18.1", "255.255.255.0");
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "Error al intentar conectar (%d). Reintentando...", err);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    } while (err != ESP_OK);

    // inicializaciones
    sys_int();
    lvgl_init();
    ui_styles_init();

    // Pantalla de fondo
    lv_obj_t *pantalla = base_screen();
    lv_scr_load(pantalla);

    // Crear un card dentro de la pantalla
    lv_obj_t *card1 = card_create(pantalla);


    // Actualización de la pantalla
    while (1) {
        lv_task_handler();  // Maneja los eventos de LVGL
        vTaskDelay(pdMS_TO_TICKS(10));  // Retardo de 10ms
    }
}
