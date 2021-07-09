# attack25

<img src="https://i.imgur.com/pySb3wU.jpg" width="600px">

A 5x5 key pad project.

Keyboard Maintainer: [monksoffunk](https://github.com/monksoffunk)  
Hardware Supported: Attack25 PCB  
Hardware Availability: https://25keys.booth.pm/ and http://www.sho-k.co.uk/tech/590.html

Make example for this keyboard (after setting up your build environment):

If your PCB is rev1.x:

    make 25keys/attack25/rev1:default
    or
    make 25keys/attack25/rev1:via

If your PCB is rev2.x:

    make attack25/attack25/rev2:default
    or
    make attack25/attack25/rev2:via
    
If your PCB is rev3 or rev3.1:

    make 25keys/attack25/rev3:default
    or
    make 25keys/attack25/rev3:via
    
If your PCB is rev3.2 or higher:

    make 25keys/attack25/rev32:default
    or
    make 25keys/attack25/rev32:via
    
Flashing example for this keyboard (rev3 PCB):

    make 25keys/attack25/rev3:default:flash
    or
    make 25keys/attack25/rev3:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

