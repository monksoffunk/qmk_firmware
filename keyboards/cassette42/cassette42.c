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
#include "cassette42.h"

#ifdef ENCODER_ENABLE
uint8_t encoder_lock_layer[] = {0,0};

void matrix_scan_kb(void) {
    encoder_action_unregister(encoder_lock_layer);
    matrix_scan_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise, encoder_lock_layer);
    return(encoder_update_user(index, clockwise));
}

bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case ENCPST0:
        case ENCPST1:
        case ENCPST2:
        case ENCPST3:
            if (record->event.pressed) {
                if (encoder_lock_layer[0] != keycode - ENCPST0 + 1) {
                    encoder_lock_layer[0] = keycode - ENCPST0 + 1;
                    encoder_lock_layer[1] = keycode - ENCPST0 + 1;
                } else {
                    encoder_lock_layer[0] = 0;
                    encoder_lock_layer[1] = 0;
                }
            }
            return false;
            break;
        default:
            break;
    }
    return process_record_user(keycode, record);
}
#endif
