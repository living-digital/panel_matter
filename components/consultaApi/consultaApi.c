#include "consultaApi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_http_client.h"
#include "esp_log.h"

static const char *TAG = "consultaApi";

/* Estructura para acumular la respuesta */
typedef struct {
    char *buffer;
    size_t length;
} consultaApiMemoryBlock;

/* Callback de escritura para acumular la respuesta HTTP */
static size_t http_event_handler(void *handler_args, char *data, size_t len)
{
    consultaApiMemoryBlock *mem = (consultaApiMemoryBlock *)handler_args;
    char *ptr = realloc(mem->buffer, mem->length + len + 1);
    if (ptr == NULL) {
        ESP_LOGE(TAG, "No hay suficiente memoria (realloc retornó NULL)");
        return 0; // Retorna 0 para indicar error; la petición se abortará
    }
    mem->buffer = ptr;
    memcpy(&(mem->buffer[mem->length]), data, len);
    mem->length += len;
    mem->buffer[mem->length] = '\0';  // Asegurar la terminación nula
    return len;
}

char *consultaApiGet(const char *url)
{
    // Inicializar estructura para almacenar la respuesta
    consultaApiMemoryBlock mem;
    mem.length = 0;
    mem.buffer = malloc(1);  // Inicialización con 1 byte
    if (mem.buffer == NULL) {
        ESP_LOGE(TAG, "Error al asignar memoria inicial");
        return NULL;
    }
    mem.buffer[0] = '\0';

    // Configuración del cliente HTTP
    esp_http_client_config_t config = {
        .url = url,
        .event_handler = http_event_handler,
        .user_data = &mem, // Puntero a nuestra estructura para acumular datos
        // Opcional: se pueden configurar tiempos de espera, etc.
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    if (client == NULL) {
        ESP_LOGE(TAG, "Error al inicializar el cliente HTTP");
        free(mem.buffer);
        return NULL;
    }
    
    esp_err_t err = esp_http_client_perform(client);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Error en la petición HTTP: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        free(mem.buffer);
        return NULL;
    }

    esp_http_client_cleanup(client);
    return mem.buffer; // Se retorna la respuesta; el usuario debe hacer free() de la cadena
}
