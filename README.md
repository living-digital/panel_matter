# panel_matter
Este proyecto permite conectar un ESP32 con display de 4" a una red WiFi, tambien trabajaremos con esp-matter (fork de Matter especifico para esta plataforma) para la conectividad de dispositivos IOT, todo ello con una interfaz generada con lvgl


## Requisitos previos:

ESP-IDF instalado (v5.0 o superior recomendado)

Cable USB para flashear el ESP32

Red WiFi de 2.4 GHz (el ESP32 no es compatible con redes de 5 GHz)


## Versionado: vX.Y.Z🔖
Cada número tiene un propósito específico:

Major (X) – Cambios incompatibles: Se incrementa cuando haces cambios que rompen compatibilidad con versiones anteriores.

Minor (Y) – Nuevas funcionalidades compatibles: Se incrementa cuando agregas nuevas funciones o mejoras, pero sin romper lo que ya existía.

Patch (Z) – Corrección de errores o mejoras menores:Se incrementa cuando haces correcciones, mejoras internas o ajustes, pero sin agregar ni quitar funcionalidades públicas.

```
0.1.0 - Primera version
```

## Notas:

Asegúrate de que la red wifi sea visible y opere en la banda de 2.4 GHz

Si estás usando IP fija, evita conflictos con el rango DHCP del router

El sistema intentará reconectarse automáticamente si se pierde la conexión

Desarrollado con ESP-IDF para ESP32-S3
 
 
