/* Copyright 2021 sekigon-gonnoc
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

#include "platform_deps.h"
#include "quantum.h"
#include "hardware/adc.h"
#include "hardware/clocks.h"

#ifndef PICO_SYSTEM_CLOCK_KHZ
#    define PICO_SYSTEM_CLOCK_KHZ 125000
#endif

uint32_t interrupts;

void platform_setup(void) {

    set_sys_clock_khz(PICO_SYSTEM_CLOCK_KHZ, true);

    for (int i = 0; i < 32; i++) {
        if ( i != RGB_DI_PIN ) {
            gpio_init(i);
            setPinInputHigh(i);
        }
    }

    adc_init();
}
