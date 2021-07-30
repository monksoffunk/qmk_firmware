# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = lite     # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
MIDI_ENABLE = no            # MIDI controls
UNICODE_ENABLE = no         # Unicode
RGBLIGHT_ENABLE = yes       # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
RGB_MATRIX_ENABLE = no

define ATTACK25_CUSTOMISE_MSG
  	$(info Attack25 customize)
  	$(info -  LED_BACK=$(LED_BACK_ENABLE))
  	$(info -  LED_UNDERGLOW=$(LED_UNDERGLOW_ENABLE))
  	$(info -  LED_BOTH=$(LED_BOTH_ENABLE))
  	$(info -  LED_1LED=$(LED_1LED_ENABLE))
    $(info -  RGBMATRIX=$(RGB_MATRIX))
  	$(info -  LEDANIMATION=$(LED_ANIMATIONS))
  	$(info -  IOS_DEVICE=$(IOS_DEVICE_ENABLE))
endef

# Attack25 keyboard customize
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB backlight)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight)
LED_BOTH_ENABLE = no        # LED backlight and underglow
LED_1LED_ENABLE = no        # LED 1LED (Enable WS2812 RGB light)
RGB_MATRIX = no             # RGB LED Matrix
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

ifneq ($(strip $(ATTACK25)),)
  	ifeq ($(findstring back,$(ATTACK25)), back)
    	LED_BACK_ENABLE = yes
		LED_BOTH_ENABLE = no
  	endif
  	ifeq ($(findstring under,$(ATTACK25)), under)
    	LED_UNDERGLOW_ENABLE = yes
		LED_BOTH_ENABLE = no
  	endif
	ifeq ($(findstring 1led,$(ATTACK25)), 1led)
    	LED_1LED_ENABLE = yes
		LED_BOTH_ENABLE = no
  	endif
	ifeq ($(findstring both,$(ATTACK25)), both)
    	LED_BOTH_ENABLE = yes
  	endif
	ifeq ($(findstring matrix,$(ATTACK25)), matrix)
    	RGB_MATRIX = yes
    endif
  	ifeq ($(findstring na,$(ATTACK25)), na)
    	LED_ANIMATIONS = no
  	endif
  	ifeq ($(findstring ios,$(ATTACK25)), ios)
    	IOS_DEVICE_ENABLE = yes
  	endif
  	# $(eval $(call ATTACK25_CUSTOMISE_MSG))
  	# $(info )
endif

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  	RGBLIGHT_ENABLE = yes
  	OPT_DEFS += -DRGBLED_BACK
  	ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
     	OPT_DEFS += -DRGBLED_BOTH
    	$(info both LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE)
  	endif
else ifeq ($(strip $(LED_UNDERGLOW_ENABLE)), yes)
    RGBLIGHT_ENABLE = yes
else ifeq ($(strip $(LED_BOTH_ENABLE)), yes)
    RGBLIGHT_ENABLE = yes
    OPT_DEFS += -DRGBLED_BOTH
else ifeq ($(strip $(LED_1LED_ENABLE)), yes)
    RGBLIGHT_ENABLE = yes
    OPT_DEFS += -DRGBLED_1LED
else
  	RGBLIGHT_ENABLE = no
endif

ifeq ($(strip $(RGB_MATRIX)), yes)
  RGBLIGHT_ENABLE = no
  RGB_MATRIX_ENABLE = yes
  RGB_MATRIX_DRIVER = WS2812
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DRGBLIGHT_ANIMATIONS
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
SRC += ../common/led_func.c
LTO_ENABLE = yes

ifeq ($(findstring matrix,$(ATTACK25)), matrix)
 	SRC += ../common/rgb_matrix_layer.c
endif
