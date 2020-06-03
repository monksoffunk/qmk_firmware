#include "attack25.h"
#include "common/promicro_LED.h"

#ifndef SMD
void keyboard_post_init_kb(void) {
        TX_RX_LED_INIT; //Turn ProMicro LEDs off by default
        RXLED0;
        TXLED0;
        keyboard_post_init_user();
}
#endif
