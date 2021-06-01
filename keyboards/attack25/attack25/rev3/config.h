/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xEACB
#define DEVICE_VER      0x0003
#define MANUFACTURER    monksoffunk
#define PRODUCT         Attack25 rev3
#define DESCRIPTION     5x5 Keyboard Pad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { B0, B7, B6, B5, B4 }
#define MATRIX_COL_PINS { F5, F6, D2, D1, D0 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D5 }

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_LAYERS
    #define RGB_DI_PIN F0
    #define RGBLED_NUM 5
    // current rev3 PCB has 5 underglow RGB LED only and so always RGBLED_NUM=5

    #define LAYER_RGBLED_START 0
    #define LAYER_RGBLED_NUM RGBLED_NUM

    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_LIMIT_VAL 255

    #if defined(RGBLIGHT_ENABLE) && !defined(IOS_DEVICE_ENABLE)
    // USB_MAX_POWER_CONSUMPTION value
    //  120  RGBoff
    //  330  RGB 6
    //  300  RGB 32
        #define USB_MAX_POWER_CONSUMPTION 400
    #else
        // fix iPhone and iPad power adapter issue
        // iOS device need lessthan 100
        #define USB_MAX_POWER_CONSUMPTION 100
    #endif
#endif

// NumLock LED pins F1 for SW1 LED, D4 for SW5
#define LED_NLK F1  
// #define LED_NLK D4 
#ifdef LED_NLK
    #define BACKLIGHT_PIN LED_NLK
    #define BACKLIGHT_LEVELS 5    // The number of brightness levels (maximum 31 excluding off)
    #define BACKLIGHT_BREATHING   // Enable backlight breathing, if supported
    #define BREATHING_PERIOD 3    // The length of one backlight "breath" in seconds
#endif

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 1 // Custom config starts after VIA's EEPROM usage

