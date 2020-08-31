#include QMK_KEYBOARD_H

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

    #define BLINK_DURATION 500

    void blink_indicator(uint8_t blink_rgb_layer, uint8_t blink_num) {
        RGB_current_config = RGB_CONFIG;
        for(uint8_t i = 0 ; i < blink_num ; i++) {
            rgblight_mode_noeeprom(0);
            rgblight_set_layer_state(blink_rgb_layer, true);
            wait_ms(BLINK_DURATION);
            rgblight_disable_noeeprom();
            wait_ms(BLINK_DURATION);
            rgblight_enable_noeeprom();
        }
        rgblight_set_layer_state(blink_rgb_layer, false);
        rgblight_mode_noeeprom(RGB_current_config.mode);
        rgb_sethsv_noeeprom(RGB_current_config_hue, RGB_current_config_sat, RGB_current_config_val);      
    }
#endif

#ifdef MAC_MODE
    bool MAC_mode = true;
#else
    bool MAC_mode = false;
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
        KC_P1, KC_P2, KC_P3, KC_TAB, LT(_BLED, KC_DEL),
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
        BL_TOGG, BL_ON, BL_INC, BL_STEP, XXXXXXX,
        BL_BRTG, BL_OFF, BL_DEC, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

void keyboard_post_init_user(void) {
// Call the post init code.
    debug_enable=true;
    numcheck_timer = timer_read();
    #if defined(RGBLIGHT_ENABLE)
        rgblight_init();
        RGB_current_config = RGB_CONFIG;
        rgblight_layers = rgb_layers;
        blink_indicator(2+!MAC_mode, 3);
    #elif defined(RGB_MATRIX_ENABLE)
        rgb_matrix_init();
        RGB_current_config = RGB_CONFIG;
    #endif
}

void matrix_scan_user(void) {
    #ifdef MAC_MODE
        if (!NumLock_init_done) {
            if (timer_elapsed(numcheck_timer) > 500) {
                if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
                    tap_code16(KC_NLCK);
                }
                NumLock_init_done = true;
            }
        }
        #ifdef LED_NLK
            writePin(LED_NLK, NumLock_Mode);
        #endif
    #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WINMAC:
            if (record->event.pressed) {
                MAC_mode = !MAC_mode;
                #ifdef RGBLIGHT_ENABLE
                    blink_indicator(2+!MAC_mode, 3);
                #endif                  
                if (MAC_mode && !NumLock_Mode) {
                    tap_code16(KC_NLCK);
                    layer_on(_NUMOFF);
                } else if (!MAC_mode && !NumLock_Mode) {
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
                if (MAC_mode) {
                    NumLock_Mode = !NumLock_Mode;
                    if (NumLock_Mode) {
                        layer_off(_NUMOFF);
                    } else {
                        layer_on(_NUMOFF);
                    }
                    #ifdef LED_NLK
                        writePin(LED_NLK, NumLock_Mode);
                    #endif
                    return false;
                } else {
                    return true; //Win
                }
            } else {
                if (MAC_mode) {
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

    case RGB_MODE_PLAIN:
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
        break;

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
        if (!RGB_momentary_on && rgb_matrix_config.enable && !MAC_mode) {
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
#else // for RGBLIGHT or LED_NumLock enabled
    uint32_t layer_state_set_user(uint32_t state) {
        if (MAC_mode) {
            rgblight_set_layer_state(0, layer_state_cmp(state, _NUMOFF));
        }
        rgblight_set_layer_state(1, layer_state_cmp(state, _FN));
        return state;
        }
#endif

void led_set_user(uint8_t usb_led) {
    if (!MAC_mode) {
        if (usb_led & (1 << USB_LED_NUM_LOCK)) {
            NumLock_Mode = true;
            #ifdef RGBLIGHT_ENABLE
            // turn _NUMOFF layer light off when NumLock in Windows Mode
            rgblight_set_layer_state(0, false);
            #endif                
            #ifdef LED_NLK
                writePin(LED_NLK, 1);
            #endif
        } else {
            NumLock_Mode = false;
            #ifdef RGBLIGHT_ENABLE
            // layer Lightning mode is _NUMOFF though _NUM layer in Windows Mode (NumLock LED off)
            rgblight_set_layer_state(0, true);
            #endif
            #ifdef LED_NLK
                writePin(LED_NLK, 0);
            #endif
        }
    }
}

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
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
                        tap_code(KC_LANG2);
                    }else {
                        SEND_STRING(SS_LALT("`"));
                    }
                } else {
                    if(keymap_config.swap_lalt_lgui==false){
                        tap_code(KC_LANG1);
                    } else {
                        SEND_STRING(SS_LALT("`"));
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

            case _RGB:
                if (clockwise) {
                    rgblight_step();
                } else {
                    rgblight_step_reverse();
                }
                break;

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
}           
#endif
