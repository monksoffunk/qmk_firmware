/*
Copyright 2019 monksoffunk

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

#ifdef OLED_ENABLE
  #define OLED_TIMEOUT 300000
  #define OLED_SCROLL_TIMEOUT 60000
#endif

#ifdef RGB_DI_PIN
#    define RGBLIGHT_HUE_STEP 8
#    define RGBLIGHT_SAT_STEP 8
#    define RGBLIGHT_VAL_STEP 8
#    define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
#    define RGBLIGHT_SLEEP         /* If defined, the RGB lighting will be switched off when the host goes to sleep */
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define MOUSEKEY_INTERVAL 16

#define DYNAMIC_KEYMAP_LAYER_COUNT 11

// #define DISABLE_KB_FUNCTIONS /* disable all functions in cassette42.c */
// #define CUSTOM_LAYER_NUMBER  /* use your own layer number enum */
