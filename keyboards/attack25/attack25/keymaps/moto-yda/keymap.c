#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
  extern rgblight_config_t rgblight_config;
  rgblight_config_t RGB_current_config;
#endif

enum layer_number {
  _NUM = 0,
  _FN,
  _RGB,
  _BLED
};

enum custom_keycodes {
  RGB_MODF = SAFE_RANGE,
  RGB_MODR,
  RGBHINC,
  RGBHDEC,
  RGBSINC,
  RGBSDEC,
  RGBVINC,
  RGBVDEC,
  RGBRST,
  P00
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_NUM] = LAYOUT_ortho_5x5( \
	KC_ESC, KC_F2, LCTL(KC_1), KC_DEL, KC_BSPC, \
	KC_7, KC_8, KC_9, KC_COLN, LT(_FN, KC_HOME), \
	KC_4, KC_5, KC_6, KC_SLSH, LT(_RGB, KC_END), \
	KC_1, KC_2, KC_3, KC_UP, LT(_BLED, KC_PENT), \
	KC_0, SFT_T(KC_DOT), KC_LEFT, KC_DOWN, KC_RGHT),\

[_FN] = LAYOUT_ortho_5x5( \
	KC_F10, KC_F11, KC_F12, KC_TRNS, KC_NLCK, \
	KC_F7, KC_F8, KC_F9, KC_TRNS, XXXXXXX, \
	KC_F4, KC_F5, KC_F6, KC_TRNS, KC_TRNS, \
	KC_F1, KC_F2, KC_F3, KC_TRNS, KC_TRNS, \
	XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS, KC_TRNS), \

[_RGB] = LAYOUT_ortho_5x5( \
	RGB_TOG, RGB_MODF, RGBHINC, RGBSINC, RGBVINC, \
  RGBRST,  RGB_MODR, RGBHDEC, RGBSDEC, RGBVDEC, \
	RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_MODE_RAINBOW, XXXXXXX, XXXXXXX, \
	RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, XXXXXXX, XXXXXXX, \
	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS), \

[_BLED] = LAYOUT_ortho_5x5(
    BL_TOGG, BL_ON, BL_INC, BL_STEP, XXXXXXX,
    BL_BRTG, BL_OFF, BL_DEC, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)
};

bool RGB_momentary_on;

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
	    rgblight_init();
      RGB_current_config = rgblight_config;
    #endif
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
	case RGB_MODF:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed){
		  rgblight_mode_noeeprom(RGB_current_config.mode);
		  rgblight_step();
		  RGB_current_config.mode = rgblight_config.mode;
	  }
    #endif
	  return false;
	  break;
	case RGB_MODR:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed)
	    {
		  rgblight_mode_noeeprom(RGB_current_config.mode);
		  rgblight_step_reverse();
		  RGB_current_config.mode = rgblight_config.mode;
	    }
    #endif
	  return false;
	  break;
	case RGBRST:
    #ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        RGB_current_config = rgblight_config;
	  }
    #endif
	  return false;
	  break;
	case RGBHINC:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
	      rgblight_increase_hue();
		    RGB_current_config.hue = rgblight_config.hue;
	    }
    #endif
    return false;
	  break;
	case RGBHDEC:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
		    rgblight_decrease_hue();
		    RGB_current_config.hue = rgblight_config.hue;
	    }
    #endif
	  return false;
	  break;
	case RGBSINC:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
		    rgblight_increase_sat();
		    RGB_current_config.sat = rgblight_config.sat;
	    }
    #endif
    return false;
	  break;
	case RGBSDEC:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
		    rgblight_decrease_sat();
		    RGB_current_config.sat = rgblight_config.sat;
	    }
    #endif
	  return false;
	  break;
	case RGBVINC:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
		    rgblight_increase_val();
		    RGB_current_config.val = rgblight_config.val;
	    }
    #endif
    return false;
	  break;
	case RGBVDEC:
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
		    rgblight_decrease_val();
		    RGB_current_config.val = rgblight_config.val;
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
    #ifdef RGBLIGHT_ENABLE
	    if (record->event.pressed) {
	      } else {
			  RGB_current_config.mode = rgblight_config.mode;
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


uint32_t layer_state_set_user(uint32_t state) {
  #ifdef RGBLIGHT_ENABLE
	  switch (biton32(state)) {
      case _FN:
        rgblight_sethsv_noeeprom_orange();
        rgblight_mode_noeeprom(1);
		    RGB_momentary_on = true;
		    break;
	    case _RGB:
		    break;
	    default:
		    rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
		    rgblight_mode_noeeprom(RGB_current_config.mode);
		    RGB_momentary_on = false;
        break;
	  }
	#endif
	return state;
}

void led_set_user(uint8_t usb_led) {
	#ifdef RGBLIGHT_ENABLE
    if (!RGB_momentary_on) {
	    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
	      rgblight_sethsv_noeeprom(RGB_current_config.hue, RGB_current_config.sat, RGB_current_config.val);
			  rgblight_mode_noeeprom(RGB_current_config.mode);
	    } else {
		    rgblight_sethsv_noeeprom_azure();
        rgblight_mode_noeeprom(1);
	    }
	  }
	#endif

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {

  } else {

	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {

	} else {

	}

	if (usb_led & (1 << USB_LED_KANA)) {

	} else {

	}

}
