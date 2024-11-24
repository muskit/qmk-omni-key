#pragma once

#ifndef MSK_OMNI
#define MSK_OMNI

#include QMK_KEYBOARD_H

enum msk_keycodes {
    KC_OMNI = QK_KB_7,
};

// how long to wait on omni-key press before action_delay_callback is run
const uint16_t MACRO_TAP_THRESHOLD = 300;

deferred_token omni_callback_token = 0;
int            omni_presses_count  = 0;
bool           omni_btn_held  = false;

// run action based on how omni-key was used
uint32_t action_delay_callback(uint32_t trigger_time, void *cb_arg) {
    switch (omni_presses_count) {
        case 1:
            if (omni_btn_held) {
                tap_code(KC_MUTE);
            } else {
                tap_code(KC_MPLY);
            }
            break;
        case 2:
            tap_code(KC_MNXT);
            break;
        case 3:
            tap_code(KC_MPRV);
            break;
        default:
            tap_code(KC_MUTE);
            break;
    }

    omni_presses_count  = 0;
    omni_callback_token = INVALID_DEFERRED_TOKEN;
    return 0; // if ≠ 0, repeat after n milliseconds. otherwise, end.
}

// handle button event
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_OMNI) {
        omni_btn_held = record->event.pressed;
        if (record->event.pressed) // on key down
        {
            omni_presses_count++;
            if (omni_callback_token == INVALID_DEFERRED_TOKEN)
                omni_callback_token = defer_exec(MACRO_TAP_THRESHOLD, action_delay_callback, NULL);
            else
                extend_deferred_exec(omni_callback_token, MACRO_TAP_THRESHOLD);
        }
        return false; // Skip all further processing of this key
    }
    return true;
}

#endif // MSK_OMNI