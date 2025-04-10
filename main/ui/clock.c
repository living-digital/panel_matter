#include "clock.h"
#include "lvgl.h"
#include <stdio.h>
#include <sys/time.h>



// Función para crear un reloj
// Esta función crea un nuevo reloj en un contenedor 'parent' dado
// El reloj se mostrará como un label con la hora actual que se actualizará cada segundo
Clock* clock_create(lv_obj_t *parent) {
    // Asignar memoria para el nuevo reloj
    Clock *clock = (Clock*)malloc(sizeof(Clock));
    
    if (clock == NULL) return NULL;  // Verificar si la asignación de memoria fue exitosa

    // nuevo label dentro de 'parent'
    clock->label = lv_label_create(parent);
    
    // Establecer la alineación del texto en el centro del label
    // lv_obj_align(clock->label, LV_ALIGN_TOP_LEFT);

    // Crear una tarea de LVGL que ejecutará la función 'clock_update' cada 1000ms (1 segundo)
    // La tarea actualizará la hora del reloj cada segundo
    clock->task = lv_task_create((lv_task_cb_t)clock_update, 1000, LV_TASK_PRIO_LOW, clock);

    return clock;  // Devolver el objeto reloj creado
}

// Función que actualiza la hora en el label del reloj
// Esta función se ejecuta cada segundo gracias a una tarea en LVGL.
void clock_update(Clock *clock) {
    struct tm timeinfo;        // Estructura para almacenar la hora actual
    char time_str[6];          // Buffer para almacenar la hora en formato "hh:mm"

    // Obtener la hora actual utilizando la función gettimeofday
    // gettimeofday llena la estructura 'timeinfo' con la hora actual del sistema
    if (gettimeofday(&timeinfo, NULL) == 0) {
        // Convertir la hora actual a una cadena con formato "hh:mm"
        strftime(time_str, sizeof(time_str), "%H:%M", &timeinfo);
        
        // Actualizar el texto del label con la nueva hora
        lv_label_set_text(clock->label, time_str);
    }
}

// Función para destruir un reloj y liberar los recursos asociados
// Esta función elimina la tarea de actualización y libera la memoria asignada al reloj
void clock_destroy(Clock *clock) {
    if (clock == NULL) return;  // Verificar si el reloj es válido

    // Eliminar la tarea de actualización del reloj
    lv_task_del(clock->task);

    // Liberar la memoria del objeto reloj
    free(clock);
}
