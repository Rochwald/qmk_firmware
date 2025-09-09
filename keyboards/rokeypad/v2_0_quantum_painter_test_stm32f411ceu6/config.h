// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Display settings
#define DISPLAY_DRIVER ST7789
#define LCD_WIDTH 240
#define LCD_HEIGHT 240
#define SPI_MODE 3
#define LCD_SPI_DIVISOR 4
#define LCD_WAIT_TIME 150
#define LCD_ROTATION QP_ROTATION_0
#define LCD_OFFSET_X 0
#define LCD_OFFSET_Y 0
//#define LCD_INVERT_COLOR

// SPI pins (for display)
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
//#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
//#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6 // Unused (can be NO_PIN)
//#define SPI_MISO_PAL_MODE 5
#define LCD_RST_PIN A3 // can be NO_PIN
#define LCD_DC_PIN A2
#define LCD_CS_PIN A4

// Display backlight
#define BACKLIGHT_PIN A1
#define BACKLIGHT_LEVELS 8
#define BACKLIGHT_PWM_DRIVER PWMD5
#define BACKLIGHT_PWM_CHANNEL 2
//#define BACKLIGHT_PAL_MODE 2

// QP Configuration
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
//#define ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS

// Display timeout configuration, default 30000 (30 sek). 0 = No timeout.
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
