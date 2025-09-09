// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "qp.h"
#include "qp_st7789.h"        // Add this line for your specific display
#include "color.h"            // Add this for COLOR constants

#include "Mario_240x240.qgf.h"
#include "Black_Copper_240x240.qgf.h"
#include "test_gif.qgf.h"

static painter_device_t       display;
static painter_image_handle_t my_image;

void keyboard_post_init_user(void) {
    display = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, SPI_MODE);

    // first image
    qp_init(display, LCD_ROTATION);
    qp_clear(display);
    my_image = qp_load_image_mem(gfx_Mario_240x240);
    qp_drawimage(display, 0, 0, my_image);
    qp_flush(display);

    wait_ms(3000);

    // second image
    qp_clear(display);
    my_image = qp_load_image_mem(gfx_Black_Copper_240x240);
    qp_drawimage(display, 0, 0, my_image);
    qp_flush(display);

    /*
    wait_ms(3000);

    // animated gif
    qp_clear(display);
    my_image = qp_load_image_mem(gfx_test_gif);
    qp_animate(display, 0, 0, my_image);
    qp_flush(display);
    */
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_4x1(
        BL_DOWN, KC_B, KC_C, BL_UP
        )
};
