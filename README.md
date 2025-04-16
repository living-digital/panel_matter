# panel_matter
Este proyecto permite conectar un ESP32 con display de 4" a una red WiFi, tambien trabajaremos con esp-matter (fork de Matter especifico para esta plataforma) para la conectividad de dispositivos IOT, todo ello con una interfaz generada con lvgl


## Instalacion de ESP-IDF y compilacion del proyecto:

Para compilar este proyecto es imprescindible utilizar ESP-IDF versión 5.2.3, para obtener esta versión, primero clona el repositorio oficial de ESP-IDF:
```
git clone https://github.com/espressif/esp-idf.git"
```
una vez clonado, ingresar al directorio esp-idf y ejecuta:
```
git fetch    # Descargar información (commits, ramas, etiquetas, etc.) desde el repositorio remoto
git checkout v5.2.3    # Cambiar a versión etiquetada v5.2.3, git mueve el puntero HEAD a esa etiqueta
git submodule update --init --recursive   # Inicializar y actualizar todos los submódulos
```
Instalaremos IDF:
```
./install.sh
. ./export.sh
```

Tambien se requiere LVGL v8.3.11 (Incluido en los components), LVGL v9 resulta incompatible.

para la compilacion del proyecto, usaremos el siguiente comando desde la carpeta raiz del proyecto:
```
idf.py build
```
Para averigual el archivo que corresponde a nuestro dispositivo lanzaremos un ls con el dispositivo desconectado y otro ls con el dispositivo conectado:
```
david@PC-DAVID:~/esp/panel_matter$ ls /dev/tty*
tty        tty16      tty24      tty32      tty40      tty49      tty57      tty8       ttyS14     ttyS22     ttyS30
tty0       tty17      tty25      tty33      tty41      tty5       tty58      tty9       ttyS15     ttyS23     ttyS31
tty1       tty18      tty26      tty34      tty42      tty50      tty59      ttyprintk  ttyS16     ttyS24     ttyS4
tty10      tty19      tty27      tty35      tty43      tty51      tty6       ttyS0      ttyS17     ttyS25     ttyS5
tty11      tty2       tty28      tty36      tty44      tty52      tty60      ttyS1      ttyS18     ttyS26     ttyS6
tty12      tty20      tty29      tty37      tty45      tty53      tty61      ttyS10     ttyS19     ttyS27     ttyS7
tty13      tty21      tty3       tty38      tty46      tty54      tty62      ttyS11     ttyS2      ttyS28     ttyS8
tty14      tty22      tty30      tty39      tty47      tty55      tty63      ttyS12     ttyS20     ttyS29     ttyS9
tty15      tty23      tty31      tty4       tty48      tty56      tty7       ttyS13     ttyS21     ttyS3      
david@PC-DAVID:~/esp/panel_matter$ ls /dev/tty*
tty        tty16      tty24      tty32      tty40      tty49      tty57      tty8       ttyS13     ttyS21     ttyS3
tty0       tty17      tty25      tty33      tty41      tty5       tty58      tty9       ttyS14     ttyS22     ttyS30
tty1       tty18      tty26      tty34      tty42      tty50      tty59      ttyACM0    ttyS15     ttyS23     ttyS31
tty10      tty19      tty27      tty35      tty43      tty51      tty6       ttyprintk  ttyS16     ttyS24     ttyS4
tty11      tty2       tty28      tty36      tty44      tty52      tty60      ttyS0      ttyS17     ttyS25     ttyS5
tty12      tty20      tty29      tty37      tty45      tty53      tty61      ttyS1      ttyS18     ttyS26     ttyS6
tty13      tty21      tty3       tty38      tty46      tty54      tty62      ttyS10     ttyS19     ttyS27     ttyS7
tty14      tty22      tty30      tty39      tty47      tty55      tty63      ttyS11     ttyS2      ttyS28     ttyS8
tty15      tty23      tty31      tty4       tty48      tty56      tty7       ttyS12     ttyS20     ttyS29     ttyS9
```
vemos que nuestro dispositivo aparece en la lista como **/dev/ttyACM0**, y ya podemos subir nuestro codigo al hardware:
```
idf.py -p /dev/ttyACM0 flash monitor
```
El parametro *flash* indica que vamos a `flashear` el chip con nuestro codigo

El parametro *monitor* deja nuestra terminal a la escucha de la informacion que nos envie el hardware

El parametro *build* (va entre la ruta de nuestro dispositivo y el parametro flash) compila nuestro codigo antes de flashear

El parametro *erase-flash* (antes de build) borra el firmware actual antes de subir el nuevo

## Hardware

Fabricante: Espressif

Entorno desarrollo recomendado: ESP-IDF

Modelo: Placa de entrenamiento ESP32-S3-LCD-EV v0.2

Serigrafia: ESP-RGB_LCD

CPU: Núcleo Xtensa LX7

Número de Núcleos: 2

Frecuencia de CPU: 240 MHz

Memoria RAM: Aproximadamente 320 KB de SRAM interna

Flash Interna: 16 MB

Conectividad WiFi: 802.11 b/g/n

Conectividad Bluetooth: Bluetooth Low Energy (BLE) 5.0

Interfaces USB: USB-C

<table>
  <tr>
    <td><img src="https://github.com/living-digital/panel_matter/blob/main/IMG/1.jpg" width="200" title="HomeScreen"></td>
    <td><img src="https://github.com/living-digital/panel_matter/blob/main/IMG/2.jpg" alt="AuthorListViewScreen" width="200" title="AuthorListViewScreen"></td>
    <td><img src="https://github.com/living-digital/panel_matter/blob/main/IMG/3.jpg" alt="AuthorAddScreen" width="200" title="AuthorAddScreen"></td>
  </tr>
   <tr>
    <td><img src="https://github.com/living-digital/panel_matter/blob/main/IMG/4.jpg" alt="HomeScreen" width="200" title="HomeScreen"></td>
    <td><img src="https://github.com/living-digital/panel_matter/blob/main/IMG/5.jpg" alt="AuthorListViewScreen" width="200" title="AuthorListViewScreen"></td>
    <td><img src="https://github.com/living-digital/panel_matter/blob/main/IMG/6.jpg" alt="AuthorAddScreen" width="200" title="AuthorAddScreen"></td>
  </tr>
</table>

## Requisitos Hardware

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
 
 
 
 
 
 
 
 
 
 
