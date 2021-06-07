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

#pragma once

enum attack25_layer_number {
    _NUM = 0,
    _NUMOFF,
    _FN,
    _RGB,
    _BLED,
    _SP
    };

#ifndef ATTACK25_CUSTOM_KEYCODES
enum attack25_custom_keycodes {
    RGBRST = SAFE_RANGE,
    P00,
    WINMAC,
    EN_RST,
    EN_FN,
    EN_RGB,
    EN_BLED,
    EN_SP
    };
#endif

#ifndef ATTACK25_CUSTOM_USER_EEPROM
typedef union {
  uint32_t raw;
  struct {
    bool mac_mode :1;
  };
} user_config_t;
#endif
