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

#ifdef MATRIX_ROWS
#undef MATRIX_ROWS
#undef MATRIX_COLS
#undef DIRECT_PINS
/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 10

// four F0 : dummies for encoder
#define DIRECT_PINS {{ B4, F6, F5, F4, B5, F7, F0, F0, F0, F0 }}

#endif

// uncomment some animations for reducing firmware size
#ifdef RGBLIGHT_ANIMATIONS
#    undef RGBLIGHT_ANIMATIONS
#endif

#define RGBLIGHT_ANIMATION_SELECT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
// #define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
// #define RGBLIGHT_EFFECT_RGB_TEST
// #define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

#undef LAYOUT
#define LAYOUT( \
    k06, k07, k08, k09,\
        k10,  k11,   \
    k00, k01, k02, k03\
) \
{ \
    { k00, k01, k02, k03, k10, k11, k06, k07, k08, k09 }, \
}

#define ENCODER0_CCW_KEY_ROW 0
#define ENCODER0_CCW_KEY_COL 6
#define ENCODER0_CW_KEY_ROW 0
#define ENCODER0_CW_KEY_COL 7
#define ENCODER1_CCW_KEY_ROW 0
#define ENCODER1_CCW_KEY_COL 8
#define ENCODER1_CW_KEY_ROW 0
#define ENCODER1_CW_KEY_COL 9
#define MODECONTROL_ENABLE

#undef ENCODER_RESOLUTION
#define ENCODER_RESOLUTION 2

#define OLED_TIMEOUT 300000
//  #define OLED_SCROLL_TIMEOUT 60000

#define MOUSEKEY_INTERVAL 16
