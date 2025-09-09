// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"
#include "qp.h"
#include "qp_st7789.h"
#include "color.h"
#include "keycode.h"

#include "graphics/logo_120x120.qgf.h"
#include "graphics/roboto_bold32.qff.h"
#include "graphics/roboto20.qff.h"
#include "graphics/roboto12.qff.h"

extern painter_device_t display;
extern painter_font_handle_t font_bold32;
extern painter_font_handle_t font20;
extern painter_font_handle_t font12;

void display_timeout_backlight(void);
void clear_display_white(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
uint32_t display_task_callback(uint32_t trigger_time, void *cb_arg);
const char *shorten_keycode(uint16_t keycode);
void display_write_single_keycode(uint8_t layer, uint8_t row, uint8_t col, painter_font_handle_t font);
void display_write_all_keycodes(uint8_t layer, painter_font_handle_t font);
void display_write_layer_name(char *layer_name, painter_font_handle_t font, uint8_t h, uint8_t s, uint8_t v);

void display_init_kb(void);
bool display_init_user(void);
void display_task_kb(void);
bool display_task_user(void);

void keyboard_post_init_kb(void);
void housekeeping_task_kb(void);
void dynamic_keymap_user_keycode_changed(uint8_t layer, uint8_t key, uint16_t keycode);
