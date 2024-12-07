# Omni-key for QMK

Custom key function that combines playback controls and mute into a single command. Make that knob button more than just the mute button!

![demo](https://github.com/user-attachments/assets/9ea2e0b5-28e6-4496-b11c-2e440a044a4d)

## Usage

If you've ever used wired headphones with a play/pause button on your phone, this will be familiar to you.

- HOLD: Mute
- TAP: Play/Pause
- TAPx2: Next Track
- TAPx3: Prev Track

## Add to your keymap

### 0. Copy the _omni.h_ file into your keymap folder.

Alternatively, you can add this repo to your keymap folder either as a clone of this repo or as a submodule of a repo for your keymap if you have one. Do make sure you're including _omni.h_ in your keymap properly later on.

### 1. Set the keycode in _omni.h_ (+ optionally, update your definition JSON)

In _omni.h_, you'll find the following block.

```C
enum msk_keycodes {
    KC_OMNI = QK_KB_9,
};
```

`KC_OMNI` is the variable for referencing the omni-key in code. Here, it is set to `QK_KB_9`, which is the constant of the next available custom command for [Monsgeek M1W's QMK VIA code](https://github.com/monsgeek/qmk_firmware/tree/wireless/keyboards/monsgeek/m1w). Substitute this constant for something else, like a another custom command (`QK_KB_n` where `n` is an integer) or `SAFE_RANGE`. **Make sure to adapt to your current keymap.**

If you do want to set it to a `QK_KB` constant for VIA, check your definition JSON to see what index the keycode will be at when you add it. For my Monsgeek M1W, adding the keycode would result in the JSON's `customKeycodes` array being the following:

```JSON
"customKeycodes": [
    { "name": "USB", "title": "USB", "shortName": "DEV USB" },
    { "name": "BT DEV1", "title": "BT Device 1", "shortName": "DEV1" },
    { "name": "BT DEV2", "title": "BT Device 2", "shortName": "DEV2" },
    { "name": "BT DEV3", "title": "BT Device 3", "shortName": "DEV3" },
    { "name": "BT DEV4", "title": "BT Device 4", "shortName": "DEV4" },
    { "name": "BT DEV5", "title": "BT Device 5", "shortName": "DEV5" },
    { "name": "2.4G", "title": "2.4G", "shortName": "DEV 2.4G" },
    { "name": "BATQ", "title": "Battery Check", "shortName": "BATQ" },
    { "name": "WASD", "title": "Swap WASD & Arrow Keys", "shortName": "WASD" },
    { "name": "OMNI", "title": "Media Omni-key", "shortName": "OMNI" } // MY ADDED LINE //
],
```

Thus, I had set my `KC_OMNI` variable to `QK_KB_9`.

### 2. Update your _keymap.c_

In your _keymap.c_, include _omni.h_.

```c
#include "./omni.h"
```

If accessing this repo via cloning/submodule, make sure you include it properly.

```c
#include "./qmk-omni-key/omni.h"
```

> [!IMPORTANT]  
> _omni.h_ defines the `process_record_user` function in order to intercept the omni-key and work as it does. If your _keymap.c_ already defines that function, you may need to make code changes so that it calls the function in _omni.h_ properly. This will be left as an exercise for the user.

Feel free to modify your default mapping by setting a key to `KC_OMNI`.

You should be all set. Compile, flash, and enjoy!

## References

- https://github.com/qmk/qmk_firmware/blob/master/docs/custom_quantum_functions.md
- https://get.vial.today/docs/custom_keycode.html
