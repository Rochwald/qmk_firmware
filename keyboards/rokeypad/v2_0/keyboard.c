// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "keyboard.h"

#define WELCOME_TIMEOUT_MS 2000 // welcome display timeout

#define GRID_ROWS 4
#define GRID_COLS 4
#define TOP_OFFSET 40
#define BOTTOM_OFFSET 0
#define LEFT_OFFSET 0
#define RIGHT_OFFSET (LEFT_OFFSET)   // should be the same to keep grid left-right symetrical

#define GRID_WIDTH (LCD_WIDTH  - LEFT_OFFSET - RIGHT_OFFSET)
#define GRID_HEIGHT (LCD_HEIGHT - TOP_OFFSET - BOTTOM_OFFSET)
#define CELL_WIDTH (GRID_WIDTH / GRID_COLS)
#define CELL_HEIGHT (GRID_HEIGHT / GRID_ROWS)

#define RECT_MARGIN 2   // margain for highlighting keys on the display

static painter_image_handle_t welcome_image; // image object
static deferred_token display_task_token;

painter_device_t       display;  // display device
painter_font_handle_t  font_bold32;     // font object
painter_font_handle_t  font20;     // font object
painter_font_handle_t  font12;     // font object

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
static bool force_redraw = false;

typedef struct {
    uint8_t h;
    uint8_t s;
    uint8_t v;
} hsv_helper_t;

static hsv_helper_t current_layer_color = {HSV_WHITE};

#if defined(DISPLAY_BACKLIGHT_TIMEOUT) && (DISPLAY_BACKLIGHT_TIMEOUT > 0)
void display_timeout_backlight(void) {
    static bool display_on                  = true;
    bool        should_change_display_state = false;
    bool        target_display_state        = false;
    if (last_input_activity_elapsed() < (DISPLAY_BACKLIGHT_TIMEOUT)) {
        should_change_display_state = (display_on == false);
        target_display_state        = true;
    } else {
        should_change_display_state = (display_on == true);
        target_display_state        = false;
    }

    if (should_change_display_state) {
        if (target_display_state) {
            backlight_enable();
        } else {
            backlight_disable();
        }
    }
    display_on = target_display_state;
}
#endif // DISPLAY_BACKLIGHT_TIMEOUT

void clear_display_white(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
    qp_clear(display);
    qp_rect(display, x1, y1, x2, y2, 0, 0, 255, true);
    qp_flush(display);
}

uint32_t display_task_callback(uint32_t trigger_time, void *cb_arg) {
    static bool welcome_done = false;

    if (!welcome_done) {
        // Welcome timeout finished
        welcome_done = true;
        force_redraw = true;  // force redraw to replace welcome screen
    }

    display_task_kb();
    return 100; // call every 100 ms continuously
}

