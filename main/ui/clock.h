#ifndef CLOCK_H
#define CLOCK_H

#include "lvgl.h"

#ifdef __cplusplus
extern "C" {
#endif

// Estructura que representa el reloj
typedef struct {
    lv_obj_t *label;   // Etiqueta para mostrar la hora
    void (*update)(void);  // Función para actualizar la hora
} Clock;

// Función para inicializar el reloj
void clock_init(Clock *clock, lv_obj_t *parent);

// Función para obtener la hora actual
void clock_update(Clock *clock);

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_H */
