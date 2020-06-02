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
#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0xA109
#define DEVICE_VER 0x0002
#define MANUFACTURER monksoffunk
#define PRODUCT Attack25
#define DESCRIPTION 5x5 Keyboard Pad

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 5

/* key matrix pins */
#define MATRIX_ROW_PINS { B4, B5, B6, B2, B3 }
#define MATRIX_COL_PINS { D4, C6, D7, F5, F6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* prevent stuck modifiers */
#define PREVENT_STUCK_MODIFIERS

#define RGB_DI_PIN D3

#ifdef RGB_MATRIX_ENABLE
    #ifdef RGBLED_BOTH
        #define RGBLED_NUM 30
    #else
        #define RGBLED_NUM 25
    #endif
    #define DRIVER_LED_TOTAL RGBLED_NUM
#endif

#ifdef RGBLIGHT_ENABLE
    #ifdef RGBLED_BOTH
        #define RGBLED_NUM 30
    #else
        #ifdef RGBLED_BACK
            #define RGBLED_NUM 25
        #else
            #ifdef RGBLED_1LED
                #define RGBLED_NUM 1
            #else
                #define RGBLED_NUM 5
            #endif
        #endif
    #endif
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
#endif

#ifndef IOS_DEVICE_ENABLE
    #if RGBLED_NUM <= 6
        #define RGBLIGHT_LIMIT_VAL 255
        #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
    #else
        #if RGBLED_NUM <= 30
            #define RGBLIGHT_LIMIT_VAL 130
            #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
        #else
            #define RGBLIGHT_LIMIT_VAL 120
            #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
        #endif
    #endif
    #define RGBLIGHT_VAL_STEP 17
#else
    #if RGBLED_NUM <= 6
        #define RGBLIGHT_LIMIT_VAL 180
    #else
        #if RGBLED_NUM <= 30
            #define RGBLIGHT_LIMIT_VAL 90
        #else
            #define RGBLIGHT_LIMIT_VAL 35
        #endif
    #endif
    #define RGBLIGHT_VAL_STEP 4
#endif

#if (defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)) && !defined(IOS_DEVICE_ENABLE)
// USB_MAX_POWER_CONSUMPTION value
//  120  RGBoff
//  330  RGB 6
//  300  RGB 32
#    define USB_MAX_POWER_CONSUMPTION 400
#else
// fix iPhone and iPad power adapter issue
// iOS device need lessthan 100
    #define USB_MAX_POWER_CONSUMPTION 100
#endif
//#endif
