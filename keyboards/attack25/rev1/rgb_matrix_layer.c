//
// Most of the code is shamelessly copied from Drashna's rgb_stuff.c
//

#include "rgb_matrix_layer.h"
#include QMK_KEYBOARD_H

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    #include "lib/lib8tion/lib8tion.h"
    //extern led_config_t g_led_config;
    void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type) {
        HSV hsv = {hue, sat, val};
        if (hsv.v > rgb_matrix_config.hsv.v) {
            hsv.v = rgb_matrix_config.hsv.v;
        }

        switch (mode) {
            case 1:  // breathing
            {
                uint16_t time = scale16by8(g_rgb_counters.tick, speed / 8);
                hsv.v         = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
                RGB rgb       = hsv_to_rgb(hsv);
                for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                    if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                    }
                }
                break;
            }
            default:  // Solid Color
            {
                RGB rgb = hsv_to_rgb(hsv);
                for (uint8_t i = 0; i < DRIVER_LED_TOTAL; i++) {
                    if (HAS_FLAGS(g_led_config.flags[i], led_type)) {
                        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
                    }
                }
                break;
            }
        }
    }

    void rgb_matrix_turnoff(uint8_t led_type) {
        rgb_matrix_layer_helper(0, 0, 0, 0, 0, led_type);
    }
#endif
