// card.c

#include "card.h"
#include "ui_styles.h"

// Función para crear un card
lv_obj_t *card_create(lv_obj_t *parent) {
    // Crear el objeto de la tarjeta
    lv_obj_t *card = lv_obj_create(parent);

    // Aplicar el estilo de la tarjeta desde ui_styles
    lv_obj_add_style(card, &style_card, 0);

    // Asegurarse de que el objeto ocupe el espacio adecuado
    lv_obj_set_size(card, lv_disp_get_hor_res(NULL) - 40, 400);  // Ancho y altura arbitrarios
    lv_obj_align(card, LV_ALIGN_CENTER, 0, 0);  // Alineación centrada

    return card;
}

