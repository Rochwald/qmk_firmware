// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include <stdio.h>
#include "keyboard.h"

#define KC_COPY  LCTL(KC_C) // copy
#define KC_CUT   LCTL(KC_X) // cut
#define KC_PASTE LCTL(KC_V) // paste
#define KC_ALL   LCTL(KC_A) // select all
#define KC_UNDO  LCTL(KC_Z) // undo
#define KC_REDO  LCTL(KC_Y) // redo

#define MACRO_DELAY 50  // delay in ms between key presses for macros (max value 232)

enum custom_keycodes {
    KC_LAY_UP = SAFE_RANGE,
    KC_LAY_DOWN,
    KC_REPOUR,
    KC_SHELVE,
    KC_UNSHELVE,
    KC_POLY_M,
    KC_FLIP,
    KC_MEASURE,
    KC_1_LAYER,
    KC_LAY_STCK,
    KC_STITCH,
    KC_UNSTITCH,
    KC_DISCORD,
    KC_CHROME,
    KC_VSC,
    KC_ALTIUM,
};

KEYCODE_STRING_NAMES_USER(
    KEYCODE_STRING_NAME(KC_REPOUR),
    KEYCODE_STRING_NAME(KC_SHELVE),
    KEYCODE_STRING_NAME(KC_UNSHELVE),
    KEYCODE_STRING_NAME(KC_POLY_M),
    KEYCODE_STRING_NAME(KC_FLIP),
    KEYCODE_STRING_NAME(KC_MEASURE),
    KEYCODE_STRING_NAME(KC_1_LAYER),
    KEYCODE_STRING_NAME(KC_LAY_STCK),
    KEYCODE_STRING_NAME(KC_STITCH),
    KEYCODE_STRING_NAME(KC_UNSTITCH),
    KEYCODE_STRING_NAME(KC_DISCORD),
    KEYCODE_STRING_NAME(KC_CHROME),
    KEYCODE_STRING_NAME(KC_VSC),
    KEYCODE_STRING_NAME(KC_ALTIUM),

    KEYCODE_STRING_NAME(UG_TOGG),
    KEYCODE_STRING_NAME(UG_PREV),
    KEYCODE_STRING_NAME(UG_NEXT),
    KEYCODE_STRING_NAME(UG_HUED),
    KEYCODE_STRING_NAME(UG_HUEU),
    KEYCODE_STRING_NAME(UG_SATD),
    KEYCODE_STRING_NAME(UG_SATU),
    KEYCODE_STRING_NAME(UG_VALD),
    KEYCODE_STRING_NAME(UG_VALU),
    KEYCODE_STRING_NAME(UG_SPDD),
    KEYCODE_STRING_NAME(UG_SPDU),
    KEYCODE_STRING_NAME(RM_TOGG),
    KEYCODE_STRING_NAME(RM_PREV),
    KEYCODE_STRING_NAME(RM_NEXT),
    KEYCODE_STRING_NAME(RM_HUED),
    KEYCODE_STRING_NAME(RM_HUEU),
    KEYCODE_STRING_NAME(RM_SATD),
    KEYCODE_STRING_NAME(RM_SATU),
    KEYCODE_STRING_NAME(RM_VALD),
    KEYCODE_STRING_NAME(RM_VALU),
    KEYCODE_STRING_NAME(RM_SPDD),
    KEYCODE_STRING_NAME(RM_SPDU),
    KEYCODE_STRING_NAME(QK_RBT),
    KEYCODE_STRING_NAME(BL_DOWN),
    KEYCODE_STRING_NAME(BL_UP)
);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*  numpad layer
     * ┌──────────────┬──────────────┬──────────────┬──────────────┐
     * │     CAPS     │  layer down  │   layer up   │     mute     │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      7       │      8       │      9       │      /       │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      4       │      5       │      6       │      *       │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      1       │      2       │      3       │      -       │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │   NUM_LOCK   │      0       │      ,       │      +       │
     * └──────────────┴──────────────┴──────────────┴──────────────┘
     */
    [0] = LAYOUT_macropad_4x5(
        KC_CAPS,  KC_LAY_DOWN,  KC_LAY_UP,  KC_MUTE,
        KC_P1,    KC_P8,        KC_P9,      KC_PSLS,
        KC_P4,    KC_P5,        KC_P6,      KC_PAST,
        KC_P1,    KC_P2,        KC_P3,      KC_PMNS,
        KC_NUM,   KC_P0,        KC_COMM,    KC_PPLS
    ),

    /*  letters layer
     * ┌──────────────┬──────────────┬──────────────┬──────────────┐
     * │     CAPS     │  layer down  │   layer up   │     mute     │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      a       │      b       │      c       │      d       │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      e       │      f       │      g       │      h       │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      i       │      j       │      k       │      l       │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │      m       │      n       │      o       │      p       │
     * └──────────────┴──────────────┴──────────────┴──────────────┘
     */
    [1] = LAYOUT_macropad_4x5(
        KC_CAPS,  KC_LAY_DOWN,  KC_LAY_UP,  KC_MUTE,
        KC_A,     KC_B,         KC_C,       KC_D,
        KC_E,     KC_F,         KC_G,       KC_H,
        KC_I,     KC_J,         KC_K,       KC_L,
        KC_M,     KC_N,         KC_O,       KC_P
    ),

    /*  commands layer
     * ┌──────────────┬──────────────┬──────────────┬──────────────┐
     * │     CAPS     │  layer down  │   layer up   │     mute     │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │     copy     │     cut      │    paste     │  select all  │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │     undo     │     redož    │              │              │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │  calculator  │ my_computer  │              │     WIN      │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │   CHROME     │VISUAL STUDIO │    ALTIUM    │   DISCORD    │
     * └──────────────┴──────────────┴──────────────┴──────────────┘
     */
    [2] = LAYOUT_macropad_4x5(
        KC_CAPS,    KC_LAY_DOWN,  KC_LAY_UP,  KC_MUTE,
        KC_COPY,    KC_CUT,       KC_PASTE,   KC_ALL,
        KC_UNDO,    KC_REDO,      KC_NO,      KC_NO,
        KC_CALC,    KC_MYCM,      KC_NO,      KC_LWIN,
        KC_CHROME,  KC_VSC,       KC_ALTIUM,  KC_DISCORD
    ),

    /*  Altium layer
     * ┌──────────────┬──────────────┬──────────────┬──────────────┐
     * │     CTRL     │  layer down  │   layer up   │    SHIFT     │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │    repour    │    shelve    │   unshelve   │polygon manage│
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │     flip     │   measure    │ single layer │  layer stack │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │add stitching │ rm stitching │              │              │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │     ESC      │              │              │     ENT      │
     * └──────────────┴──────────────┴──────────────┴──────────────┘
     */
    [3] = LAYOUT_macropad_4x5(
        KC_LCTL,      KC_LAY_DOWN,  KC_LAY_UP,    KC_LSFT,
        KC_REPOUR,    KC_SHELVE,    KC_UNSHELVE,  KC_POLY_M,
        KC_FLIP,      KC_MEASURE,   KC_1_LAYER,   KC_LAY_STCK,
        KC_STITCH,    KC_UNSTITCH,  KC_NO,        KC_NO,
        KC_ESC,       KC_NO,        KC_NO,        KC_ENT
    ),

    /*  RGB & LCD settings layer
     * ┌──────────────┬──────────────┬──────────────┬──────────────┐
     * │   bright -   │  layer down  │   layer up   │   bright +   │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │  RGB ON/OFF  │previous mode │  next mode   │              │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │     hue-     │     hue+     │ saturation - │ saturation + │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │ brightness - │ brightness + │   speed -    │   speed +    │
     * ├──────────────┼──────────────┼──────────────┼──────────────┤
     * │    reboot    │              │ LCD bright - │ LCD bright + │
     * └──────────────┴──────────────┴──────────────┴──────────────┘
     */

     #ifdef RGBLIGHT_ENABLE
        [4] = LAYOUT_macropad_4x5(
            KC_BRID,  KC_LAY_DOWN,  KC_LAY_UP,  KC_BRIU,
            UG_TOGG,  UG_PREV,      UG_NEXT,    KC_NO,
            UG_HUED,  UG_HUEU,      UG_SATD,    UG_SATU,
            UG_VALD,  UG_VALU,      UG_SPDD,    UG_SPDU,
            QK_RBT,   KC_NO,        BL_DOWN,    BL_UP
        )
    #endif

    #ifdef RGB_MATRIX_ENABLE
        [4] = LAYOUT_macropad_4x5(
            KC_BRID,  KC_LAY_DOWN,  KC_LAY_UP,  KC_BRIU,
            RM_TOGG,  RM_PREV,      RM_NEXT,    KC_NO,
            RM_HUED,  RM_HUEU,      RM_SATD,    RM_SATU,
            RM_VALD,  RM_VALU,      RM_SPDD,    RM_SPDU,
            QK_RBT,   KC_NO,        BL_DOWN,    BL_UP
        )
    #endif
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD),              ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [1] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD),              ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [2] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD),              ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [3] = {ENCODER_CCW_CW(LCTL(MS_WHLU), LCTL(MS_WHLD)),  ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},  //TODO: special logic is needed for implementing LCTL(MS_WHLU), LCTL(MS_WHLD)
    [4] = {ENCODER_CCW_CW(UG_VALU, UG_VALD),              ENCODER_CCW_CW(BL_UP, BL_DOWN)},
};

