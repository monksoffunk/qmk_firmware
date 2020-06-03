#include QMK_KEYBOARD_H

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    extern RGB_CONFIG_t RGB_CONFIG;
    RGB_CONFIG_t RGB_current_config;
    bool RGB_momentary_on;
#endif

bool MAC_mode = true;
bool NumLock_Mode = true;

enum layer_number {
    _NUM = 0,
    _NUMOFF,
    _FN,
    _FN2,
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
[_NUM] = LAYOUT_ortho_4x4(
	KC_P7, KC_P8, KC_P9, LT(_RGB, KC_PMNS),
	KC_P4, KC_P5, KC_P6, LT(_FN, KC_PPLS),
	KC_P1, KC_P2, KC_P3, LT(_BLED, KC_PSLS), //LT(_FN, KC_DEL),
	KC_P0, KC_PDOT, LT(_FN2, KC_PENT), LT(_BLED, KC_PAST)),

[_NUMOFF] = LAYOUT_ortho_4x4(
    KC_HOME, KC_UP, KC_PGUP, _______,
    KC_LEFT, XXXXXXX, KC_RGHT, _______,
    KC_END, KC_DOWN, KC_PGDN, _______,
    KC_INS, KC_DEL, _______, _______),

[_FN] = LAYOUT_ortho_4x4(
	KC_F7, KC_F8, KC_F9, KC_F10,
	KC_F4, KC_F5, KC_F6, XXXXXXX,
	KC_F1, KC_F2, KC_F3, _______,
	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

[_FN2] = LAYOUT_ortho_4x4(
	KC_NLCK, KC_PSLS, KC_PAST, S(KC_TAB),
	KC_ESC, _______, WINMAC, KC_TAB,
	_______, _______, _______, KC_BSPC,
	_______, _______, _______, _______),

[_RGB] = LAYOUT_ortho_4x4(
	RGB_TOG, RGB_MOD, RGB_HUI, XXXXXXX,
    RGBRST,  RGB_MODR, RGB_HUD, _______,
	RGB_SAI, XXXXXXX, RGB_VAI, XXXXXXX,
	RGB_SAD, XXXXXXX, RGB_VAD, XXXXXXX),

[_BLED] = LAYOUT_ortho_4x4(
    BL_TOGG, BL_ON, BL_INC, BL_STEP,
    BL_BRTG, BL_OFF, BL_DEC, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

void matrix_init_user(void) {
    #if defined(RGBLIGHT_ENABLE)
	    rgblight_init();
        RGB_current_config = RGB_CONFIG;
    #elif defined(RGB_MATRIX_ENABLE)
        RGB_current_config = RGB_CONFIG;
    #endif
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
                #ifdef RGBLIGHT_ENABLE
                    eeconfig_update_rgblight_default();
                #else
                    eeconfig_update_rgb_matrix_default();
                #endif
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
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.hue = RGB_CONFIG.hue;
                #else
                    RGB_current_config.hsv.h = RGB_CONFIG.hsv.h;
                #endif
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
                #ifdef RGBLIGHT_ENABLE
                    RGB_current_config.hue = RGB_CONFIG.hue;
                #else
                    RGB_current_config.hsv.h = RGB_CONFIG.hsv.h;
                #endif
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
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.sat = RGB_CONFIG.sat;
                #else
                    RGB_current_config.hsv.s = RGB_CONFIG.hsv.s;
                #endif
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
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.sat = RGB_CONFIG.sat;
                #else
                    RGB_current_config.hsv.s = RGB_CONFIG.hsv.s;
                #endif
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
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.val = RGB_CONFIG.val;
                #else
                    RGB_current_config.hsv.v = RGB_CONFIG.hsv.v;
                #endif
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
                #ifdef RGBLIGHT_ENABLE
		            RGB_current_config.val = RGB_CONFIG.val;
                #else
                    RGB_current_config.hsv.v = RGB_CONFIG.hsv.v;
                #endif
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
            rgb_matrix_sethsv_noeeprom(RGB_current_config.hsv.h, RGB_current_config.hsv.s, RGB_current_config.hsv.v);
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

            case _FN2:
                //rgblight_sethsv_noeeprom(HSV_ORANGE);
                //rgblight_mode_noeeprom(1);
		        RGB_momentary_on = true;
		        break;

            case _NUMOFF:
                rgblight_sethsv_noeeprom(HSV_AZURE);
			    rgblight_mode_noeeprom(1);
                break;

            case _RGB:
		        break;

            default:
		        rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
	            rgblight_mode_noeeprom(RGB_current_config.mode);
	            RGB_momentary_on = false;
                break;
	    }
	    return state;
    }

    void led_set_user(uint8_t usb_led) {
         if (!RGB_momentary_on && !MAC_mode){
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

