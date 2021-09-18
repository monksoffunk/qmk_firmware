/*
Win OS detect

Caution : experimental phase!!

Copyright 2019 monksoffunk

*/


#include QMK_KEYBOARD_H
#include "windetect.h"
#define OSCHECK_TIME 60000
#define PREOSCHECK_TIME 500
#define NUMCHECK_TIME 500
#define KEYWAIT_TIME 500

uint8_t winos_check(void) {
    static bool mac_mode = true;
    static uint8_t modecheck_step = 0;
    static uint16_t oscheck_timer, keywait_timer;

    switch (modecheck_step) {
        case 0:
            oscheck_timer = timer_read();
            modecheck_step++;
        case 1:
            if (timer_elapsed(oscheck_timer) > PREOSCHECK_TIME) {
                if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                    mac_mode = false;
                    modecheck_step = 5;
                } else {
                    register_code(KC_CAPS);
                    wait_ms(500);
                    unregister_code(KC_CAPS);
                    keywait_timer = timer_read();
                    modecheck_step++;
                }
            }
            break;
        case 2:
            if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) {
                modecheck_step++;
            } else if (timer_elapsed(keywait_timer) > KEYWAIT_TIME) {
                modecheck_step--;
            }
            break;
        case 3:
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                modecheck_step = 5;
                mac_mode = false;
                register_code(KC_CAPS);
                wait_ms(120);
                unregister_code(KC_CAPS);
                break;
            } else {
                register_code(KC_NLCK);
                wait_ms(120);
                unregister_code(KC_NLCK);
                keywait_timer = timer_read();
                modecheck_step++;
            }
        case 4:
            if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) {
                register_code(KC_NLCK);
                register_code(KC_CAPS);
                wait_ms(120);
                unregister_code(KC_NLCK);
                unregister_code(KC_CAPS);
                mac_mode = false;
                modecheck_step++;
            } else if (timer_elapsed(keywait_timer) > NUMCHECK_TIME) {
                modecheck_step = 5;
                register_code(KC_CAPS);
                wait_ms(120);
                unregister_code(KC_CAPS);
            }
            break;
        default:
            break;
    }

    if (timer_elapsed(oscheck_timer) > OSCHECK_TIME) {
        modecheck_step = 5;
    }

    keymap_config.swap_lalt_lgui = !mac_mode;
    return (modecheck_step);
}
