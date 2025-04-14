#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Configuraciones de hardware
#include "bsp_board.h"

// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_err.h"

// LVGL: biblioteca principal y su inicialización
#include "lvgl.h"
#include "lvgl_init.h"

// Elementos de la interfaz (UI)
#include "ui/ui_styles.h"
#include "ui/base_screen.h"
#include "ui/card.h"
#include "ui/subcard.h"
#include "esp_timer.h"

// Conexión WiFi
#include "wifi_conect.h"

// Consultas a API (consultaApiGet se define en consultaApi.c, con su header consultaApi.h)
#include "consultaApi.h"

/*
ESP_LOGE(TAG, "Este es un mensaje de ERROR");
ESP_LOGW(TAG, "Este es un mensaje de ADVERTENCIA");
ESP_LOGI(TAG, "Este es un mensaje de INFORMACIÓN");
ESP_LOGD(TAG, "Este es un mensaje de DEPURACIÓN");
ESP_LOGV(TAG, "Este es un mensaje VERBOSE");
*/

void app_main(void) {
    const char *TAG = "MAIN";

    // 1. Conectar a WiFi
    esp_err_t err;
    do {
        err = wifi_conect("MOVISTAR_606E", 
                          "111D3321BD3B5C34AA26",
                          "192.168.18.250", 
                          "192.168.18.1", 
                          "255.255.255.0", 
                          "8.8.8.8");
        if (err != ESP_OK) {
            ESP_LOGW(TAG, "Error al intentar conectar (%d). Reintentando...", err);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    } while (err != ESP_OK);

    ESP_LOGW(TAG, "Pausa para estabilidad en conexion wifi.");
    vTaskDelay(pdMS_TO_TICKS(5000));

    // Verificar conexión WiFi e Internet
    if (wifi_conect_is_connected()){
        ESP_LOGW(TAG, "Conexion wifi OK.");
    } else {
        ESP_LOGW(TAG, "Error al conectar a wifi.");
    }

    if (internet_connected_ip()){
        ESP_LOGW(TAG, "Acceso a internet OK (IP).");
    } else {
        ESP_LOGW(TAG, "Error en acceso a internet (IP).");
    }

    if (internet_connected_dns()){
        ESP_LOGW(TAG, "Acceso a internet OK (DNS).");
    } else {
        ESP_LOGW(TAG, "Error en acceso a internet (DNS).");
    }

    // 2. Realizar consulta a la API
    const char *url = "http://devel.livingdigitalsolutions.com/admin/datetime";
    char *response = consultaApiGet(url);
    if (response) {
        ESP_LOGI(TAG, "RESPUESTA API: %s", response);
        // Aquí podrías parsear el JSON para extraer el campo "datetime"
        free(response);  // Liberar la memoria asignada en consultaApiGet
    } else {
        ESP_LOGE(TAG, "Error al consultar la API");
    }

    // 3. Inicializar LVGL y la UI
    sys_int();        // Inicialización del sistema
    lvgl_init();      // Inicializa LVGL
    ui_styles_init(); // Inicializa estilos de UI

    // Configurar la pantalla de fondo
    lv_obj_t *pantalla = base_screen();
    lv_scr_load(pantalla);

    // Crear cards
    lv_obj_t *card1 = card_create(pantalla, 0, 0, 200, 100);   // Superior izquierda
    lv_obj_t *card2 = card_create(pantalla, 0, 110, 200, 200);  // Centro izquierda
    lv_obj_t *card3 = card_create(pantalla, 0, 320, 200, 120);  // Inferior izquierda
    lv_obj_t *card4 = card_create(pantalla, 210, 0, 230, 440);  // Derecha

    // Crear subcards en card4
    lv_obj_t *subcard1 = subcard_create(card4, 0, 160, 100, 100);
    lv_obj_t *subcard2 = subcard_create(card4, 110, 160, 100, 100);
    lv_obj_t *subcard3 = subcard_create(card4, 0, 270, 100, 100);
    lv_obj_t *subcard4 = subcard_create(card4, 110, 270, 100, 100);
    lv_obj_t *subcard5 = subcard_create(card4, 0, 380, 210, 40);

    // Crear labels en card4
    lv_obj_t *labelClock = lv_label_create(card4);
    lv_obj_add_style(labelClock, &style_titulo1, 0);
    lv_obj_align(labelClock, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_label_set_text(labelClock, "12:00");

    lv_obj_t *labelDate = lv_label_create(card4);
    lv_obj_add_style(labelDate, &style_texto1, 0);
    lv_obj_align(labelDate, LV_ALIGN_TOP_LEFT, 0, 60);
    lv_label_set_text(labelDate, "labelDate");

    // Crear label para la conexión a Internet, en subcard5
    lv_obj_t *labelNet = lv_label_create(subcard5);
    lv_obj_add_style(labelNet, &style_texto1, 0);
    lv_obj_align(labelNet, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_label_set_text(labelNet, "labelNet");

    // 4. Iniciar un bucle para refrescar la UI
    while (1) {
        lv_task_handler();  // Procesa y refresca la interfaz de LVGL
        vTaskDelay(pdMS_TO_TICKS(10));  // Pequeño retardo para no saturar la CPU
    }
}
