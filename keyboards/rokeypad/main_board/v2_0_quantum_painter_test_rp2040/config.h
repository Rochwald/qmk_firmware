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
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN NO_PIN // Unused
#define LCD_RST_PIN NO_PIN
#define LCD_DC_PIN GP12
#define LCD_CS_PIN GP13

// Display backlight
#define BACKLIGHT_PIN GP22
#define BACKLIGHT_LEVELS 8
#define BACKLIGHT_PWM_DRIVER PWMD3
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A

// QP Configuration
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
//#define ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS

// Display timeout configuration, default 30000 (30 sek). 0 = No timeout.
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0
