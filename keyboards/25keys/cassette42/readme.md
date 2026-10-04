# Cassette42

![cassette42](https://pbs.twimg.com/media/D63q5S0UcAE9Rfj?format=jpg&name=large)

An audio control pad with 4 switches and 2 rotary encoders.

* Keyboard Maintainer: [monksoffunk](https://github.com/monksoffunk)  [@monksoffunkJP](https://twitter.com/monksoffunkJP)
* Hardware Supported: Cassette 42 PCB
* Hardware Availability: [Yushakobo Shop](https://yushakobo.jp/shop/cassette42/)

Make example for this keyboard (after setting up your build environment):

    make cassette42:default

Make example for this keyboard using a Pro Micro RP2040-compatible controller:

    make 25keys/cassette42:default CONVERT_TO=promicro_rp2040

QMK CLI example for this keyboard using a Pro Micro RP2040-compatible controller:

    qmk compile -kb 25keys/cassette42 -km default -e CONVERT_TO=promicro_rp2040

Unless you have a specific reason to use another keymap, the `via` keymap is recommended because it supports Remap:

The `via` keymap supports Remap:

    make 25keys/cassette42:via CONVERT_TO=promicro_rp2040

    qmk compile -kb 25keys/cassette42 -km via -e CONVERT_TO=promicro_rp2040

The `via` keymap also includes a DJ mode. The layers from Layer 6 (DJ) through Layer 11 (RGB MODE) are special-purpose layers for the built-in controls. It is recommended not to change these layers in Remap. Layers 0 through 5 are available for customization.

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
