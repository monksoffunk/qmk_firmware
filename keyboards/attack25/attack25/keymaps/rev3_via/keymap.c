#include QMK_KEYBOARD_H
//#include "debug.h"

#ifdef BACKLIGHT_ENABLE
    #include "backlight.h"
#endif

typedef union {
  uint32_t raw;
  struct {
    bool mac_mode :1;
  };
} user_config_t;

user_config_t user_config;

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    extern RGB_CONFIG_t RGB_CONFIG;
    RGB_CONFIG_t RGB_current_config;
    bool RGB_momentary_on = false;
#endif

#ifdef RGBLIGHT_ENABLE
    const rgblight_segment_t PROGMEM _NUMOFF_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_RGBLED_START, LAYER_RGBLED_NUM, HSV_CYAN - 100}
    );
    const rgblight_segment_t PROGMEM _FN_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_RGBLED_START, LAYER_RGBLED_NUM, HSV_ORANGE - 100}
    );
    const rgblight_segment_t PROGMEM _MAC_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_RGBLED_START, LAYER_RGBLED_NUM, HSV_MAGENTA - 100}
    );
    const rgblight_segment_t PROGMEM _WIN_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LAYER_RGBLED_START, LAYER_RGBLED_NUM, HSV_TEAL}
    );
    const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    _NUMOFF_layer,
    _FN_layer,
    _MAC_layer,
    _WIN_layer
    );
#endif
    #if defined(RGBLIGHT_ENABLE) || defined(LED_NLK)
    #define BLINK_DURATION 500

    void blink_indicator(uint8_t blink_rgb_layer, uint8_t blink_num) {
        #ifdef RGBLIGHT_ENABLE
            RGB_current_config = RGB_CONFIG;
        #endif

        for(uint8_t i = 0 ; i < blink_num ; i++) {
            #ifdef RGBLIGHT_ENABLE
                rgblight_mode_noeeprom(0);
                rgblight_set_layer_state(blink_rgb_layer, true);
                rgblight_enable_noeeprom();
            #endif
            #ifdef LED_NLK
                backlight_level_noeeprom(BACKLIGHT_LEVELS);
            #endif
            wait_ms(BLINK_DURATION);
            #ifdef RGBLIGHT_ENABLE
                rgblight_disable_noeeprom();
            #endif
            #ifdef LED_NLK
                backlight_level_noeeprom(0);
            #endif
            wait_ms(BLINK_DURATION);
            #ifdef RGBLIGHT_ENABLE
            #endif
        }
        #ifdef RGBLIGHT_ENABLE
            rgblight_set_layer_state(blink_rgb_layer, false);
            rgblight_mode_noeeprom(RGB_current_config.mode);
            rgb_sethsv_noeeprom(RGB_current_config_hue, RGB_current_config_sat, RGB_current_config_val);
            if (RGB_current_config.enable) {
                rgblight_enable_noeeprom();
            } else {
                rgblight_disable_noeeprom();
            }
        #endif
        #ifdef LED_NLK
            backlight_config_t backlight_eeprom_config;
            backlight_eeprom_config.raw = eeconfig_read_backlight();
            backlight_level_noeeprom(backlight_eeprom_config.level);
        #endif
    }
#endif

bool NumLock_Mode = true;
bool NumLock_init_done = false;
static uint16_t numcheck_timer;

enum layer_number {
    _NUM = 0,
    _NUMOFF,
    _FN,
    _RGB,
    _BLED
    };

