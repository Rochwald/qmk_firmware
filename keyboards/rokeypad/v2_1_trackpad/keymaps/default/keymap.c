// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include <stdio.h>
#include "keyboard.h"

enum custom_keycodes {
    KC_LAY_UP = SAFE_RANGE,
    KC_LAY_DOWN,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_1x6(
        KC_LAY_DOWN,  MS_BTN1,  MS_BTN4,  MS_BTN5,  MS_BTN2,  KC_LAY_UP
    ),

    [1] = LAYOUT_1x6(
        KC_LAY_DOWN,  KC_B,  KC_H,  KC_G,  KC_U,  KC_LAY_UP
    )
};

// joystick configuration for gamepad
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    [0] = JOYSTICK_AXIS_IN(C4, 0, 512, 1023),   // JOYSTICK1_X
    [1] = JOYSTICK_AXIS_IN(C5, 0, 512, 1023),   // JOYSTICK1_Y
    [2] = JOYSTICK_AXIS_IN(NO_PIN, 0, 512, 1023),   // JOYSTICK1_Y
    [3] = JOYSTICK_AXIS_IN(C0, 0, 512, 1023),   // JOYSTICK2_X
    [4] = JOYSTICK_AXIS_IN(C1, 0, 512, 1023),   // JOYSTICK2_Y
};

// Helper for custom keycodes with highlighting
bool handle_custom_key(uint16_t keycode, keyrecord_t *record, void (*action)(void)) {
    if (record->event.key.row == 0) {   // Skip row 0: just run the macro if defined
        if (record->event.pressed && action) {
            action();
        }
        return false;  // prevent normal processing
    }
    if (record->event.pressed) {
        post_process_record_kb(keycode, record);    // highlight pressed key
        if (action) action();                       // perform the macro/action
    } else {
        post_process_record_kb(keycode, record);    // un-highlight on release
    }
    return false;  // suppress normal keycode
}

// --- Action functions for custom keycodes ---
static void action_lay_up(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer < LAYER_CYCLE_START || current_layer > LAYER_CYCLE_END) return;
    uint8_t next_layer = current_layer + 1;
    if (next_layer > LAYER_CYCLE_END) next_layer = LAYER_CYCLE_START;
    qp_rect(display, 0, 0, 239, 239, 0, 0, 255, true);
    layer_move(next_layer);
}

static void action_lay_down(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer < LAYER_CYCLE_START || current_layer > LAYER_CYCLE_END) return;
    uint8_t next_layer = current_layer - 1;
    if (next_layer > LAYER_CYCLE_END) next_layer = LAYER_CYCLE_END;
    qp_rect(display, 0, 0, 239, 239, 0, 0, 255, true);
    layer_move(next_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LAY_UP:      return handle_custom_key(keycode, record, action_lay_up);
        case KC_LAY_DOWN:    return handle_custom_key(keycode, record, action_lay_down);
        default:
            // Suppress highlight for normal keycodes in row 0
            if (record->event.key.row == 0) {
                return true;   // let QMK handle key, but skip post_process_record_kb highlight
            }
            return true;       // normal behavior for all other keys
    }
}