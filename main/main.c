// FreeRTOS
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// Conexión WiFi
#include "wifi_conect.h"
// Consultas a API (consultaApiGet se define en consultaApi.c, con su header consultaApi.h)
#include "consultaApi.h"
// biblioteca principal de LVGL (LittlevGL)
#include "lvgl.h"
// configuraciones y la inicialización de parámetros específicos de la placa de hardware
#include "bsp_board.h"
// inicialización de la interfaz de LVGL
#include "lvgl_init.h"
// Elementos de la interfaz (UI)
// #include "ui/ui_styles.h"
// #include "ui/base_screen.h"
// #include "ui/card.h"
// #include "ui/subcard.h"
// #include "esp_timer.h"

// /*
// ESP_LOGE(TAG, "Este es un mensaje de ERROR");
// ESP_LOGW(TAG, "Este es un mensaje de ADVERTENCIA");
// ESP_LOGI(TAG, "Este es un mensaje de INFORMACIÓN");
// ESP_LOGD(TAG, "Este es un mensaje de DEPURACIÓN");
// ESP_LOGV(TAG, "Este es un mensaje VERBOSE");
// */

void app_main(void)
{
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


    // inicialización del hardware y lvgl
    sys_int();
    lvgl_init();
    
    // Crear un label para mostrar "Hola Mundo"
    lv_obj_t *label = lv_label_create(lv_scr_act());  // Crea un label en la pantalla actual (pantalla principal)
    lv_label_set_text(label, "Hola Mundo");  // Establece el texto del label

    // Centra el hola mundo
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}
