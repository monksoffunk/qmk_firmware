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
#include "rev32.h"
#include "print.h"

user_config_t user_config;

void eeconfig_init_kb(void) {
    user_config.raw      = 0;
    user_config.mac_mode = true;
    eeconfig_update_kb(user_config.raw);
    eeconfig_init_user();
}

#ifdef ENCODER_ENABLE
uint8_t encoder_lock_layer = 0;
#endif

#ifdef RGBLIGHT_ENABLE
extern RGB_CONFIG_t RGB_CONFIG;
RGB_CONFIG_t        RGB_current_config;

#    ifndef USER_CUSTOM_LIGHTING_LAYER
const rgblight_segment_t PROGMEM        _NUMOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _NUMOFF_HSV});
const rgblight_segment_t PROGMEM        _FN_layer[]     = RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _FN_HSV});
const rgblight_segment_t PROGMEM        _MAC_layer[]    = RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _MAC_HSV});
const rgblight_segment_t PROGMEM        _WIN_layer[]    = RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _WIN_HSV});
const rgblight_segment_t* const PROGMEM rgb_layers[]    = RGBLIGHT_LAYERS_LIST(_NUMOFF_layer, _FN_layer, _MAC_layer, _WIN_layer);
#    endif
#endif

bool            NumLock_Mode      = true;
bool            NumLock_init_done = false;
static uint16_t numcheck_timer;

void keyboard_pre_init_kb(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();
    numcheck_timer  = timer_read();
#if defined(RGBLIGHT_ENABLE)
    rgblight_init();
    RGB_current_config = RGB_CONFIG;
    rgblight_layers    = rgb_layers;
#endif
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
#if defined(MODE_BLINK_ENABLE)
    blink_indicator(2 + !user_config.mac_mode, 2 + !user_config.mac_mode * 2);
#endif
    debug_enable = true;
    keyboard_post_init_user();
    }

void matrix_scan_kb(void) {
    if (user_config.mac_mode) {
        if (!NumLock_init_done) {
            if (timer_elapsed(numcheck_timer) > 500) {
                if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) {
                    tap_code16(KC_NLCK);
                }
                NumLock_init_done = true;
            }
        } else {
#if defined(LED_NLK) && defined(BACKLIGHT_ENABLE)
            numlock_backlight(NumLock_Mode);
#endif
        }
    }
    matrix_scan_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case WINMAC:
            if (record->event.pressed) {
                user_config.mac_mode = !user_config.mac_mode;
                eeconfig_update_user(user_config.raw);
#if defined(MODE_BLINK_ENABLE)
                blink_indicator(2 + !user_config.mac_mode, 2 + !user_config.mac_mode * 2);
#endif
                if (user_config.mac_mode && !NumLock_Mode) {
                    tap_code16(KC_NLCK);
                    layer_on(_NUMOFF);
                    default_layer_or(1UL << _NUMOFF);
                } else if (!user_config.mac_mode && !NumLock_Mode) {
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
                    NumLock_Mode = !NumLock_Mode;
                    if (NumLock_Mode) {
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
#ifdef ENCODER_ENABLE
        case EN_RST:
            encoder_lock_layer = 0;
            return false;
        case EN_FN:
            encoder_lock_layer = _FN;
            return false;
        case EN_RGB:
            encoder_lock_layer = _RGB;
            return false;
        case EN_BLED:
            encoder_lock_layer = _BLED;
            return false;
        case EN_SP:
            encoder_lock_layer = _SP;
            return false;
#endif
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            dprint("RGBRST\n");
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
#endif
            return false;
        case P00:
            if (record->event.pressed) {
                tap_code(KC_P0);
                tap_code(KC_P0);
            }
            return false;
    }
    return process_record_user(keycode, record);
}

#ifdef RGBLIGHT_ENABLE
layer_state_t layer_state_set_kb(uint32_t state) {
    dprintf("layer_state %08lX(%u)\n", layer_state, get_highest_layer(layer_state));
    dprintf("default_layer_state %08lX(%u)\n", default_layer_state, get_highest_layer(default_layer_state));

    if (user_config.mac_mode) {
        rgblight_set_layer_state(0, layer_state_cmp(state | default_layer_state, _NUMOFF));
    }
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    return layer_state_set_user(state);
}
#endif

// for Windows
void led_set_kb(uint8_t usb_led) {
    if (!user_config.mac_mode) {
        if ((usb_led & (1 << USB_LED_NUM_LOCK)) && !IS_LAYER_ON(_NUMOFF)) {
            NumLock_Mode = true;
#ifdef RGBLIGHT_ENABLE
            // turn _NUMOFF layer light off when NumLock in Windows Mode
            rgblight_set_layer_state(0, false);
#endif
        } else {
            NumLock_Mode = false;
#ifdef RGBLIGHT_ENABLE
            // layer Lightning mode is _NUMOFF though _NUM layer in Windows Mode (NumLock LED off)
            rgblight_set_layer_state(0, true);
#endif
        }
#if defined(LED_NLK) && defined(BACKLIGHT_ENABLE)
        numlock_backlight(NumLock_Mode);
#endif
    }
    led_set_user(usb_led);
}

#ifdef ENCODER_ENABLE
bool encoder_update_kb(uint8_t index, bool clockwise) {
    keypos_t key;
    bool     encoder_layer_locked = false;

    if (index == 0) {
        if (clockwise) {
            key.row = 5;
            key.col = 1;
        } else {
            key.row = 5;
            key.col = 0;
        }
        if (get_highest_layer(layer_state) < _FN) {
        layer_on(encoder_lock_layer);
        encoder_layer_locked = true;
        }
        action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
        action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
        if (encoder_layer_locked) {
            layer_off(encoder_lock_layer);
        }
    }
    return true;
}
#endif
