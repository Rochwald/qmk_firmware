// Copyright 2025 Rok Hrovat (@Rochwald)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_MAX_POWER_CONSUMPTION 300

// num of layers
#define LAYER_CYCLE_START 0 // first layer
#define LAYER_CYCLE_END   4 // last layer

// macros
#define SENDSTRING_BELL
#define BELL_SOUND TERMINAL_SOUND

// rotary encoders
#define ENCODER_A_PINS {C11, C5}
#define ENCODER_B_PINS {C10, C4}
#define ENCODER_RESOLUTIONS {4, 4}

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

// RGB
// see RM0368
#define WS2812_DI_PIN B1
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 4
#define WS2812_PWM_PAL_MODE 2
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM2
#define WS2812_PWM_DMA_CHANNEL 5

#ifdef RGB_MATRIX_ENABLE
    #define RGB_MATRIX_LED_COUNT 16
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 80
    #define RGB_MATRIX_DEFAULT_ON false
    #define RGB_MATRIX_DEFAULT_HUE 0
    #define RGB_MATRIX_DEFAULT_SAT 255
    #define RGB_MATRIX_DEFAULT_VAL 80
    #define RGB_MATRIX_DEFAULT_SPD 255
    #define RGB_TRIGGER_ON_KEYDOWN
    //#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    //#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    #undef ENABLE_RGB_MATRIX_SOLID_COLOR
#endif

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LED_COUNT 9
    #define RGBLIGHT_LIMIT_VAL 80
    #define RGBLIGHT_DEFAULT_ON false
    #define RGBLIGHT_SLEEP
    #define RGBLIGHT_DEFAULT_HUE 0
    #define RGBLIGHT_DEFAULT_SAT 0
    #define RGBLIGHT_DEFAULT_VAL 0
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 10
    //#define RGBLIGHT_LAYERS
#endif