# panel_matter
Este proyecto permite conectar un ESP32 con display de 4" a una red WiFi, tambien trabajaremos con esp-matter (fork de Matter especifico para esta plataforma) para la conectividad de dispositivos IOT, todo ello con una interfaz generada con lvgl


## Requisitos previos:

ESP-IDF instalado (v5.0 o superior recomendado)

Cable USB para flashear el ESP32

Red WiFi de 2.4 GHz (el ESP32 no es compatible con redes de 5 GHz)


## Notas:

Asegúrate de que la red wifi sea visible y opere en la banda de 2.4 GHz

Si estás usando IP fija, evita conflictos con el rango DHCP del router

El sistema intentará reconectarse automáticamente si se pierde la conexión


## Notas:
Desarrollado con ESP-IDF para ESP32-S3