/*
Copyright 2019 monksoffunk

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "numa16.h"
#include "common/promicro_LED.h"

#ifndef SMD
void keyboard_post_init_kb(void) {
        TX_RX_LED_INIT; //Turn ProMicro LEDs off by default
        RXLED0;
        TXLED0;
        keyboard_post_init_user();
}
#endif
