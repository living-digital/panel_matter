#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "esp_http_client.h"
#include "consultaApi.h"

#define TAG "consultaApi"
#define API_BUFFER_SIZE 1024

char *consultaApiGet(const char *url)
{
    ESP_LOGI(TAG, "Consulta a: %s", url);

    if (url == NULL) {
        ESP_LOGE(TAG, "URL no válida");
        return NULL;
    }

    // Configuración del cliente HTTP sin buffer_size, sin cert_pem, HTTP por puerto 80
    esp_http_client_config_t config = {
        .url = url,
        .method = HTTP_METHOD_GET,
        .timeout_ms = 5000
    };

    // Inicializa el cliente con la config. indicada arriba
    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "No se pudo inicializar el cliente HTTP");
        return NULL;
    }

    // Abre la conexión HTTP sin realizar lectura automática del cuerpo
    esp_err_t err = esp_http_client_open(client, 0);

    char *buffer = NULL;

    if (err == ESP_OK) {
        // Longitud del msg indicada por el servidor
        int content_length = esp_http_client_fetch_headers(client);
        ESP_LOGI(TAG, "Content-Length reportado por servidor: %d Bytes", content_length);

        // indicamos espacio para buffer en memoria
        buffer = malloc(API_BUFFER_SIZE);
        if (buffer == NULL) {
            ESP_LOGE(TAG, "No se pudo reservar memoria para la respuesta");
            esp_http_client_cleanup(client);
            return NULL;
        }

        // Obtiene la longitud real del msg
        int len = esp_http_client_read_response(client, buffer, API_BUFFER_SIZE - 1);
        ESP_LOGI(TAG, "Content-Length leídos: %d Bytes", len);

        if (len > 0) {
            buffer[len] = '\0';
            ESP_LOGI(TAG, "Respuesta API: %s , len=%d", buffer, len);
        } else if (len == 0) {
            ESP_LOGW(TAG, "La longitud del mensaje es 0 Bytes, eso es lamentable.");
            free(buffer);
            buffer = NULL;
        } else {
            ESP_LOGE(TAG, "Error al leer la respuesta: %d", len);
            free(buffer);
            buffer = NULL;
        }

    } else {
        ESP_LOGE(TAG, "Error al abrir conexión HTTP: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
    return buffer;
}
