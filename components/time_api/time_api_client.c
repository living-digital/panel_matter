#include "time_api_client.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_client.h"

static const char *TAG = "time_api_client";

// Event handler (opcional) para registrar eventos durante la petición.
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI(TAG, "Datos recibidos: len=%d", evt->data_len);
            break;
        // Otros eventos se pueden gestionar si es necesario
        default:
            break;
    }
    return ESP_OK;
}

int get_time(char *buffer, size_t bufsize)
{
    // Configuración del cliente HTTP
    esp_http_client_config_t config = {
        .url = "http://devel.livingdigitalsolutions.com/admin/time",
        .event_handler = _http_event_handler,
        // Opcional: se pueden configurar tiempos de espera o validaciones SSL si se requiere.
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (!client) {
        ESP_LOGE(TAG, "Error al inicializar la conexión HTTP");
        return -1;
    }

    // Realiza la petición HTTP GET
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        int status_code = esp_http_client_get_status_code(client);
        int content_length = esp_http_client_get_content_length(client);
        ESP_LOGI(TAG, "Status HTTP: %d, longitud del contenido: %d", status_code, content_length);

        // Se lee la respuesta; suponemos que el string es corto (formato "HH:MM")
        int read_len = esp_http_client_read(client, buffer, bufsize - 1);
        if (read_len >= 0) {
            buffer[read_len] = '\0'; // Aseguramos el terminador nulo
        } else {
            ESP_LOGE(TAG, "Error al leer los datos de la respuesta");
            esp_http_client_cleanup(client);
            return -1;
        }
    } else {
        ESP_LOGE(TAG, "Falla en la petición HTTP: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        return -1;
    }

    esp_http_client_cleanup(client);
    return 0;
}
