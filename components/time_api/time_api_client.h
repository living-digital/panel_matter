#ifndef TIME_API_CLIENT_H
#define TIME_API_CLIENT_H

#include <stddef.h>

// Obtiene la hora actual desde la API.
// buffer: buffer donde se almacenará la respuesta (formato "HH:MM").
// bufsize: tamaño del buffer.
// Retorna 0 en éxito o -1 en caso de error.
int get_time(char *buffer, size_t bufsize);

#endif // TIME_API_CLIENT_H
