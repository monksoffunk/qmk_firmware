
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = yes       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
# BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing

define ATTACK25_CUSTOMISE_MSG
  	$(info Attack25 customize)
  	$(info -  LED_BACK_ENABLE=$(LED_BACK_ENABLE))
  	$(info -  LED_UNDERGLOW_ENABLE=$(LED_UNDERGLOW_ENABLE))
  	$(info -  LED_BOTH_ENABLE=$(LED_BOTH_ENABLE))
  	$(info -  LED_1LED_ENABLE=$(LED_1LED_ENABLE))
    $(info -  RGB_MATRIX=$(RGB_MATRIX))
  	$(info -  LED_ANIMATION=$(LED_ANIMATIONS))
  	$(info -  IOS_DEVICE_ENABLE=$(IOS_DEVICE_ENABLE))
endef

# Attack25 keyboard customize
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB backlight)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight)
LED_BOTH_ENABLE = no        # LED backlight and underglow
LED_1LED_ENABLE = no        # LED 1LED (Enable WS2812 RGB light)
RGB_MATRIX = no             # RGB LED Matrix
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
Link_Time_Optimization = no # if firmware size over limit, try this option
####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

### Attack25 keyboard 'default' keymap: convenient command line option
##    make ATTACK25=<options> attack25:defualt
##    option= back | under | both | 1led | matrix | na | ios
##    ex.
##      make ATTACK25=under    attack25:defualt
##      make ATTACK25=under,ios attack25:defualt
##      make ATTACK25=back     attack25:default
##      make ATTACK25=back,na  attack25:default
##      make ATTACK25=back,ios attack25:default
##      make ATTACK25=1led     attack25:default


ifneq ($(strip $(ATTACK25)),)
  	ifeq ($(findstring back,$(ATTACK25)), back)
    	LED_BACK_ENABLE =  yes
  	endif
  	ifeq ($(findstring under,$(ATTACK25)), under)
    	LED_UNDERGLOW_ENABLE = yes
  	endif
  	ifeq ($(findstring both,$(ATTACK25)), both)
    	LED_BOTH_ENABLE = yes
  	endif
  	ifeq ($(findstring 1led,$(ATTACK25)), 1led)
    	LED_1LED_ENABLE = yes
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
  	$(eval $(call ATTACK25_CUSTOMISE_MSG))
  	$(info )
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
  RGB_MATRIX_ENABLE = WS2812
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DRGBLIGHT_ANIMATIONS
endif

ifeq ($(strip $(Link_Time_Optimization)),yes)
    EXTRAFLAGS += -flto -DUSE_Link_Time_Optimization
endif

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif

# Uncomment these for debugging
# $(info -- RGBLIGHT_ENABLE=$(RGBLIGHT_ENABLE))
# $(info -- OPT_DEFS=$(OPT_DEFS))
# $(info )