enum custom_keycodes {
    RGBRST = SAFE_RANGE,
    P00,
    WINMAC
    };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUM] = LAYOUT_ortho_5x5(
        KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_ESC,
        KC_P7, KC_P8, KC_P9, KC_PPLS, LT(_FN, KC_SLCK),
        KC_P4, KC_P5, KC_P6, S(KC_TAB), LT(_RGB, KC_PSCR),
        KC_P1, KC_P2, KC_P3, KC_PENT, LT(_BLED, KC_DEL),
        KC_P0, P00, KC_PDOT, KC_PENT, KC_BSPC),

    [_NUMOFF] = LAYOUT_ortho_5x5(
        _______, _______, _______, _______, _______,
        KC_HOME, KC_UP, KC_PGUP, _______, LT(_FN, KC_SLCK),
        KC_LEFT, XXXXXXX, KC_RGHT, _______, LT(_RGB, KC_PSCR),
        KC_END, KC_DOWN, KC_PGDN, _______, _______,
        KC_INS, P00, KC_DEL, _______, _______),

    [_FN] = LAYOUT_ortho_5x5(
        KC_F10, KC_F11, KC_F12, KC_TRNS, KC_TRNS,
        KC_F7, KC_F8, KC_F9, KC_TRNS, XXXXXXX,
        KC_F4, KC_F5, KC_F6, KC_TRNS, _______,
        KC_F1, KC_F2, KC_F3, KC_TRNS, WINMAC,
        XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_RGB] = LAYOUT_ortho_5x5(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI,
        RGBRST,  RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD,
        RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_SPI, RGB_SPI, XXXXXXX,
        RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_SPD, RGB_SPD, XXXXXXX,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_BLED] = LAYOUT_ortho_5x5(
        XXXXXXX, XXXXXXX, BL_INC, BL_STEP, XXXXXXX,
        BL_BRTG, XXXXXXX, BL_DEC, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RESET, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

void keyboard_post_init_user(void) {
    // Call the post init code.
    // debug_enable = true;

    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    numcheck_timer = timer_read();
    #if defined(RGBLIGHT_ENABLE)
        rgblight_init();
        RGB_current_config = RGB_CONFIG;
        rgblight_layers = rgb_layers;
    #endif
    #if defined(RGBLIGHT_ENABLE) || defined(LED_NLK)
        blink_indicator(2+!user_config.mac_mode, 2+!user_config.mac_mode*2);
    #endif
}

#ifdef LED_NLK
void numlock_backlight(void) {
    backlight_config_t backlight_eeprom_config;
    backlight_eeprom_config.raw = eeconfig_read_backlight();
    if (NumLock_Mode && !is_backlight_enabled()) {
        backlight_level_noeeprom(backlight_eeprom_config.level);
    } else if (!NumLock_Mode && is_backlight_enabled()) {
        backlight_level_noeeprom(0);
    }
}
#endif

void matrix_scan_user(void) {
    if (user_config.mac_mode) {
        if (!NumLock_init_done) {
            if (timer_elapsed(numcheck_timer) > 500) {
                if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
                    tap_code16(KC_NLCK);
                }
                NumLock_init_done = true;
            }
        } else {
            #ifdef LED_NLK
                numlock_backlight();
            #endif
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WINMAC:
            if (record->event.pressed) {
                user_config.mac_mode = !user_config.mac_mode;
                eeconfig_update_user(user_config.raw);
                #ifdef RGBLIGHT_ENABLE
                    blink_indicator(2+!user_config.mac_mode, 2+!user_config.mac_mode*2);
                #endif                  
                if (user_config.mac_mode && !NumLock_Mode) {
                    tap_code16(KC_NLCK);
                    layer_on(_NUMOFF);
                } else if (!user_config.mac_mode && !NumLock_Mode) {
                    tap_code16(KC_NLCK);
                    layer_clear();
                    #ifdef RGBLIGHT_ENABLE
                        RGB_momentary_on = false;
                    #endif
                }
            }
            return false;
            break;

        case KC_NLCK:
            if (record->event.pressed) {
                if (user_config.mac_mode) {
                    NumLock_Mode = !NumLock_Mode;
                    if (NumLock_Mode) {
                        layer_off(_NUMOFF);
                    } else {
                        layer_on(_NUMOFF);
                    }
                    #ifdef LED_NLK
                        //numlock_backlight();
                    #endif
                    return false;
                } else {
                    return true; //Win
                }
            } else {
                if (user_config.mac_mode) {
                    return false;
                } else {
                    return true;
                }
            }
            break;

        case RGBRST:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        dprint("RGBRST\n");
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
        #endif
        return false;
        break;

/*     case RGB_MODE_PLAIN:
    case RGB_MODE_BREATHE:
    case RGB_MODE_RAINBOW:
    case RGB_MODE_SWIRL:
    case RGB_MODE_SNAKE:
    case RGB_MODE_KNIGHT:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
            } else {
            }
        #endif
        return true;
        break; */

    case P00:
        if (record->event.pressed) {
            tap_code(KC_P0);
            tap_code(KC_P0);
        }
        return false;
        break;

    default:
    break;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
    void rgb_matrix_indicators_user(void) {
        if (!g_suspend_state && rgb_matrix_config.enable) {
            switch (biton32(layer_state)) {
                case _FN:
                    RGB_momentary_on = true;
                    #ifdef RGBLED_BOTH
                        rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                    #else
                        rgb_matrix_layer_helper(HSV_ORANGE, 0, rgb_matrix_config.speed, LED_FLAG_NONE);
                    #endif
                    break;

                case _NUMOFF:
                    #ifdef RGBLED_BOTH
                        rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                    #else
                        rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_NONE);
                    #endif
                    break;

                case _RGB:
                    break;

                default:
                    RGB_momentary_on = false;
                    break;
            }
        }
        uint8_t usb_led = host_keyboard_leds();
        if (!RGB_momentary_on && rgb_matrix_config.enable && !user_config.mac_mode) {
            NumLock_Mode = usb_led & (1 << USB_LED_NUM_LOCK);
            if (NumLock_Mode) {
                rgb_matrix_enable_noeeprom();
            } else {
                #ifdef RGBLED_BOTH
                    rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                #else
                    rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_NONE);
                #endif
            }
        }
    }
#else 
    #ifdef RGBLIGHT_ENABLE
        uint32_t layer_state_set_user(uint32_t state) {
            if (user_config.mac_mode) {
                rgblight_set_layer_state(0, layer_state_cmp(state, _NUMOFF));
            }
            rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
            return state;
            }
    #endif
#endif

void led_set_user(uint8_t usb_led) {
    if (!user_config.mac_mode) {
        if (usb_led & (1 << USB_LED_NUM_LOCK)) {
            NumLock_Mode = true;
            #ifdef RGBLIGHT_ENABLE
            // turn _NUMOFF layer light off when NumLock in Windows Mode
            rgblight_set_layer_state(0, false);
            #endif
        } else {
            NumLock_Mode = false;
            #ifdef RGBLIGHT_ENABLE
            // layer Lightning mode is _NUMOFF though _NUM layer in Windows Mode (NumLock LED off)
            rgblight_set_layer_state(0, true);
            #endif
        }
            #ifdef LED_NLK                       
                numlock_backlight();
                //writePin(LED_NLK, NumLock_Mode);
            #endif
    }
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state)) {
            case _NUM:
                if (clockwise) {
                    tap_code(KC_TAB);
                } else {
                    register_code(KC_LSFT);
                    tap_code(KC_TAB);
                    unregister_code(KC_LSFT);
                }
                break;

            case _NUMOFF:
                if (clockwise) {
                    if(keymap_config.swap_lalt_lgui==false){
                        tap_code16(LCMD(KC_Y));
                    } else {
                        tap_code16(C(KC_Y));
                    }
                } else {
                    if(keymap_config.swap_lalt_lgui==false){
                        tap_code16(LCMD(KC_Z));
                    } else {
                        tap_code16(C(KC_Z));
                    }
                }
                break;

            case _FN:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
#ifdef RGBLIGHT_ENABLE
            case _RGB:
                if (clockwise) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
                break;
#endif
            case _BLED:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
            
            default:
                break;
        }
    }
    return true;
}           
#endif
