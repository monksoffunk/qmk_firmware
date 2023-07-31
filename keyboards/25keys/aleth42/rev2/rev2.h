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

#include "quantum.h"
#include <../common/encoder_action.h>

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
/* ALETH42 layout
 * ,-----------------------------------------------------------.  ,-------. ,-------.
 * | 00 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 0A | 38 |  |40 | 41| |42 | 43|
 * |-----------------------------------------------------------|  `-------' `-------'
 * | 10   | 11 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 1A    |
 * |-----------------------------------------------------------|
 * | 20     | 21 | 22 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 2A  |
 * |-----------------------------------------------------------|
 * | 30 | 31  | 32  |    33     |      34     | 35  | 36 | 37  |
 * `-----------------------------------------------------------'
 */

#ifdef ENCODER_ENABLE
#define LAYOUT( \
  k40, k41, k42, k43,\
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k38,\
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,\
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A,\
  k30, k31, k32, k33, k34, k35, k36, k37\
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A },\
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A },\
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A },\
  { k30, k31, k32, k33, k34, k35, k36, k37, 0,   0,   k38 },\
  { k40, k41, k42, k43, 0,   0,   0,   0,   0,   0,   0   }\
}
#else
#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k38,\
  k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A,\
  k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A,\
  k30, k31, k32, k33, k34, k35, k36, k37\
) \
{ \
  { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A },\
  { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1A },\
  { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2A },\
  { k30, k31, k32, k33, k34, k35, k36, k37, 0,   0,   k38 }\
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
    ENCADJ = SAFE_RANGE,//KC_FN0,
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
    ENC_14,
    USR_SAFE_RANGE,
};

#else
enum kb_keycodes {
    USR_SAFE_RANGE = SAFE_RANGE,
};
#endif
