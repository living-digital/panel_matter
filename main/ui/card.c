// card.c

#include "card.h"
#include "ui_styles.h"

// Función para crear un card
// x = horizontal
// y = vertical
lv_obj_t *card_create(lv_obj_t *parent, int x, int y, int ancho, int alto) {
    // Crear el objeto de la tarjeta
    lv_obj_t *card = lv_obj_create(parent);

    // Aplicar el estilo de la tarjeta desde ui_styles
    lv_obj_add_style(card, &style_card, 0);

    // Establecer el tamaño de la tarjeta usando los parámetros
    lv_obj_set_size(card, ancho, alto);  

    // Alineación de la tarjeta en la posición dada
    lv_obj_set_pos(card, x, y);  

    return card;
}
