#include "json_worker.h"
#include "cJSON.h"

// Verifica que el json del argumento es valido
bool jsonIsValid(const char *json_str)
{
    if (json_str == NULL) return false;

    cJSON *json = cJSON_Parse(json_str);
    if (json == NULL) {
        return false;
    }

    cJSON_Delete(json);
    return true;
}
