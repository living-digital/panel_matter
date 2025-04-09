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
#include "ui/subcard.h"

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

    // Crear cards dentro de la pantalla
    lv_obj_t *card1 = card_create(pantalla, 0, 0, 200, 100); // sup. izq. 
    lv_obj_t *card2 = card_create(pantalla, 0, 110, 200, 200); // centr. izq.
    lv_obj_t *card3 = card_create(pantalla, 0, 320, 200, 120); // inf. izq
    lv_obj_t *card4 = card_create(pantalla, 210, 0, 230, 440); // der. 

    // Crear subcards dentro de card4
    lv_obj_t *subcard1 = subcard_create(card4, 0, 160, 100, 100); // sup. izq.
    lv_obj_t *subcard2 = subcard_create(card4, 110, 160, 100, 100); // sup. der. 
    lv_obj_t *subcard3 = subcard_create(card4, 0, 270, 100, 100); // sup. izq.
    lv_obj_t *subcard4 = subcard_create(card4, 110, 270, 100, 100); // sup. der. 
    lv_obj_t *subcard5 = subcard_create(card4, 0, 380, 210, 40); // sup. der.


    // Actualización de la pantalla
    while (1) {
        lv_task_handler();  // Maneja los eventos de LVGL
        vTaskDelay(pdMS_TO_TICKS(10));  // Retardo de 10ms
    }
}
