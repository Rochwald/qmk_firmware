GRAVE_ESC_ENABLE = no
MUSIC_ENABLE = no

KEYCODE_STRING_ENABLE = yes
SEND_STRING_ENABLE = yes

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_ST7789_SPI_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi

SRC += keyboard.c
SRC += graphics/logo_120x120.qgf.c
SRC += graphics/roboto_bold32.qff.c
SRC += graphics/roboto20.qff.c
SRC += graphics/roboto12.qff.c

BACKLIGHT_ENABLE = yes

WS2812_DRIVER = pwm

# uncomment one of two options:
# option 1: per key rgb
#RGB_MATRIX_ENABLE = yes
#RGB_MATRIX_DRIVER = ws2812

# option 2: underglow rgb
RGBLIGHT_ENABLE = yes
RGBLIGHT_DRIVER = ws2812
