# The custom keymap for cassette42

custom keymap example that doesn't use functions in cassette42.c but use its own functions in keymap.c

While cassette42.c has built-in functionality and keymap.c requires almost only keymap definitions, maybe you want to fully customize it yourself.
If you don't want to use functions in cassette42.c, include the line `#define DISABLE_KB_FUNCTIONS` in your `config.h`.
When you want your own layer number enum for your keymap.  `#define CUSTOM_LAYER_NUMBER` in your `config.h`.
