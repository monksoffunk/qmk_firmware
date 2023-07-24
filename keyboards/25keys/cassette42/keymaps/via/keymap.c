/* Copyright 2019 monksoffunk
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

#include "common/oled_helper.h"
#define OLED_LOGO_TOGGLE_INTERVAL   500
#define OLED_INFOMATION_TERM        2000
#define MODECON_HOLD_TERM           200
#define OLED_UPDATE_INTERVAL        10

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    RGBRST = SAFE_RANGE,
    WRTROM,
    RGBNHUI,
    RGBNHUD,
    RGBNSAI,
    RGBNSAD,
    RGBNVAI,
    RGBNVAD,
    RGBNMOD,
    RGBNRMD,
    ENCPST0,
    ENCPST1,
    ENCPST2,
    ENCPST3,
    MODECON,
};

enum layer_number {
    _AUDIO = 0,
    _RGB,
    _FN0,
    _FN1,
    _FN2,
    _FN3,
    _HUE,
    _SAT,
    _VAL,
    _MODE,
};

uint8_t  current_layer  = _AUDIO;
uint8_t  mode_layer     = _AUDIO;
bool     modecon_enable = false;
bool     write_rom      = false;
uint16_t key_timer;
uint16_t sleep_counter;
uint32_t oled_timer;
bool     is_oled_sleep = false;
void     render_status(void);

#ifdef ENCODER_ENABLE
uint8_t encoder_lock_layer = 0;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // LAYOUT(LeftEncoder, RightEncoder, LeftSwitch, CenterLeftSwitch, CenterRightSwitch, RightSwitch)
    [_AUDIO] = LAYOUT(KC_VOLD, KC_VOLU, KC_DOWN, KC_UP,   MODECON, KC_ENT,  LT(_FN0, KC_MPRV), LT(_FN1, KC_MPLY), LT(_FN2, KC_MNXT), LT(_FN3, KC_SPC)),
    [_RGB]   = LAYOUT(_______, _______, _______, _______, MODECON, _______, LT(_HUE, KC_MPRV), LT(_SAT, KC_MPLY), LT(_VAL, KC_MNXT), LT(_MODE, KC_SPC)),
    [_FN0]   = LAYOUT(_______, _______, _______, _______, MODECON, ENCPST0, _______, _______, _______, _______),
    [_FN1]   = LAYOUT(_______, _______, _______, _______, MODECON, ENCPST1, _______, _______, _______, _______),
    [_FN2]   = LAYOUT(_______, _______, _______, _______, MODECON, ENCPST2, _______, _______, _______, _______),
    [_FN3]   = LAYOUT(_______, _______, _______, _______, MODECON, ENCPST3, _______, _______, _______, _______),
    [_HUE]   = LAYOUT(RGBNHUD, RGBNHUI, KC_DOWN, KC_UP,   RGB_TOG, RGBRST,  _______, _______, RGBNHUD, RGBNHUI),
    [_SAT]   = LAYOUT(RGBNSAD, RGBNSAI, KC_DOWN, KC_UP,   _______, _______, _______, _______, RGBNSAD, RGBNSAI),
    [_VAL]   = LAYOUT(RGBNVAD, RGBNVAI, KC_DOWN, KC_UP,   _______, _______, RGBNVAD, RGBNVAI, _______, RGBNVAI),
    [_MODE]  = LAYOUT(RGBNRMD, RGBNMOD, KC_DOWN, KC_UP,   _______, WRTROM,  RGBNRMD, RGBNMOD, _______, _______)};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t presstime;
//    if (is_oled_scrolling())
//        oled_scroll_off();
    is_oled_sleep = false;
    oled_timer = timer_read32();
    switch (keycode) {
        case MODECON:
            if (record->event.pressed) {
                presstime      = timer_read();
                modecon_enable = true;
            } else {
                modecon_enable = false;
                if ((timer_elapsed(presstime) < MODECON_HOLD_TERM) && (current_layer == mode_layer)) {
                    tap_code16(KC_MUTE);
                } else {
                    if (current_layer > 0) {
                        layer_off(current_layer);
                    }
                    layer_on(mode_layer);
                    current_layer = mode_layer;
                    render_status();
                }
            }
            return false;
            break;
        case ENCPST0:
        case ENCPST1:
        case ENCPST2:
        case ENCPST3:
            encoder_lock_layer = keycode - ENCPST0 + 1;
            return false;
            break;
        case RGBNHUI:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_increase_hue_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNHUD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_decrease_hue_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNSAI:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_increase_sat_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNSAD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_decrease_sat_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNVAI:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_increase_val_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNVAD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_decrease_val_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNMOD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_step_noeeprom();
            }
#endif
            return false;
            break;
        case RGBNRMD:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                rgblight_step_reverse_noeeprom();
            }
#endif
            return false;
            break;
        case WRTROM:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_current();
                write_rom = true;
                key_timer = timer_read();
            }
#endif
            return false;
            break;

        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
#endif
            return false;
            break;
    }
    return true;
}

#ifdef OLED_ENABLE
#    include <stdio.h>
#    include <string.h>

// assign the right code to your layers for OLED display
#    define L_AUDIO 0
#    define L_RGB (1 << _RGB)
#    define L_FN0 (1 << _FN0)
#    define L_FN1 (1 << _FN1)
#    define L_FN2 (1 << _FN2)
#    define L_FN3 (1 << _FN3)
#    define L_HUE (1 << _HUE)
#    define L_SAT (1 << _SAT)
#    define L_VAL (1 << _VAL)
#    define L_MODE (1 << _MODE)

void keyboard_post_init_user(void) {
    oled_timer = timer_read32();
}

void render_status(void) {
    uint32_t render_timer;
    
    if (!is_oled_sleep && sleep_counter >= OLED_TIMEOUT / 1000) {
        is_oled_sleep = true;
        oled_off();
        sleep_counter = 0;
    } else if (!is_oled_sleep) {
        render_timer = timer_elapsed32(oled_timer);
        render_logo(render_timer < OLED_LOGO_TOGGLE_INTERVAL ? 0 : 1);
        if (render_timer >= OLED_LOGO_TOGGLE_INTERVAL * 2) {
            oled_timer = timer_read32();
            sleep_counter++;
        }
        if (write_rom) {
            oled_write_P(PSTR("RGB CONFIG SAVED"), true);
            if (timer_elapsed(key_timer) > OLED_INFOMATION_TERM) {
                write_rom = false;
            }
        } else {
            // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
            switch (get_highest_layer(layer_state)) {
                case _AUDIO:
                    oled_write_P(PSTR("MAIN LAYER"), false);
                    break;
                case _FN0:
                    oled_write_P(PSTR("FN0 LAYER"), false);
                    break;
                case _FN1:
                    oled_write_P(PSTR("FN1 LAYER"), false);
                    break;
                case _FN2:
                    oled_write_P(PSTR("FN2 LAYER"), false);
                    break;
                case _FN3:
                    oled_write_P(PSTR("FN3 LAYER"), false);
                    break;
                case _RGB:
                    oled_write_P(PSTR("RGB CONFIG"), false);
                    break;
                case _HUE:
                    oled_write_P(PSTR("RGB HUE CTRL/RESET"), false);
                    break;
                case _SAT:
                    oled_write_P(PSTR("RGB SAT CTRL"), false);
                    break;
                case _VAL:
                    oled_write_P(PSTR("RGB VAL CTRL"), false);
                    break;
                case _MODE:
                    oled_write_P(PSTR("RGB MODE CTRL/SAVE"), false);
                    break;
                default:
                    break;
            }
        }
        oled_write_ln_P((!modecon_enable) ? PSTR("") : (mode_layer == _AUDIO) ? PSTR(" >> MAIN") : (mode_layer == _RGB) ? PSTR(" >> RGB") : (mode_layer == _FN0) ? PSTR(" >> FN0") : (mode_layer == _FN1) ? PSTR(" >> FN1") : (mode_layer == _FN2) ? PSTR(" >> FN2") : (mode_layer == _FN3) ? PSTR(" >> FN3") : (mode_layer > _FN3) ? PSTR(" >> RGB") : "", false);
        UPDATE_LED_STATUS();
        RENDER_LED_STATUS();
    }
}

bool oled_task_user(void) {
    render_status();
    return false;
}
#endif

void led_set_user(uint8_t usb_led) {}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    bool     encoder_layer_locked = false;

    if (index == 0) {
        if (modecon_enable) {
            if (clockwise) {
                mode_layer++;
                if (mode_layer > _FN3) {
                    mode_layer = 0;
                }
            } else {
                if (mode_layer == 0) {
                    mode_layer = _FN3;
                } else {
                    mode_layer--;
                }
            }
            render_status();
            return false;
        } else {
            if (clockwise) {
                key.row = ENCODER0_CW_KEY_ROW;
                key.col = ENCODER0_CW_KEY_COL;
            } else {
                key.row = ENCODER0_CCW_KEY_ROW;
                key.col = ENCODER0_CCW_KEY_COL;
            }
        }
    } else if (index == 1) {
        if (clockwise) {
            key.row = ENCODER1_CW_KEY_ROW;
            key.col = ENCODER1_CW_KEY_COL;
        } else {
            key.row = ENCODER1_CCW_KEY_ROW;
            key.col = ENCODER1_CCW_KEY_COL;
        }
    }

    if (get_highest_layer(layer_state) == 0) {
        layer_on(encoder_lock_layer);
        encoder_layer_locked = true;
    }
    action_exec((keyevent_t){.key = key, .pressed = true, .time = (timer_read() | 1)});
    action_exec((keyevent_t){.key = key, .pressed = false, .time = (timer_read() | 1)});
    if (encoder_layer_locked) {
        layer_off(encoder_lock_layer);
    }
    return true;
}
#endif