const char *shorten_keycode(uint16_t keycode) {
    switch (keycode) {
        case KC_NO:          return "";
        case KC_NUM_LOCK:    return "NUMLOCK";
        case KC_KP_SLASH:    return "/";
        case KC_KP_ASTERISK: return "*";
        case KC_KP_MINUS:    return "-";
        case KC_KP_PLUS:     return "+";
        case KC_COMM:        return ",";
        case KC_CALC:        return "CALC";
        case KC_MYCM:        return "FILES";
        case KC_BRID:        return "Bright+";
        case KC_BRIU:        return "Bright-";
        default:             break;
    }

    static char buf[9]; // 8 characters + null-terminator
    const char *full = get_keycode_string(keycode);

    // List of known prefixes
    const char *prefixes[] = {"KC_KP_", "KC_", "QK_", NULL };

    // Check and strip known prefix
    for (int8_t i = 0; prefixes[i] != NULL; ++i) {
        size_t len = strlen(prefixes[i]);
        if (strncmp(full, prefixes[i], len) == 0) {
            full += len;
            break;
        }
    }

    // Copy the rest (truncated to fit the buffer)
    strncpy(buf, full, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';
    return buf;
}

void display_write_single_keycode(uint8_t layer, uint8_t row, uint8_t col, painter_font_handle_t font) {
    // get keycode, without first row (encoders and layer change buttons)
    #ifdef VIA_ENABLE
        uint16_t keycode = dynamic_keymap_get_keycode(layer, row+1, col);
    #else
        uint16_t keycode = keymaps[layer][row+1][col];
    #endif

    const char *keycode_string = shorten_keycode(keycode);

    // Calculate position
    int16_t x0 = LEFT_OFFSET + col * CELL_WIDTH;
    int16_t y0 = TOP_OFFSET + row * CELL_HEIGHT;
    int16_t cx = x0 + CELL_WIDTH / 2;
    int16_t cy = y0 + CELL_HEIGHT / 2;

    int16_t text_height = font->line_height;
    int16_t text_width = qp_textwidth(font, keycode_string);

    // Draw text at the center (adjust as needed for alignment)
    qp_drawtext_recolor(display, cx - text_width/2, cy - text_height/2, font, keycode_string, HSV_BLACK, HSV_WHITE);
}

void display_write_all_keycodes(uint8_t layer, painter_font_handle_t font) {
    for (int16_t row = 0; row < GRID_ROWS; row++) {
        for (int16_t col = 0; col < GRID_COLS; col++) {
            display_write_single_keycode(layer, row, col, font);
        }
    }
}

void display_write_layer_name(char *layer_name, painter_font_handle_t font, uint8_t h, uint8_t s, uint8_t v) {
    int16_t text_height = font->line_height;
    int16_t text_width = qp_textwidth(font, layer_name);
    qp_drawtext_recolor(display, ((LCD_WIDTH-1)/2 - text_width/2), text_height/2 - 1, font, layer_name, HSV_BLACK, h, s, v);
}

void display_init_kb(void) {

    if (!display_init_user()) {
        return;
    }

    display = qp_st7789_make_spi_device(LCD_WIDTH, LCD_HEIGHT, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, LCD_SPI_DIVISOR, SPI_MODE);
    qp_init(display, LCD_ROTATION);
    clear_display_white(0, 0, (LCD_WIDTH-1), (LCD_HEIGHT-1));

    font_bold32 = qp_load_font_mem(font_roboto_bold32);
    font20 = qp_load_font_mem(font_roboto20);
    font12 = qp_load_font_mem(font_roboto12);

    welcome_image = qp_load_image_mem(gfx_logo_120x120);

    static const char *text_top1 = "Welcome to";
    static const char *text_top2 = "RoKeyPad";
    static const char *text_bottom = "HrovaTech";
    int16_t width_text_top1 = qp_textwidth(font20, text_top1);
    int16_t width_text_top2 = qp_textwidth(font_bold32, text_top2);
    int16_t width_text_bottom = qp_textwidth(font20, text_bottom);
    int16_t text_height_font20 = font20->line_height;
    int16_t text_height_font32 = font_bold32->line_height;
    int16_t welcome_image_width = welcome_image->width;
    int16_t welcome_image_height = welcome_image->height;

    qp_drawimage( display, (LCD_WIDTH/2 - welcome_image_width/2 - 1), (LCD_HEIGHT/2 - welcome_image_height/2 + 30), welcome_image );
    qp_drawtext_recolor( display, (LCD_WIDTH/2 - width_text_top1/2 - 1), (text_height_font20)/2, font20, text_top1, HSV_BLACK, HSV_WHITE );
    qp_drawtext_recolor( display, (LCD_WIDTH/2 - width_text_top2/2 - 1), (text_height_font20)/2 + (text_height_font32), font_bold32, text_top2, HSV_BLACK, HSV_WHITE );
    qp_drawtext_recolor( display, (LCD_WIDTH - width_text_bottom - 5), (LCD_HEIGHT - text_height_font20 - 1), font20, text_bottom, HSV_BLACK, HSV_WHITE );
    qp_flush(display);

    qp_close_image(welcome_image);
    display_task_token = defer_exec(WELCOME_TIMEOUT_MS, display_task_callback, NULL);
}

__attribute__((weak)) bool display_init_user(void) {
    return true;
}

void display_task_kb(void) {
    static uint8_t last_drawn_layer = 255;
    uint8_t current_layer = get_highest_layer(layer_state);

    if (!display_task_user()) {
        return;
    }

    if (current_layer != last_drawn_layer || force_redraw) {
        force_redraw = false;  // reset flag
        last_drawn_layer = current_layer;
        qp_rect(display, 0, 0, (LCD_WIDTH-1), (LCD_HEIGHT-1), HSV_WHITE, true);   // Clear before drawing new layer

        // optional: draw grid outside border
        //qp_rect(display, LEFT_OFFSET, TOP_OFFSET, LEFT_OFFSET + GRID_COLS * CELL_WIDTH - 1, TOP_OFFSET + GRID_ROWS * CELL_HEIGHT - 1, HSV_BLACK, false);

        // draw vertical lines
        for (int16_t col = 0; col < GRID_COLS - 1; col++) {
            int16_t x = LEFT_OFFSET + (col + 1) * CELL_WIDTH;
            qp_line(display, x, TOP_OFFSET, x, LCD_HEIGHT - BOTTOM_OFFSET - 1, HSV_BLACK);
        }

        // draw horizontal lines
        for (int16_t row = 0; row < GRID_ROWS - 1; row++) {
            int16_t y = TOP_OFFSET + (row + 1) * CELL_HEIGHT;
            qp_line(display, LEFT_OFFSET, y, LCD_WIDTH - RIGHT_OFFSET - 1, y, HSV_BLACK);
        }

        // draw layer info
        switch (get_highest_layer(layer_state)) {
            case 0:
                current_layer_color = (hsv_helper_t){HSV_RED};
                display_write_layer_name("Numpad", font20, current_layer_color.h, current_layer_color.s, current_layer_color.v);
                display_write_all_keycodes(0, font12);
                break;

            case 1:
                current_layer_color = (hsv_helper_t){HSV_GREEN};
                display_write_layer_name("Letters", font20, current_layer_color.h, current_layer_color.s, current_layer_color.v);
                display_write_all_keycodes(1, font12);
                break;

            case 2:
                current_layer_color = (hsv_helper_t){HSV_BLUE};
                display_write_layer_name("Commands/Shortcuts", font20, current_layer_color.h, current_layer_color.s, current_layer_color.v);
                display_write_all_keycodes(2, font12);
                break;

            case 3:
                current_layer_color = (hsv_helper_t){HSV_ALTIUM};
                display_write_layer_name("Altium", font20, current_layer_color.h, current_layer_color.s, current_layer_color.v);
                display_write_all_keycodes(3, font12);
                break;

            case 4:
                current_layer_color = (hsv_helper_t){HSV_PINK};
                display_write_layer_name("Settings", font20, current_layer_color.h, current_layer_color.s, current_layer_color.v);
                display_write_all_keycodes(4, font12);
                break;

            default:
                current_layer_color = (hsv_helper_t){HSV_WHITE};
                display_write_layer_name("INVALID LAYER", font20, current_layer_color.h, current_layer_color.s, current_layer_color.v);
        }
    }
}

__attribute__((weak)) bool display_task_user(void) {
    return true;
}

void keyboard_post_init_kb(void) {
    backlight_enable(); // make sure LCD backlight is ON
    display_init_kb();
}

void post_process_record_kb(uint16_t keycode, keyrecord_t *record) {  // is executed AFTER every keypress
    if (record->event.key.row == 0) {
        return;
    }

    uint8_t pressed_row = record->event.key.row - 1;   // 1-4 (0-rotary encoders and layer change)
    uint8_t pressed_col = record->event.key.col;       // 0-3

    int16_t x1 = LEFT_OFFSET + pressed_col * CELL_WIDTH + RECT_MARGIN;
    int16_t y1 = TOP_OFFSET  + pressed_row * CELL_HEIGHT + RECT_MARGIN;
    int16_t x2 = LEFT_OFFSET + (pressed_col+1) * CELL_WIDTH - RECT_MARGIN;
    int16_t y2 = TOP_OFFSET  + (pressed_row+1) * CELL_HEIGHT - RECT_MARGIN;
    if (record->event.pressed) {  //if any key was pressed down
        qp_rect(display, x1, y1, x2, y2, current_layer_color.h, current_layer_color.s, current_layer_color.v, true);
    }
    else {
        qp_rect(display, x1, y1, x2, y2, HSV_WHITE, true);
    }
    display_write_single_keycode(get_highest_layer(layer_state), pressed_row, pressed_col, font12);

}

void housekeeping_task_kb(void) {
    #if defined(DISPLAY_BACKLIGHT_TIMEOUT) && (DISPLAY_BACKLIGHT_TIMEOUT > 0)
    display_timeout_backlight();
    #endif
}

void dynamic_keymap_user_keycode_changed(uint8_t layer, uint8_t key, uint16_t keycode) {
    force_redraw = true;
    display_task_kb();
}