#ifdef RGBLIGHT_ENABLE
    layer_state_t layer_state_set_user(layer_state_t state) {
        switch (get_highest_layer(state)) {
        case 0:
            rgblight_sethsv(HSV_RED);
            break;
        case 1:
            rgblight_sethsv(HSV_GREEN);
            break;
        case 2:
            rgblight_sethsv(HSV_BLUE);
            break;
        case 3:
            rgblight_sethsv(HSV_PINK);
            break;
        case 4:
            rgblight_sethsv(HSV_YELLOW);
            break;
        default: //  for any other layers, or the default layer
            rgblight_sethsv(HSV_OFF);
            break;
        }
    return state;
    }
#endif

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
        // Key Matrix to LED Index
        {NO_LED,  NO_LED,  NO_LED,  NO_LED},
        {0,       1,       2,       3     },
        {7,       6,       5,       4     },
        {8,       9,       10,      11    },
        {15,      14,      13,      12    }
    }, {
        // LED Index to Physical Position
        {0, 0} , {74, 0 }, {149, 0 }, {223, 0 },
        {0, 21}, {74, 21}, {149, 21}, {223, 21},
        {0, 42}, {74, 42}, {149, 42}, {223, 42},
        {0, 63}, {74, 63}, {149, 63}, {223, 63}
    }, {
        // LED Index to Flag
        4, 4, 4, 4,
        4, 4, 4, 4,
        4, 4, 4, 4,
        4, 4, 4, 4
    } };

    bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 0:
                rgb_matrix_sethsv(HSV_RED);
                break;
            case 1:
                rgb_matrix_sethsv(HSV_GREEN);
                break;
            case 2:
                rgb_matrix_sethsv(HSV_BLUE);
                break;
            case 3:
                rgb_matrix_sethsv(HSV_PINK);
                break;
            case 4:
                rgb_matrix_sethsv(HSV_YELLOW);
                break;
            default:
                rgb_matrix_sethsv(HSV_OFF);
                break;
        }
    return false;
}
#endif

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

