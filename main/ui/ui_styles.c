#include "ui_styles.h"

// Definición de colores en formato hexadecimal
/*
-------------------------------------
|  Hexadecimal   |  Color Name      |
|----------------|------------------|
| #F4A300      | Vivid Amber      |
| #09B1B7      | Medium Turquoise |
| #E2B97F      | Light Gold       |
| #EE5F5B      | Reddish Pink     |
| #DAA520      | Goldenrod        |
| #9C42A3      | Medium Purple    |
| #9C270C      | Dark Red         |
| #4A7C59      | Dark Olive Green |
| #A12A0A      | Firebrick        |
| #31668B      | Blue Green       |
| #D32F2F      | Fire Engine Red  |
| #FF8C00      | Dark Orange      |
| #56B4D3      | Powder Blue      |
| #017D3B      | Emerald Green    |
| #2E75B6      | Azure Blue       |
| #07243b      | Gunmetal         |
| #001626      | Azul profundo    |
| #f0efe7      | Marfil           |
| #72b1c3      | Azul Claro       |
| #e89c32      | Mostaza          |
-------------------------------------
*/

#define COLOR_FONDO1 lv_color_hex(0x07243b)
#define COLOR_FONDO2 lv_color_hex(0x001626)
#define COLOR_PRIMARIO lv_color_hex(0xf0efe7)
#define COLOR_SECUNDARIO lv_color_hex(0x72b1c3)
#define COLOR_TERCIARIO lv_color_hex(0x31668B)

// Declaraciones de estilos
lv_style_t style_fondo;
lv_style_t style_titulo1;
lv_style_t style_titulo2;
lv_style_t style_texto1;
lv_style_t style_texto2;
lv_style_t style_card;
lv_style_t style_subcard;

void ui_styles_init(void) {
    // === Estilo de base_screen ===
    lv_style_init(&style_fondo); // inicializa el estilo
    lv_style_set_bg_color(&style_fondo, COLOR_FONDO1); // establece color de fondo
    lv_style_set_bg_opa(&style_fondo, LV_OPA_COVER);  // opacidad al 100%
    lv_style_set_border_width(&style_fondo, 0); // Esto elimina el borde blanco
    lv_style_set_radius(&style_fondo, 0);        // Elimina el radio de las esquinas
    lv_style_set_pad_all(&style_fondo, 20);  // Esto agrega el padding

    // === Estilo de titulo1 ===
    lv_style_init(&style_titulo1);
    lv_style_set_text_color(&style_titulo1, COLOR_PRIMARIO);
    lv_style_set_text_font(&style_titulo1, &lv_font_montserrat_48);
    lv_style_set_text_align(&style_titulo1, LV_TEXT_ALIGN_LEFT);

    // === Estilo de titulo2 ===
    lv_style_init(&style_titulo2);
    lv_style_set_text_color(&style_titulo2, COLOR_PRIMARIO);
    lv_style_set_text_font(&style_titulo2, &lv_font_montserrat_22);
    lv_style_set_text_align(&style_titulo2, LV_TEXT_ALIGN_LEFT);

    // === Estilo de texto1 ===
    lv_style_init(&style_texto1);
    lv_style_set_text_color(&style_texto1, COLOR_PRIMARIO);
    lv_style_set_text_font(&style_texto1, &lv_font_montserrat_16);
    lv_style_set_text_align(&style_texto1, LV_TEXT_ALIGN_LEFT);

    // === Estilo de texto2 ===
    lv_style_init(&style_texto2);
    lv_style_set_text_color(&style_texto2, COLOR_PRIMARIO);
    lv_style_set_text_font(&style_texto2, &lv_font_montserrat_8);
    lv_style_set_text_align(&style_texto2, LV_TEXT_ALIGN_LEFT);

    // === Estilo de card ===
    lv_style_init(&style_card);
    lv_style_set_bg_color(&style_card, COLOR_FONDO2);  // Color de fondo del card
    lv_style_set_bg_opa(&style_card, LV_OPA_COVER);    // Opacidad 100%
    lv_style_set_border_width(&style_card, 0);         // Ancho del borde
    lv_style_set_border_color(&style_card, COLOR_SECUNDARIO);  // Color del borde
    lv_style_set_radius(&style_card, 10);              // Radio de las esquinas
    lv_style_set_pad_all(&style_card, 10);             // Padding dentro del card

    // === Estilo de subcard ===
    lv_style_init(&style_subcard);
    lv_style_set_bg_color(&style_subcard, COLOR_FONDO1);  // Color de fondo del card
    lv_style_set_bg_opa(&style_subcard, LV_OPA_COVER);    // Opacidad 100%
    lv_style_set_border_width(&style_subcard, 0);         // Ancho del borde
    lv_style_set_border_color(&style_subcard, COLOR_SECUNDARIO);  // Color del borde
    lv_style_set_radius(&style_subcard, 10);              // Radio de las esquinas
    lv_style_set_pad_all(&style_subcard, 10);             // Padding dentro del card

} 
