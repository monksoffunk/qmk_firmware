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
#include QMK_KEYBOARD_H
//#include <../rev1/rev1.h>

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
    _ENCADJ
};

// Defines the keycodes used by our macros in process_record_user
// start with = USR_SAFE_RANGE
/* enum custom_keycodes {
    QWERTY = USR_SAFE_RANGE,
}; */


 /* Default Layer
     * ,-----------------------------------------------------------.
     * | Esc|  Q |  W |  E |  R |  T |  Y |  U |  I |  O |  P | BS |
     * |-----------------------------------------------------------|
     * | Tab |  A |  S |  D |  F |  G |  H |  J |  K |  L | Ent    |
     * |-----------------------------------------------------------|
     * | LSft   |  Z |  X |  C |  V |  B |  N |  M |  , | . |fn2(/)|
     * |-----------------------------------------------------------|
     * | Esc  | LAlt| LGui|  spc fn0  |  spc fn1    |RGui|RAlt|RCtl|
     * `-----------------------------------------------------------'
 */

#define __________DEFAULT_1__________   KC_ESC,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,   KC_BSPC
#define __________DEFAULT_2__________   MT(MOD_LCTL, KC_TAB),  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_ENT
#define __________DEFAULT_3__________   KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  LT(_ADJUST, KC_SLSH)
#define __________DEFAULT_4__________   MT(MOD_LCTL, KC_ESC), KC_LALT   , KC_LGUI, LT(_LOWER, KC_SPC),   LT(_RAISE, KC_SPC), KC_RGUI, KC_RALT, KC_RCTL

 /* Lower Layer
     * ,-----------------------------------------------------------.
     * |  ~ |  ! |  @ |  # |  $ |  % |  ^ |  & |  * |  ( |  ) |EN11|
     * |-----------------------------------------------------------|
     * |        |    |    |    |    |     | _ | + | { | } |  Pipe  |
     * |-----------------------------------------------------------|
     * |          |    |    |    |    |    |   | ;  | '  | Up |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |Left|Down|Right |
     * `-----------------------------------------------------------'
     */

#define ___________LOWER_1___________   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, ENC_11
#define ___________LOWER_2___________   _______, _______, _______, _______, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE
#define ___________LOWER_3___________   _______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT, KC_UP,   _______
#define ___________LOWER_4___________   _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT

	/* Raise Layer
     * ,-----------------------------------------------------------.
     * |  ` |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 |  0 | Del|
     * |-----------------------------------------------------------|
     * |  F1   | F2  | F3 | F4 | F5 |  F6 | - | = | [ | ] |  Pipe  |
     * |-----------------------------------------------------------|
     * |    F7    | F8 | F9 | F10| F11| F12|  \ |  \ |   |    |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
     */

#define ___________RAISE_1___________   KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL
#define ___________RAISE_2___________   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS
#define ___________RAISE_3___________   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______
#define ___________RAISE_4___________   _______, _______, _______, _______, _______, _______, _______, _______

	/* Adjust Layer
     * ,-----------------------------------------------------------.
     * |Mute| F1 | F2 | F3 | F4 | F5 | F6 | F7 | F8 | F9 | F10|F11 |
     * |-----------------------------------------------------------|
     * |ENCADJ |BTOG |BSTP|BINC| MAC|RGBTOG|HUI|WIN|SAI|VAI|  F12  |
     * |-----------------------------------------------------------|
     * |   Caps   |     |BBRE|BDEC|    |RMOD|HUD |   |SAD|VAD |    |
     * |-----------------------------------------------------------|
     * |SLEEP|    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
      */

#define __________ADJUST_1___________   KC_MUTE, KC_F1,   KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11
#define __________ADJUST_2___________   MO(_ENCADJ), BL_TOGG, BL_STEP, BL_INC,  AG_NORM,  RGB_TOG, RGB_HUI, AG_SWAP, RGB_SAI, RGB_VAI,  KC_F12
#define __________ADJUST_3___________   KC_CAPS, _______,   BL_BRTG, BL_DEC,  _______,  RGB_MOD, RGB_HUD, _______, RGB_SAD, RGB_VAD,  _______
#define __________ADJUST_4___________   KC_SLEP, _______, _______, _______, _______, _______, _______, _______

    /* Encoder Adj Layer
     * ,-----------------------------------------------------------.
     * |EN00|EN01|EN02|EN03|    |    |    |    |EN13|EN12|EN11|EN10|
     * |-----------------------------------------------------------|
     * |ENCADJ|CHENCR0|CHENCR1|    |    |      |   |   |   |   |   |
     * |-----------------------------------------------------------|
     * |          |Reset|    |    |    |    |    |   |   |    |    |
     * |-----------------------------------------------------------|
     * |     |    |     |           |             |     |    |     |
     * `-----------------------------------------------------------'
      */

