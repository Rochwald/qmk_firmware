// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// num of layers
#define LAYER_CYCLE_START 0 // first layer
#define LAYER_CYCLE_END   1 // last layer

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

// QP Configuration
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE
#define QUANTUM_PAINTER_SUPPORTS_NATIVE_COLORS TRUE
//#define ST7789_NO_AUTOMATIC_VIEWPORT_OFFSETS
#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0   // Display timeout configuration, default 30000 (30 sek). 0 = No timeout.

// Display backlight
#define BACKLIGHT_PWM_DRIVER PWMD5
#define BACKLIGHT_PWM_CHANNEL 2
//#define BACKLIGHT_PAL_MODE 2
#define DISPLAY_BACKLIGHT_TIMEOUT (QUANTUM_PAINTER_DISPLAY_TIMEOUT) // uncomment if LCD backlight timeout is also desired

// joystick settings for gamepad
#define JOYSTICK_BUTTON_COUNT 0     // joystick buttons report as normal keyboard keys
#define JOYSTICK_AXIS_COUNT 5   // 4+1
#define JOYSTICK_AXIS_RESOLUTION 10

// joystick settings for pointing device
//#define ANALOG_JOYSTICK_X_AXIS_PIN C4
//#define ANALOG_JOYSTICK_Y_AXIS_PIN C5

// I2C settings for trackpad
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PIN B6
//#define POINTING_DEVICE_DEBUG
#define POINTING_DEVICE_MOTION_PIN B1   // CHG pin
#define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#define POINTING_DEVICE_INVERT_X
#define POINTING_DEVICE_INVERT_Y

// trackpad settings
#define MXT_SENSOR_WIDTH_MM 72.2
#define MXT_SENSOR_HEIGHT_MM 53.2
#define MXT_MATRIX_X_SIZE 14
#define MXT_MATRIX_Y_SIZE 19
#define MAX_TOUCH_REPORTS 4
#define MXT_SCROLL_DIVISOR 16
#define MXT_TAP_TIME 100
#define MXT_TAP_AND_HOLD_TIME 500
#define MXT_TAP_AND_HOLD_DISTANCE 10
#define MXT_DEFAULT_DPI 400
#define MXT_TOUCH_THRESHOLD 18
#define MXT_GAIN 4
#define MXT_DX_GAIN 255
