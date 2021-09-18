#include "attack25.h"
#include "common/promicro_LED.h"

#ifndef KEYBOARD_attack25_attack25_rev3
void keyboard_post_init_kb(void) {
        TX_RX_LED_INIT; //Turn ProMicro LEDs off by default
        RXLED0;
        TXLED0;
        keyboard_post_init_user();
}
#endif
