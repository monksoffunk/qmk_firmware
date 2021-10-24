# Build Options
# If you need, add below.

MCU = atmega32u2
BOOTLOADER = atmel-dfu

OPT_DEF += -SMD
SRC += ../common/led_func.c
LTO_ENABLE = yes
