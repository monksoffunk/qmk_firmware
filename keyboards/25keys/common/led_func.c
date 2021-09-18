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

#include QMK_KEYBOARD_H
#include "led_func.h"
#include "rgb_matrix_layer.h"
#ifdef BACKLIGHT_ENABLE
	#include "backlight.h"
#endif

extern void rgb_matrix_update_pwm_buffers(void);

#ifndef BLINK_DURATION
#   define BLINK_DURATION 500
#endif

#ifndef USER_CUSTOM_LIGHTING_LAYER
#    ifdef RGB_MATRIX_ENABLE
const HSV rgb_matrix_layers[] PROGMEM = {
    {_NUMOFF_HSV},
    {_FN_HSV},
    {_MAC_HSV},
    {_WIN_HSV}
};
#    endif
#endif

void blink_indicator(uint8_t blink_rgb_layer, uint8_t blink_num) {
#ifdef RGBLIGHT_ENABLE
    extern RGB_CONFIG_t RGB_CONFIG;
    RGB_CONFIG_t        RGB_current_config = RGB_CONFIG;
#endif
#ifdef BACKLIGHT_ENABLE
    breathing_disable();
#endif
    for(uint8_t i = 0 ; i < blink_num ; i++) {
#ifdef RGBLIGHT_ENABLE
        rgblight_mode_noeeprom(0);
        rgblight_set_layer_state(blink_rgb_layer, true);
        rgblight_enable_noeeprom();
#elif defined(RGB_MATRIX_ENABLE)
        rgb_matrix_layer_helper(pgm_read_byte(&rgb_matrix_layers[blink_rgb_layer].h), pgm_read_byte(&rgb_matrix_layers[blink_rgb_layer].s),pgm_read_byte(&rgb_matrix_layers[blink_rgb_layer].v), 0, rgb_matrix_config.speed, BLINK_LED_FLAG);
        rgb_matrix_update_pwm_buffers();
#endif
#ifdef BACKLIGHT_ENABLE
        backlight_level_noeeprom(BACKLIGHT_LEVELS);
#endif
        wait_ms(BLINK_DURATION);
#ifdef RGBLIGHT_ENABLE
        rgblight_disable_noeeprom();
#elif defined(RGB_MATRIX_ENABLE)
        rgb_matrix_turnoff(BLINK_LED_FLAG);
        rgb_matrix_update_pwm_buffers();
#endif
#ifdef BACKLIGHT_ENABLE
        backlight_level_noeeprom(0);
#endif
        wait_ms(BLINK_DURATION);
    }
#ifdef RGBLIGHT_ENABLE
    rgblight_set_layer_state(blink_rgb_layer, false);
    rgb_sethsv_noeeprom(RGB_current_config_hue, RGB_current_config_sat, RGB_current_config_val);
    if (RGB_current_config.enable) {
        rgblight_enable_noeeprom();
    } else {
        rgblight_disable_noeeprom();
    }
    rgblight_mode_noeeprom(RGB_current_config.mode);
#elif defined(RGB_MATRIX_ENABLE)
    rgb_matrix_enable_noeeprom();
#endif
#ifdef BACKLIGHT_ENABLE
    backlight_config_t backlight_eeprom_config;
    backlight_eeprom_config.raw = eeconfig_read_backlight();
    backlight_level_noeeprom(backlight_eeprom_config.level);
#endif
}

#ifdef BACKLIGHT_ENABLE
void numlock_backlight(bool NumLock_Mode) {
    backlight_config_t backlight_eeprom_config;
    backlight_eeprom_config.raw = eeconfig_read_backlight();
    if (NumLock_Mode && !is_backlight_enabled()) {
        backlight_level_noeeprom(backlight_eeprom_config.level);
    } else if (!NumLock_Mode && is_backlight_enabled()) {
        backlight_level_noeeprom(0);
    }
}
#endif
