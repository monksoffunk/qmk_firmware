/* Copyright 2020 monksoffunk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef RGB_MATRIX_ENABLE
    #ifdef RGBLED_BOTH
        #define RGBLED_NUM 30
    #else
        #define RGBLED_NUM 25
    #endif
    #define DRIVER_LED_TOTAL RGBLED_NUM
#endif

#ifndef CUSTOM_RGBLED_NUM
#    ifdef RGBLIGHT_ENABLE
#        define RGBLIGHT_LAYERS
#        ifdef RGBLED_BOTH
#            define RGBLED_NUM 30
#            define LAYER_RGBLED_START 25
#            define LAYER_RGBLED_NUM 5
#            define BLINK_RGBLED_START 0
#            define BLINK_RGBLED_NUM 30
#        else
#            ifdef RGBLED_BACK
#                define RGBLED_NUM 25
#                define LAYER_RGBLED_START 0
#                define LAYER_RGBLED_NUM 25
#                define BLINK_RGBLED_START 0
#                define BLINK_RGBLED_NUM 25
#            else
#                ifdef RGBLED_1LED
#                    define RGBLED_NUM 1
#                    define LAYER_RGBLED_START 0
#                    define LAYER_RGBLED_NUM 1
#                    define BLINK_RGBLED_START 0
#                    define BLINK_RGBLED_NUM 1
#                else  // for only underglow LED
#                    define RGBLED_NUM 5
#                    define LAYER_RGBLED_START 0
#                    define LAYER_RGBLED_NUM 5
#                    define BLINK_RGBLED_START 0
#                    define BLINK_RGBLED_NUM 5
#                endif
#            endif
#        endif
#        define RGBLIGHT_HUE_STEP 10
#        define RGBLIGHT_SAT_STEP 17
#    endif
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
    #define RGB_MATRIX_STARTUP_VAL 100
#else
    #if RGBLED_NUM <= 6
        #define RGBLIGHT_LIMIT_VAL 180
        #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
    #else
        #if RGBLED_NUM <= 30
            #define RGBLIGHT_LIMIT_VAL 90
            #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120
        #else
            #define RGBLIGHT_LIMIT_VAL 35
            #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
        #endif
    #endif
    #define RGBLIGHT_VAL_STEP 4
    #define RGB_MATRIX_STARTUP_VAL 100
#endif

#ifndef LAYER_LED_FLAG
#    ifdef RGBLED_BOTH
#        define LAYER_LED_FLAG LED_FLAG_INDICATOR
#    else
#        define LAYER_LED_FLAG LED_FLAG_NONE
#    endif
#endif

#ifndef BLINK_LED_FLAG
#        define BLINK_LED_FLAG LED_FLAG_NONE
#endif
