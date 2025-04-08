// ui_styles.c
#include "ui_styles.h"

// Definición de colores en formato hexadecimal
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
    // === Estilo de fondo ===
    lv_style_init(&style_fondo);
    lv_style_set_bg_color(&style_fondo, COLOR_FONDO1);
    lv_style_set_bg_opa(&style_fondo, LV_OPA_COVER);

    // === Estilo de texto principal ===
    lv_style_init(&style_texto_principal);
    lv_style_set_text_color(&style_texto_principal, COLOR_PRIMARIO);
    lv_style_set_text_font(&style_texto_principal, &lv_font_montserrat_16);
    lv_style_set_text_align(&style_texto_principal, LV_TEXT_ALIGN_LEFT);

    // === Estilo de tarjeta (contenedor con sombra) ===
    lv_style_init(&style_card);
    lv_style_set_bg_color(&style_card, COLOR_FONDO2);
    lv_style_set_bg_opa(&style_card, LV_OPA_COVER);
    lv_style_set_border_color(&style_card, COLOR_SECUNDARIO);
    lv_style_set_border_width(&style_card, 2);
    lv_style_set_radius(&style_card, 12);
    lv_style_set_pad_all(&style_card, 12);
    lv_style_set_shadow_color(&style_card, COLOR_TERCIARIO);
    lv_style_set_shadow_width(&style_card, 10);
    lv_style_set_shadow_ofs_x(&style_card, 4);
    lv_style_set_shadow_ofs_y(&style_card, 4);
} 
