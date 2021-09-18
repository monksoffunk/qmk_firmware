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

#include "attack25.h"
#include "common/promicro_LED.h"

#ifdef RGB_MATRIX_ENABLE
    #ifdef RGBLED_BOTH
        led_config_t g_led_config = { {
        // Key Matrix to LED Index
            { 0, 1, 2, 3, 4 },
            { 9, 8, 7, 6, 5 },
            { 10, 11, 12, 13, 14 },
            { 19, 18, 17, 16, 15 },
            { 20, 21, 22, 23, 24 },
        //    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
        }, {
        // LED Index to Physical Position
            {   0,   0 }, {  56,   0 }, { 112,   0 }, { 168,   0 }, { 224,   0 },
            { 224,  16 }, { 168,  16 }, { 112,  16 }, {  56,  16 }, {   0,  16 },
            {   0,  32 }, {  56,  32 }, { 112,  32 }, { 168,  32 }, { 224,  32 },
            { 224,  48 }, { 168,  48 }, { 112,  48 }, {  56,  48 }, {   0,  48 },
            {   0,  64 }, {  56,  64 }, { 112,  64 }, { 168,  64 }, { 224,  64 },
            {   0,   8 }, {   0,  60 }, { 112,  60 }, { 224,  60 }, { 224,   8 }
        }, {
        // LED Index to Flag
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            8, 8, 8, 8, 8
        } };
    #else
        led_config_t g_led_config = { {
        // Key Matrix to LED Index
            { 0, 1, 2, 3, 4 },
            { 9, 8, 7, 6, 5 },
            { 10, 11, 12, 13, 14 },
            { 19, 18, 17, 16, 15 },
            { 20, 21, 22, 23, 24 }
        }, {
        // LED Index to Physical Position
            {   0,   0 }, {  56,   0 }, { 112,   0 }, { 168,   0 }, { 224,   0 },
            { 224,  16 }, { 168,  16 }, { 112,  16 }, {  56,  16 }, {   0,  16 },
            {   0,  32 }, {  56,  32 }, { 112,  32 }, { 168,  32 }, { 224,  32 },
            { 224,  48 }, { 168,  48 }, { 112,  48 }, {  56,  48 }, {   0,  48 },
            {   0,  64 }, {  56,  64 }, { 112,  64 }, { 168,  64 }, { 224,  64 }
        }, {
        // LED Index to Flag
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4,
            4, 4, 4, 4, 4
    } };
    #endif
#endif

user_config_t user_config;

void eeconfig_init_kb(void) {
    user_config.raw      = 0;
    user_config.mac_mode = true;
    eeconfig_update_kb(user_config.raw);
    eeconfig_init_user();
}

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    extern RGB_CONFIG_t RGB_CONFIG;
    RGB_CONFIG_t RGB_current_config;
#endif

#ifdef RGBLIGHT_ENABLE
#    ifndef USER_CUSTOM_LIGHTING_LAYER
const rgblight_segment_t PROGMEM        _NUMOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _NUMOFF_HSV});
const rgblight_segment_t PROGMEM        _FN_layer[]     = RGBLIGHT_LAYER_SEGMENTS({LAYER_RGBLED_START, LAYER_RGBLED_NUM, _FN_HSV});
const rgblight_segment_t PROGMEM        _MAC_layer[]    = RGBLIGHT_LAYER_SEGMENTS({BLINK_RGBLED_START, BLINK_RGBLED_NUM, _MAC_HSV});
const rgblight_segment_t PROGMEM        _WIN_layer[]    = RGBLIGHT_LAYER_SEGMENTS({BLINK_RGBLED_START, BLINK_RGBLED_NUM, _WIN_HSV});
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
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_init();
    RGB_current_config = RGB_CONFIG;
#elif defined(RGBLIGHT_ENABLE)
    rgblight_init();
    RGB_current_config = RGB_CONFIG;
    rgblight_layers    = rgb_layers;
#endif
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
        TX_RX_LED_INIT; //Turn ProMicro LEDs off by default
        RXLED0;
        TXLED0;
#if defined(MODE_BLINK_ENABLE)
    blink_indicator(2 + !user_config.mac_mode, 2 + !user_config.mac_mode * 2);
#endif
        keyboard_post_init_user();
        debug_enable = true;
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
        case RGB_MOD:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_mode_noeeprom(RGB_current_config.mode);
                rgblight_step();
                RGB_current_config.mode = RGB_CONFIG.mode;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGB_RMOD:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_mode_noeeprom(RGB_current_config.mode);
                rgblight_step_reverse();
                RGB_current_config.mode = RGB_CONFIG.mode;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGBRST:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_config = RGB_CONFIG;
            }
#endif
            return false;
            break;
        case RGB_HUI:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_increase_hue();
                RGB_current_config_hue = RGB_CONFIG_hue;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGB_HUD:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_decrease_hue();
                RGB_current_config_hue = RGB_CONFIG_hue;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGB_SAI:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_increase_sat();
                RGB_current_config_sat = RGB_CONFIG_sat;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGB_SAD:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_decrease_sat();
                RGB_current_config_sat = RGB_CONFIG_sat;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGB_VAI:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_increase_val();
                RGB_current_config_val = RGB_CONFIG_val;
            }
            return false;
#else
            return true;
#endif
            break;
        case RGB_VAD:
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                rgblight_decrease_val();
                RGB_current_config_val = RGB_CONFIG_val;
            }
            return false;
#else
            return true;
#endif
            break;
        case P00:
            if (record->event.pressed) {
                tap_code(KC_P0);
                tap_code(KC_P0);
            }
            return false;
    }
    return process_record_user(keycode, record);
}

// for Windows Mode
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        if (!user_config.mac_mode) {
            if (led_state.num_lock && !IS_LAYER_ON(_NUMOFF)) {
                NumLock_Mode = true;
#ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(0, false);
#endif
#ifdef RGB_MATRIX_ENABLE
                rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
#endif
            } else {
                NumLock_Mode = false;
                // layer Lightning mode is _NUMOFF though _NUM layer in Windows Mode (NumLock LED off)
#ifdef RGBLIGHT_ENABLE
                rgblight_set_layer_state(0, true);
#endif
            }
#if defined(LED_NLK) && defined(BACKLIGHT_ENABLE)
            numlock_backlight(NumLock_Mode);
#endif
        }
    }
    return res;
}

#ifdef RGB_MATRIX_ENABLE
void rgb_matrix_indicators_kb(void) {
    uint8_t current_highest_layer = get_highest_layer(layer_state);
    if (!NumLock_Mode && current_highest_layer != _FN) {
        rgb_matrix_layer_helper(_NUMOFF_HSV, 1, rgb_matrix_config.speed, LAYER_LED_FLAG);
    }
    switch (current_highest_layer) {
        case _FN:
            rgb_matrix_layer_helper(_FN_HSV, 0, rgb_matrix_config.speed, LAYER_LED_FLAG);
            break;
        case _NUMOFF:

            rgb_matrix_layer_helper(_NUMOFF_HSV, 1, rgb_matrix_config.speed, LAYER_LED_FLAG);
            break;
        default:
            break;
    }
}
#elif RGBLIGHT_ENABLE
layer_state_t layer_state_set_kb(uint32_t state) {
    if (user_config.mac_mode) {
        rgblight_set_layer_state(0, layer_state_cmp(state | default_layer_state, _NUMOFF));
    }
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
    return layer_state_set_user(state);
}
#endif
