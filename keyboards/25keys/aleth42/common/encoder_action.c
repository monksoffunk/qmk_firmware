/* Copyright 2020 Neil Brian Ramirez
 * Copyright 2021 monksoffunk
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "encoder_action.h"

#ifdef ENCODERS
static uint8_t encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS] = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS] = ENCODERS_CCW_KEY;
#endif

void encoder_action_unregister(uint8_t *locklayer) {
#ifdef ENCODERS
    bool layerlocked = false;
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            if ((get_highest_layer(layer_state) == 0) && (locklayer[index] > 0)) {
                layer_on(locklayer[index]);
                layerlocked = true;
            }
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
            if (layerlocked) {
                layer_off(locklayer[index]);
            }
        }
    }
#endif
}

void encoder_action_register(uint8_t index, bool clockwise, uint8_t *locklayer) {
#ifdef ENCODERS
    bool layerlocked = false;
    if ((get_highest_layer(layer_state) == 0) && (locklayer[index] > 0)) {
        layer_on(locklayer[index]);
        layerlocked = true;
    }
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
    if (layerlocked) {
        layer_off(locklayer[index]);
    }
#endif
}