// Action functions for custom keycodes
static void action_lay_up(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer < LAYER_CYCLE_START || current_layer > LAYER_CYCLE_END) return;
    uint8_t next_layer = current_layer + 1;
    if (next_layer > LAYER_CYCLE_END) next_layer = LAYER_CYCLE_START;
    qp_rect(display, 0, 0, 239, 239, 0, 0, 255, true);  // clear display
    layer_move(next_layer);
}

static void action_lay_down(void) {
    uint8_t current_layer = get_highest_layer(layer_state);
    if (current_layer < LAYER_CYCLE_START || current_layer > LAYER_CYCLE_END) return;
    uint8_t next_layer = current_layer - 1;
    if (next_layer > LAYER_CYCLE_END) next_layer = LAYER_CYCLE_END;
    qp_rect(display, 0, 0, 239, 239, 0, 0, 255, true);  // clear display
    layer_move(next_layer);
}

static void action_kc_repour(void)      { SEND_STRING_DELAY("tga", MACRO_DELAY); }
static void action_kc_shelve(void)      { SEND_STRING_DELAY("tgh", MACRO_DELAY); }
static void action_kc_unshelve(void)    { SEND_STRING_DELAY("tge", MACRO_DELAY); }
static void action_kc_poly_m(void)      { SEND_STRING_DELAY("tgm", MACRO_DELAY); }
static void action_kc_flip(void)        { SEND_STRING_DELAY("vb", MACRO_DELAY); }
static void action_kc_measure(void)     { SEND_STRING_DELAY(SS_LCTL("m"), 0); }
static void action_kc_1_layer(void)     { SEND_STRING_DELAY(SS_LSFT("s"), 0); }
static void action_kc_lay_stck(void)    { SEND_STRING_DELAY("dk", MACRO_DELAY); }
static void action_kc_stitch(void)      { SEND_STRING_DELAY("tha", MACRO_DELAY); }
static void action_kc_unstitch(void)    { SEND_STRING_DELAY("thr", MACRO_DELAY); }
static void action_kc_discord(void)     { SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(250) "discord" SS_DELAY(250) SS_TAP(X_ENT)); }
static void action_kc_chrome(void)      { SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(250) "chrome" SS_DELAY(250) SS_TAP(X_ENT)); }
static void action_kc_vsc(void)         { SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(250) "visual studio code" SS_DELAY(250) SS_TAP(X_ENT)); }
static void action_kc_altium(void)      { SEND_STRING(SS_TAP(X_LGUI) SS_DELAY(250) "altium" SS_DELAY(250) SS_TAP(X_ENT)); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_LAY_UP:      return handle_custom_key(keycode, record, action_lay_up);
        case KC_LAY_DOWN:    return handle_custom_key(keycode, record, action_lay_down);
        case KC_REPOUR:      return handle_custom_key(keycode, record, action_kc_repour);
        case KC_SHELVE:      return handle_custom_key(keycode, record, action_kc_shelve);
        case KC_UNSHELVE:    return handle_custom_key(keycode, record, action_kc_unshelve);
        case KC_POLY_M:      return handle_custom_key(keycode, record, action_kc_poly_m);
        case KC_FLIP:        return handle_custom_key(keycode, record, action_kc_flip);
        case KC_MEASURE:     return handle_custom_key(keycode, record, action_kc_measure);
        case KC_1_LAYER:     return handle_custom_key(keycode, record, action_kc_1_layer);
        case KC_LAY_STCK:    return handle_custom_key(keycode, record, action_kc_lay_stck);
        case KC_STITCH:      return handle_custom_key(keycode, record, action_kc_stitch);
        case KC_UNSTITCH:    return handle_custom_key(keycode, record, action_kc_unstitch);
        case KC_DISCORD:     return handle_custom_key(keycode, record, action_kc_discord);
        case KC_CHROME:      return handle_custom_key(keycode, record, action_kc_chrome);
        case KC_VSC:         return handle_custom_key(keycode, record, action_kc_vsc);
        case KC_ALTIUM:      return handle_custom_key(keycode, record, action_kc_altium);
        default:
            // Suppress highlight for normal keycodes in row 0
            if (record->event.key.row == 0) {
                return true;   // let QMK handle key, but skip post_process_record_kb highlight
            }
            return true;       // normal behavior for all other keys
    }
}