#define __________ENCADJ_1___________   ENC_00,  ENC_01,  ENC_02,  ENC_03,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ENC_13,  ENC_12,  ENC_11,  ENC_10
#ifdef ENCODER_ENABLE
#define __________ENCADJ_2___________   _______, CHENCR0, CHENCR1, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#else
#define __________ENCADJ_2___________   _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#endif
#define __________ENCADJ_3___________   XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______
#define __________ENCADJ_4___________   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX

#ifdef ENCODER_ENABLE
// keycodes setting for encoder             LEFT_CCW    LEFT_CW   RIGHT_CCW   RIGHT_CW
#    define __________DEFAULT_E__________   KC_PGUP,    KC_PGDN,  KC_PGUP,    KC_PGDN
#    define ___________LOWER_E___________   KC_VOLD,    KC_VOLU,  KC_VOLD,    KC_VOLU
#    define ___________RAISE_E___________   S(KC_TAB),  KC_TAB,   S(KC_TAB),  KC_TAB
#    define __________ADJUST_E___________   RGB_RMOD,   RGB_MOD,  RGB_RMOD,   RGB_MOD
#    define __________ENCADJ_E___________   BL_DEC,     BL_INC,   BL_DEC,     BL_INC
#endif

#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#ifdef ENCODER_ENABLE
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
        __________DEFAULT_E__________,
        __________DEFAULT_1__________,
        __________DEFAULT_2__________,
        __________DEFAULT_3__________,
        __________DEFAULT_4__________),

    [_LOWER] = LAYOUT_wrapper(
        ___________LOWER_E___________,
        ___________LOWER_1___________,
        ___________LOWER_2___________,
        ___________LOWER_3___________,
        ___________LOWER_4___________),

    [_RAISE] = LAYOUT_wrapper(
        ___________RAISE_E___________,
        ___________RAISE_1___________,
        ___________RAISE_2___________,
        ___________RAISE_3___________,
        ___________RAISE_4___________),

    [_ADJUST] = LAYOUT_wrapper(
        __________ADJUST_E___________,
        __________ADJUST_1___________,
        __________ADJUST_2___________,
        __________ADJUST_3___________,
        __________ADJUST_4___________),

    [_ENCADJ] = LAYOUT_wrapper(
        __________ENCADJ_E___________,
        __________ENCADJ_1___________,
        __________ENCADJ_2___________,
        __________ENCADJ_3___________,
        __________ENCADJ_4___________)
};
#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_wrapper(
        __________DEFAULT_1__________,
        __________DEFAULT_2__________,
        __________DEFAULT_3__________,
        __________DEFAULT_4__________),

    [_LOWER] = LAYOUT_wrapper(
        ___________LOWER_1___________,
        ___________LOWER_2___________,
        ___________LOWER_3___________,
        ___________LOWER_4___________),

    [_RAISE] = LAYOUT_wrapper(
        ___________RAISE_1___________,
        ___________RAISE_2___________,
        ___________RAISE_3___________,
        ___________RAISE_4___________),

    [_ADJUST] = LAYOUT_wrapper(
        __________ADJUST_1___________,
        __________ADJUST_2___________,
        __________ADJUST_3___________,
        __________ADJUST_4___________),

    [_ENCADJ] = LAYOUT_wrapper(
        __________ENCADJ_1___________,
        __________ENCADJ_2___________,
        __________ENCADJ_3___________,
        __________ENCADJ_4___________)
};
#endif

// bool encoder_update_user(uint8_t index, bool clockwise) {
//     if (index == 0) { /* Left encoder */
//         switch (get_highest_layer(layer_state)) {
//             case _QWERTY:
//                 if (clockwise) {
//                     tap_code(KC_TAB);
//                 } else {
//                     tap_code16(S(KC_TAB));
//                 }
//                 break;
//             case _RAISE:
//                 if (clockwise) {
//                 //    tap_code(KC_VOLU);
//                     if(keymap_config.swap_lalt_lgui==false){
//                         tap_code(KC_LANG2);
//                     }else {
//                         tap_code16(A(KC_GRV));
//                     }
//                 } else {
//                     if(keymap_config.swap_lalt_lgui==false){
//                     tap_code(KC_LANG1);
//                     } else {
//                         tap_code16(A(KC_GRV));
//                     }
//                 }
//                     break;
//             case _ADJUST:
//                 if (clockwise) {
//                     tap_code(KC_VOLU);
//                 } else {
//                     tap_code(KC_VOLD);
//             }
//         }

//     } else if (index == 1) { /* Right encoder */
//         if (clockwise) {
//             tap_code(KC_PGDN);
//         } else {
//             tap_code(KC_PGUP);
//         }
//     }
//     return true;
// }
