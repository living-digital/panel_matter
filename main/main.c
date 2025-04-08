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
    lv_obj_t * pantalla = base_screen();
    lv_scr_load(pantalla);

    // Crear un label para mostrar IP
    char texto_ip[64];
    snprintf(texto_ip, sizeof(texto_ip), "IP: %s", wifi_conect_get_ip());

    lv_obj_t * label1 = lv_label_create(pantalla);
    lv_obj_add_style(label1, &style_texto_principal, 0);
    lv_label_set_text(label1, texto_ip);
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 10);

    // Crear un label para mostrar resolución
    lv_coord_t hor_res = lv_disp_get_hor_res(NULL);
    lv_coord_t ver_res = lv_disp_get_ver_res(NULL);

    char texto_res[64];
    snprintf(texto_res, sizeof(texto_res), "Resolución: %dx%d", hor_res, ver_res);

    lv_obj_t *label2 = lv_label_create(pantalla);
    lv_obj_add_style(label2, &style_texto_principal, 0);
    lv_label_set_text(label2, texto_res);
    lv_obj_align(label2, LV_ALIGN_CENTER, 0, 40);

    // Actualización de la pantalla
    while (1) {
        lv_task_handler();  // Maneja los eventos de LVGL
        vTaskDelay(pdMS_TO_TICKS(10));  // Retardo de 10ms
    }
}
