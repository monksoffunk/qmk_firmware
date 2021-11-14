/* Copyright 2021 monksoffunk
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

#include "quantum.h"
#include <common/encoder_action.h>

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
/* ALETH42 layout
 * ,-----------------------------------------------------------.
 * | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 0A | 49 |
 * |-----------------------------------------------------------|
 * | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A | 4A |
 * |-----------------------------------------------------------|
 * | 20   | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 2A    |
 * |-----------------------------------------------------------|
 * | 30     | 31 | 32 | 33 | 34 | 35 | 36 | 37 | 38 | 39 | 3A  |
 * |-----------------------------------------------------------|
 * | 40 | 41  | 42  |    43     |      44     | 45  | 46 | 47  |
 * `-----------------------------------------------------------'
 *
 * ENCODER0     ENCODER1
 * CCW | CW     CCW | CW
 * RE0  RE1     RE2  RE3
 *
 * ENCODER0 can replace switch 00 or 0A
 * ENCODER1 can replace switch 01 or 49
 */
#ifdef ENCODER_ENABLE
#define LAYOUT( \
  RE0, RE1, RE2, RE3,\
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k49,\
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k4A,\
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29,      k2A,\
  k30,      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,\
  k40, k41,      k42,      k43,      k44,      k45, k46, k47\
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, RE0 },\
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, RE1 },\
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, RE2 },\
  { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, RE3 },\
  { k40, k41, k42, k43, k44, k45, k46, k47, KC_NO, k49, k4A, KC_NO }\
}
#else
#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k49,\
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, k4A,\
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29,      k2A,\
  k30,      k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A,\
  k40, k41,      k42,      k43,      k44,      k45, k46, k47\
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, KC_NO },\
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A, KC_NO },\
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A, KC_NO },\
  { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, KC_NO },\
  { k40, k41, k42, k43, k44, k45, k46, k47, KC_NO, k49, k4A, KC_NO }\
}
#endif

typedef union {
  uint32_t raw;
  struct {
    bool mac_mode :1;
    bool          :0;
    uint8_t encoder_resolutions[2];
  };
} user_config_t;

#ifdef ENCODER_ENABLE
enum kb_keycodes {
    ENCADJ = KC_FN0,
    CHENCR0,
    CHENCR1,
    ENC_00,
    ENC_01,
    ENC_02,
    ENC_03,
    ENC_04,
    ENC_10,
    ENC_11,
    ENC_12,
    ENC_13,
    ENC_14
};
#endif
