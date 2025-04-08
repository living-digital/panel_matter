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
#define COLOR_TERCIARIO lv_color_hex(0xe89c32)

// Declaraciones de estilos
lv_style_t style_fondo;
lv_style_t style_texto_principal;
lv_style_t style_card;

void ui_styles_init(void) {
    // === Estilo de base_screen ===
    lv_style_init(&style_fondo); // inicializa el estilo
    lv_style_set_bg_color(&style_fondo, COLOR_FONDO1); // establece color de fondo
    lv_style_set_bg_opa(&style_fondo, LV_OPA_COVER);  // opacidad al 100%
    lv_style_set_border_width(&style_fondo, 0); // Esto elimina el borde blanco
    lv_style_set_radius(&style_fondo, 0);        // Elimina el radio de las esquinas
    lv_style_set_pad_all(&style_fondo, 20);  // Esto agrega el padding

    // === Estilo de texto principal ===
    lv_style_init(&style_texto_principal);
    lv_style_set_text_color(&style_texto_principal, COLOR_PRIMARIO);
    lv_style_set_text_font(&style_texto_principal, &lv_font_montserrat_16);
    lv_style_set_text_align(&style_texto_principal, LV_TEXT_ALIGN_LEFT);

    // === Estilo de tarjeta (contenedor con sombra) ===
    lv_style_init(&style_card);
    lv_style_set_bg_color(&style_card, COLOR_FONDO2);  // Color de fondo del card
    lv_style_set_bg_opa(&style_card, LV_OPA_COVER);    // Opacidad 100%
    lv_style_set_border_width(&style_card, 2);         // Ancho del borde
    lv_style_set_border_color(&style_card, COLOR_SECUNDARIO);  // Color del borde
    lv_style_set_radius(&style_card, 10);              // Radio de las esquinas
    lv_style_set_pad_all(&style_card, 10);             // Padding dentro del card

} 
