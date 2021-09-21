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

//#ifdef ENCODER_INIT_ENABLE
extern bool encoders_changed;
extern uint16_t int_count;

void keyboard_pre_init_kb(void) {
    //Enable Pin Change Interrupts
    PCICR = 0;                // Disable all Pin Change Interrupts

#ifdef ENCODER_SINGLE_INTERRUPT
  //  PCMSK0 = _BV(PCINT6) | _BV(PCINT3);
#else
    PCMSK0 = _BV(PCINT2) | _BV(PCINT6) | _BV(PCINT1) | _BV(PCINT3);
#endif
    PCICR |= _BV(PCIE0);

    encoder_init();
    keyboard_pre_init_user();
}

void housekeeping_task_kb() {
#ifdef ENCODER_DETECT_OVER_SPEED
    if (int_count > 100) {
        dprintf("Interrupt: %u\n", int_count);
        int_count = 0;
    }
#endif
#ifdef OLED_ENABLE
    //oled_task();
#    if OLED_TIMEOUT > 0
    // Wake up oled if user is using those fabulous keys or spinning those encoders!
    if (encoders_changed) oled_on();
#    endif
#endif
    housekeeping_task_user();
}
//#endif
