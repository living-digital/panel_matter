#ifndef JSON_WORKER_H
#define JSON_WORKER_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Verifica si una cadena contiene un JSON válido.
 * 
 * @param json_str Cadena con el contenido JSON.
 * @return true si es un JSON válido, false en caso contrario.
 */
bool jsonIsValid(const char *json_str);

#ifdef __cplusplus
}
#endif

#endif // JSON_WORKER_H
