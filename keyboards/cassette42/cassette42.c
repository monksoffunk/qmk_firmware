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
#include <avr/io.h>
#include <avr/interrupt.h>


void keyboard_pre_init_kb(void) {
    //Enable Pin Change Interrupts
    PCICR = 0;                // Disable all Pin Change Interrupts
    PCMSK0 = _BV(PCINT2) | _BV(PCINT6) | _BV(PCINT1) | _BV(PCINT3);
    PCICR |= _BV(PCIE0);

    encoder_init();
    keyboard_pre_init_user();
}
