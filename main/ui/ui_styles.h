#ifndef UI_STYLES_H
#define UI_STYLES_H

#include "lvgl.h"

// Declaración de los estilos para ser usados en otros archivos
extern lv_style_t style_fondo;
extern lv_style_t style_texto_principal;
extern lv_style_t style_card;

void ui_styles_init(void);

#endif 