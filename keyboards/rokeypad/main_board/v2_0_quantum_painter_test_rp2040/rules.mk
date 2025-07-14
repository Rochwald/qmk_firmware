QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_ST7789_SPI_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7789_spi

SRC += gfx/converted/Mario_240x240.qgf.c
SRC += gfx/converted/Black_Copper_240x240.qgf.c
SRC += gfx/converted/test_gif.qgf.c

BACKLIGHT_ENABLE = yes
BACKLIGHT_DRIVER = pwm
