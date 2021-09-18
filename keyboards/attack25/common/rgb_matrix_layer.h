void rgb_matrix_layer_helper(uint8_t hue, uint8_t sat, uint8_t val, uint8_t mode, uint8_t speed, uint8_t led_type);
void rgb_matrix_turnoff(uint8_t led_type);

#if defined(RGB_MATRIX_ENABLE)
    #define rgb_sethsv_noeeprom rgb_matrix_sethsv_noeeprom
    #define RGB_current_config_hue  RGB_current_config.hsv.h
    #define RGB_current_config_sat  RGB_current_config.hsv.s
    #define RGB_current_config_val  RGB_current_config.hsv.v
    #define RGB_CONFIG_hue RGB_CONFIG.hsv.h
    #define RGB_CONFIG_sat RGB_CONFIG.hsv.s
    #define RGB_CONFIG_val RGB_CONFIG.hsv.v
    #define RGB_CONFIG rgb_matrix_config
    #define RGB_CONFIG_t rgb_config_t
    #define eeconfig_update_rgblight_default    eeconfig_update_rgb_matrix_default
#elif defined(RGBLIGHT_ENABLE)
    #define rgb_sethsv_noeeprom rgblight_sethsv_noeeprom
    #define RGB_current_config_hue  RGB_current_config.hue
    #define RGB_current_config_sat  RGB_current_config.sat
    #define RGB_current_config_val  RGB_current_config.val
    #define RGB_CONFIG_hue RGB_CONFIG.hue
    #define RGB_CONFIG_sat RGB_CONFIG.sat
    #define RGB_CONFIG_val RGB_CONFIG.val
    #define RGB_CONFIG rgblight_config
    #define RGB_CONFIG_t rgblight_config_t
#endif
