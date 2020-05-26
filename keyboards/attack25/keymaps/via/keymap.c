#include QMK_KEYBOARD_H
#include "promicro_LED.h"

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    extern RGB_CONFIG_t RGB_CONFIG;
    RGB_CONFIG_t RGB_current_config;
    bool RGB_momentary_on;
#endif

#ifdef MAC_MODE
    bool MAC_mode = true;
#else
    bool MAC_mode = false;
#endif

bool NumLock_Mode = true;

enum layer_number {
    _NUM = 0,
    _NUMOFF,
    _FN,
    _RGB,
    _BLED
};

enum custom_keycodes {
    RGB_MODR = SAFE_RANGE,
    RGBRST,
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

    [_RGB] = LAYOUT_ortho_5x5( \
	    RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, \
        RGBRST,  RGB_MODR, RGB_HUD, RGB_SAD, RGB_VAD, \
	    RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_SPI, RGB_SPI, XXXXXXX, \
	    RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_SPD, RGB_SPD, XXXXXXX, \
	    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS), \


     [_BLED] = LAYOUT_ortho_5x5(
        BL_TOGG, BL_ON, BL_INC, BL_STEP, XXXXXXX,
        BL_BRTG, BL_OFF, BL_DEC, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

void matrix_init_user(void) {
    #if defined(RGBLIGHT_ENABLE)
	    rgblight_init();
        RGB_current_config = RGB_CONFIG;
    #elif defined(RGB_MATRIX_ENABLE)
        rgb_matrix_init();
        RGB_current_config = RGB_CONFIG;
    #endif
    TX_RX_LED_INIT; //Turn LEDs off by default
    RXLED0;
    TXLED0;
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case WINMAC:
            if (record->event.pressed) {
                MAC_mode = !MAC_mode;
                if (MAC_mode && !NumLock_Mode) {
                    SEND_STRING(SS_TAP(X_NUMLOCK));
                } else if (!MAC_mode) {
                    layer_off(_NUMOFF);
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

	    case RGB_MOD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_mode_noeeprom(RGB_current_config.mode);
		        rgblight_step();
		        RGB_current_config.mode = RGB_CONFIG.mode;
	        }
            return false;
        #else
            return true;
        #endif
	    break;

	    case RGB_MODR:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_mode_noeeprom(RGB_current_config.mode);
		        rgblight_step_reverse();
		        RGB_current_config.mode = RGB_CONFIG.mode;
	        }
            return false;
        #else
            return true;
        #endif
	    break;

	    case RGBRST:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
                RGB_current_config = RGB_CONFIG;
	        }
        #endif
	    return false;
	    break;

	    case RGB_HUI:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
	            rgblight_increase_hue();
                RGB_current_config_hue = RGB_CONFIG_hue;
	        }
        return false;
        #else
            return true;
        #endif
	    break;

	    case RGB_HUD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        	if (record->event.pressed) {
		        rgblight_decrease_hue();
                RGB_current_config_hue = RGB_CONFIG_hue;
	        }
            return false;
        #else
	        return true;
        #endif
	    break;

	    case RGB_SAI:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
            if (record->event.pressed) {
		        rgblight_increase_sat();
		        RGB_current_config_sat = RGB_CONFIG_sat;
            }
            return false;
        #else
            return true;
        #endif
    	break;

	    case RGB_SAD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_decrease_sat();
                RGB_current_config_sat = RGB_CONFIG_sat;
	        }
            return false;
        #else
            return true;
        #endif
	    break;

	    case RGB_VAI:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_increase_val();
	            RGB_current_config_val = RGB_CONFIG_val;
	        }
            return false;
        #else
            return true;
        #endif
    	break;

	    case RGB_VAD:
        #if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
	        if (record->event.pressed) {
		        rgblight_decrease_val();
	            RGB_current_config_val = RGB_CONFIG_val;
	        }
            return false;
        #else
            return true;
        #endif
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
			  RGB_current_config.mode = RGB_CONFIG.mode;
		    }
        #endif
	    return true;
	    break;

	case P00:
	    if (record->event.pressed) {
	        SEND_STRING("00");
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
                rgb_sethsv_noeeprom(RGB_current_config_hue, RGB_current_config_sat, RGB_current_config_val);
                rgblight_mode_noeeprom(RGB_current_config.mode);
	        } else {
                #ifdef RGBLED_BOTH
                    rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_UNDERGLOW);
                #else
                    rgb_matrix_layer_helper(HSV_AZURE, 1, rgb_matrix_config.speed, LED_FLAG_NONE);
                #endif
	        }
	    }
    }

#elif defined(RGBLIGHT_ENABLE)
    uint32_t layer_state_set_user(uint32_t state) {
	    switch (biton32(state)) {
            case _FN:
                rgblight_sethsv_noeeprom(HSV_ORANGE);
                rgblight_mode_noeeprom(1);
		        RGB_momentary_on = true;
		        break;

            case _NUMOFF:
                rgblight_sethsv_noeeprom(HSV_AZURE);
			    rgblight_mode_noeeprom(1);
                break;

            case _RGB:
		        break;

            default:
                RGB_current_config.raw = eeconfig_read_rgblight();
		        rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
	            rgblight_mode_noeeprom(RGB_current_config.mode);
	            RGB_momentary_on = false;
                break;
	    }
	    return state;
    }

    void led_set_user(uint8_t usb_led) {
        if (!RGB_momentary_on && !MAC_mode) {
	        if (usb_led & (1 << USB_LED_NUM_LOCK)) {
                rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
			    rgblight_mode_noeeprom(RGB_current_config.mode);
	        } else {
		        rgblight_sethsv_noeeprom_azure();
                rgblight_mode_noeeprom(1);
	        }
	    }
    }
#endif

