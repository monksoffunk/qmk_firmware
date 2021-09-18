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

#pragma once

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LAYERS
#    define RGB_DI_PIN F0
#    define RGBLED_NUM 5
// current rev3 PCB has 5 underglow RGB LED only and so always RGBLED_NUM=5

#    define LAYER_RGBLED_START 0
#    define LAYER_RGBLED_NUM RGBLED_NUM

#    define RGBLIGHT_HUE_STEP 10
#    define RGBLIGHT_SAT_STEP 17
#    define RGBLIGHT_LIMIT_VAL 255
#endif

// NumLock LED pin F1 for SW1 LED, D4 for SW5
#ifndef LED_NLK
#    define LED_NLK F1
// #define LED_NLK D4
#    endif

#    ifdef BACKLIGHT_ENABLE
#        define BACKLIGHT_PIN LED_NLK
#        define BACKLIGHT_LEVELS 5   // The number of brightness levels (maximum 31 excluding off)
#        define BACKLIGHT_BREATHING  // Enable backlight breathing, if supported
#        define BREATHING_PERIOD 3   // The length of one backlight "breath" in seconds
#    endif
