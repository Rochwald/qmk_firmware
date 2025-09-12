#CONSOLE_ENABLE = yes

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
SRC += graphics/roboto16.qff.c
SRC += maxtouch.c

BACKLIGHT_ENABLE = yes

I2C_DRIVER_REQUIRED = yes
POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = custom

JOYSTICK_ENABLE = yes
JOYSTICK_DRIVER = analog