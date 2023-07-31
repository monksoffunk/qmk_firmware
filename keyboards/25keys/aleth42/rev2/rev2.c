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

#include "rev2.h"

user_config_t user_config;

#ifdef ENCODER_ENABLE
uint8_t encoderlocklayer[] =  {0, 0};
#endif

void eeconfig_init_kb(void) {
    user_config.raw      = 0;
    user_config.mac_mode = true;
    uint8_t encoder_resolutions[] = ENCODER_RESOLUTIONS;
    user_config.encoder_resolutions[0] = encoder_resolutions[0];
    user_config.encoder_resolutions[1] = encoder_resolutions[1];
    eeconfig_update_kb(user_config.raw);
    eeconfig_init_user();
}

void keyboard_pre_init_kb(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_kb();
    keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !user_config.mac_mode;
#ifdef ENCODER_ENABLE
    for (uint8_t i = 0 ; i < 2 ; i++) {
        if ((user_config.encoder_resolutions[i] == 0) || (user_config.encoder_resolutions[i] > 4)) {
            user_config.encoder_resolutions[i] = 4;
            eeconfig_update_kb(user_config.raw);
        }
//        encoder_set_resolution(i, user_config.encoder_resolutions[i]);
    }
#endif
//    rgblight_toggle_noeeprom();
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
//    rgblight_toggle_noeeprom();
    rgblight_disable_noeeprom();
    rgblight_reload_from_eeprom();
}


#ifdef ENCODER_ENABLE
void matrix_scan_kb(void) {
    encoder_action_unregister(encoderlocklayer);
    matrix_scan_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise, encoderlocklayer);
    return true;
}
#endif

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case AG_NORM:
            if (record->event.pressed) {
                if (!user_config.mac_mode) {
                    user_config.mac_mode = true;
                    eeconfig_update_kb(user_config.raw);
                    }
            }
            return true;
            break;
        case AG_SWAP:
            if (record->event.pressed) {
                if (user_config.mac_mode) {
                    user_config.mac_mode = false;
                    eeconfig_update_kb(user_config.raw);
                    }
            }
            return true;
            break;
#ifdef ENCODER_ENABLE
        case CHENCR0:
        case CHENCR1:
            if (record->event.pressed) {
            } else {
                uint8_t index = keycode - CHENCR0;
                user_config.encoder_resolutions[index] = (user_config.encoder_resolutions[index] << 1) & 7;
                if (user_config.encoder_resolutions[index] == 0) { user_config.encoder_resolutions[index] = 1; }
//                encoder_set_resolution(index, user_config.encoder_resolutions[index]);
                eeconfig_update_kb(user_config.raw);
            }
            return false;
            break;
        case ENC_00:
        case ENC_01:
        case ENC_02:
        case ENC_03:
        case ENC_04:
            if (record->event.pressed) {
                if (encoderlocklayer[0] != keycode - ENC_00) {
                    encoderlocklayer[0] = keycode - ENC_00;
                } else {
                    encoderlocklayer[0] = 0;
                }
            }
            return false;
            break;
        case ENC_10:
        case ENC_11:
        case ENC_12:
        case ENC_13:
        case ENC_14:
            if (record->event.pressed) {
                if (encoderlocklayer[1] != keycode - ENC_10) {
                    encoderlocklayer[1] = keycode - ENC_10;
                } else {
                    encoderlocklayer[1] = 0;
                }
            }
            return false;
            break;
#endif
        default:
            break;
    }
    return process_record_user(keycode, record);
}
