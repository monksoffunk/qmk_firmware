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
#include "rev3.h"
#include "print.h"
#ifndef USER_FULL_CUSTOM

user_config_t user_config;
void          numlock_state_check(void);

void eeconfig_init_kb(void) {
    user_config.raw                = 0;
    user_config.mac_mode           = true;
    user_config.encoder_resolution = ENCODER_RESOLUTION;
    eeconfig_update_kb(user_config.raw);
    eeconfig_init_user();
}

#    ifdef ENCODER_ENABLE
static uint8_t encoder_lock_layer[ENCODERS] = {0};
#    endif

#    ifdef RGBLIGHT_ENABLE
extern RGB_CONFIG_t RGB_CONFIG;
RGB_CONFIG_t        RGB_current_config;

#        ifndef USER_CUSTOM_LIGHTING_LAYER
const rgblight_segment_t PROGMEM _NUMOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_RGBLED_START, LAYER_RGBLED_NUM, _NUMOFF_HSV});
const rgblight_segment_t PROGMEM _FN_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _FN_HSV});
const rgblight_segment_t PROGMEM _MAC_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _MAC_HSV});
const rgblight_segment_t PROGMEM _WIN_layer[] =
    RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _WIN_HSV});
const rgblight_segment_t* const PROGMEM rgb_layers[] =
    RGBLIGHT_LAYERS_LIST(_NUMOFF_layer, _FN_layer, _MAC_layer, _WIN_layer);
#        endif
#    endif

bool            numlock_mode      = true;
bool            numlock_init_done = false;
static uint16_t numcheck_timer;

void keyboard_pre_init_kb(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    if ((user_config.encoder_resolution == 0) ||
        (user_config.encoder_resolution > 4)) {
        user_config.encoder_resolution = 4;
        eeconfig_update_user(user_config.raw);
    }
    encoder_set_resolution(0, user_config.encoder_resolution);
    numcheck_timer = timer_read();
#    if defined(RGBLIGHT_ENABLE)
    rgblight_init();
    RGB_current_config = RGB_CONFIG;
    rgblight_layers    = rgb_layers;
#    endif
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
#    if defined(MODE_BLINK_ENABLE)
    blink_indicator(2 + !user_config.mac_mode, 2 + !user_config.mac_mode * 2);
#    endif
        debug_enable = true;
    keyboard_post_init_user();
}

void matrix_scan_kb(void) {
    if (user_config.mac_mode) {
        if (!numlock_init_done) {
            if (timer_elapsed(numcheck_timer) > 500) {
                if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
                    tap_code16(KC_NLCK);
                }
                numlock_init_done = true;
            }
        } else {
#    if defined(LED_NLK) && defined(BACKLIGHT_ENABLE)
            numlock_backlight(numlock_mode);
#    endif
        }
    }
#    if defined(ENCODER_ENABLE)
    encoder_action_unregister(encoder_lock_layer);
#    endif

    numlock_state_check();
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case WINMAC:
            if (record->event.pressed) {
                user_config.mac_mode = !user_config.mac_mode;
                eeconfig_update_user(user_config.raw);
#    if defined(MODE_BLINK_ENABLE)
                blink_indicator(2 + !user_config.mac_mode,
                                2 + !user_config.mac_mode * 2);
#    endif
                if (user_config.mac_mode && !numlock_mode) {
                    tap_code16(KC_NLCK);
                    layer_on(_NUMOFF);
                    default_layer_or(1UL << _NUMOFF);
                } else if (!user_config.mac_mode && !numlock_mode) {
                    tap_code16(KC_NLCK);
                    layer_clear();
                    default_layer_xor(1UL << _NUMOFF);
                }
            }
            return false;
            break;
        case KC_NLCK:
            if (record->event.pressed) {
                if (user_config.mac_mode) {
                    numlock_mode = !numlock_mode;
                    if (numlock_mode) {
                        layer_off(_NUMOFF);
                        default_layer_xor(1UL << _NUMOFF);
                        layer_state_set_kb(layer_state);
                    } else {
                        layer_on(_NUMOFF);
                        default_layer_or(1UL << _NUMOFF);
                    }
                    return false;
                } else {
                    return true;  // Win
                }
            } else {
                if (user_config.mac_mode) {
                    return false;
                } else {
                    return true;
                }
            }
            break;
#    ifdef ENCODER_ENABLE
        case EN_RST ... EN_SP:
            if (record->event.pressed) {
                if (encoder_lock_layer[0] != keycode - EN_RST) {
                    encoder_lock_layer[0] = keycode - EN_RST;
                } else {
                    encoder_lock_layer[0] = 0;
                }
            }
            return false;
#    endif
        case RGBRST:
#    ifdef RGBLIGHT_ENABLE
            dprint("RGBRST\n");
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
#    endif
            return false;
        case P00:
            if (record->event.pressed) {
                tap_code(KC_P0);
                tap_code(KC_P0);
            }
            return false;

        case CH_ENCR:
            if (record->event.pressed) {
            } else {
                user_config.encoder_resolution =
                    (user_config.encoder_resolution << 1) & 7;
                if (user_config.encoder_resolution == 0) {
                    user_config.encoder_resolution = 1;
                }
                encoder_set_resolution(0, user_config.encoder_resolution);
                eeconfig_update_user(user_config.raw);
            }
            return false;
    }
    return process_record_user(keycode, record);
}

// for Windows Mode
void numlock_state_check(void) {
    led_t led_state = host_keyboard_led_state();
    if (!user_config.mac_mode) {
        numlock_mode = (led_state.num_lock && !IS_LAYER_ON(_NUMOFF));
#    ifdef RGBLIGHT_ENABLE
        // RGBLIGHT_LAYERS_LIST 0 is for _NUMOFF layer.
        // when numlock_mode false, _NUMOFF RGBLIGHT is on.
        // layer Lightning mode is _NUMOFF though _NUM layer in Windows Mode
        // (numlcok LED off)
        rgblight_set_layer_state(0, !numlock_mode);
#    elif defined(RGB_MATRIX_ENABLE)
        if (numlock_mode) {
            rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h,
                                       RGB_current_config.hsv.s,
                                       RGB_current_config.hsv.v);
        }
#    endif
#    if defined(LED_NLK) && defined(BACKLIGHT_ENABLE)
        numlock_backlight(numlock_mode);
#    endif
    }
    return;
}

#    ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_kb(layer_state_t state) {
    if (user_config.mac_mode) {
        rgblight_set_layer_state(
            0, layer_state_cmp(state | default_layer_state, _NUMOFF));
    }
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    return layer_state_set_user(state);
}
#    endif

#    ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise, encoder_lock_layer);
#        ifdef ENCODER_DETECT_OVER_SPEED
    int enc_over = get_encoder_over_count();
    for (; enc_over > 0; enc_over--) {
        tap_code(KC_MINUS);
    }
#        endif
    return encoder_update_user(index, clockwise);
}
#    endif
#endif
