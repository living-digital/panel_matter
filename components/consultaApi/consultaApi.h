#ifndef CONSULTA_API_H
#define CONSULTA_API_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Realiza una petición HTTP GET a la URL dada.
 * 
 * @param url Dirección de la API a consultar.
 * @return char* Puntero a una cadena con la respuesta. 
 *         Si ocurre un error, se devuelve NULL.
 *         La cadena retornada se aloja dinámicamente y el usuario debe liberarla con free().
 */
char *consultaApiGet(const char *url);

#ifdef __cplusplus
}
#endif

#endif // CONSULTA_API_H
