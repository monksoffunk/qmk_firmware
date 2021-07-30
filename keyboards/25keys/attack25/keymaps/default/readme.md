# The rev3_VIA Attack25 Layout for rev3 PCB
## Layout

### Default Layer

```
                        S(Tab) Tab  ENCCCW  ENCCW
 ,-----------------------------.             
 |NumLk|  /  |  *  |  -  | Esc |             
 |-----+-----+-----+-----+-----|
 |  7  |  8  |  9  |  +  |ScrLk|  ScrLk momentary on...FN Layer
 |-----+-----+-----+-----+-----|
 |  4  |  5  |  6  |BkTab|PrtSc|  PrtSc momentary on...RGB Layer
 |-----+-----+-----+-----+-----|
 |  1  |  2  |  3  |Enter| Del |  Del momentary on...BLED Layer
 |-----+-----+-----+-----+-----|
 |  0  | 00  |  .  |Enter|BkSpc|  BackSpace momentary on...SP Layer
 `------------------------------
```                               Enter momentary on...NUMOFF Layer

### NUMOFF Layer

```
                        S(Tab) Tab  ENCCCW  ENCCW
 ,-----------------------------.             
 |     |     |     |     |ENRST| ENCODER_Lock Reset            
 |-----+-----+-----+-----+-----|
 | Home|  Up | PgUp|     |     |
 |-----+-----+-----+-----+-----|
 | Left|     |Right|     |     |
 |-----+-----+-----+-----+-----|
 | End | Down| PgDn|     |     |
 |-----+-----+-----+-----+-----|
 | Ins |     | Del |     |     |
 `------------------------------
```
 
 ### FN Layer

```
                        Vol- Vol+  ENCCCW  ENCCW
 ,-----------------------------.             
 | F10 | F11 | F12 |     |ENCLK|             
 |-----+-----+-----+-----+-----|
 |  F7 |  F8 |  F9 |     |     |
 |-----+-----+-----+-----+-----|
 |  F4 |  F5 |  F6 |     |     |
 |-----+-----+-----+-----+-----|
 |  F1 |  F2 |  F3 |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 `------------------------------
```
 
### RGB Layer

```
                        MODR MODF  ENCCCW  ENCCW
 ,-----------------------------.             
 | TOG | MODF| HINC|     |ENCLK|             
 |-----+-----+-----+-----+-----|
 | RST | MODR| HDEC|     |     |
 |-----+-----+-----+-----+-----|
 | VINC| SINC| SPI |     |     |
 |-----+-----+-----+-----+-----|
 | VDEC| SDEC| SPD |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 `------------------------------
```

### BLED Layer

```
                         BL- BL+  ENCCCW  ENCCW
 ,-----------------------------.             
 |     |     | BL+ | BLCY|ENCLK|             
 |-----+-----+-----+-----+-----|
 | BRTG|     | BL- |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 |-----+-----+-----+-----+-----|
 |RESET|     |     |     |     |
 `------------------------------
```

### SP Layer

```
                         Ctl-Z Ctl-Y  ENCCCW  ENCCW
 ,-----------------------------.             
 |     |     |     |     |ENCLK|             
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 |-----+-----+-----+-----+-----|
 |     |     |     |     |     |
 |-----+-----+-----+-----+-----|
 |RESET|     |     |     |     |
 `------------------------------
```

## Build

Run the command according to the revision of the PCB.
For rev1.x PCB:

```
$ make 25keys/attack25/rev1:via
```

Build for rev3.2 PCB and flash the firmware:

```
$ make 25keys/attack25/rev32:default:flash
```
