#pragma once

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Función para crear un card con parámetros personalizados (posición y tamaño)
lv_obj_t *card_create(lv_obj_t *parent, int x, int y, int ancho, int alto);

#ifdef __cplusplus
}
#endif
