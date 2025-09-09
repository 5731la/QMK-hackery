// Copyright 2023 Andrew Kannan (@awkannan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "print.h"


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
    KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   ENC_PRESS,
    KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_DEL,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,
    KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENTER, KC_PSCR,
    KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_NUM,
    KC_LCTL,  KC_LGUI,  KC_LALT,                      KC_SPC,                                 MO(1),    KC_RCTL,  KC_RALT,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  [1] = LAYOUT_all(
    _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, OLED_TOGG,
    _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, CLOCK_SET,
    _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______,
    _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    QK_BOOT, _______,   _______,                   _______,                            _______, _______, _______, _______, _______, _______
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uprintf("OS: %d", detected_host_os());
    uprintf("Custom keycode detected: %d\n", keycode);

    // Check if the key combination is in the custom keycodes enum
    //if (!(keycode >= CTRL_Z && keycode < END_OF_ENUM)) {
    //    return true; // Not a custom keycode, return true to allow default processing
    //}


    if (!record->event.pressed) {
        return true; // Only process on key press
    }


    switch (detected_host_os()) {
        case OS_IOS:
        case OS_MACOS:
            // avoid C limitation
            if (false) {}
            uint8_t mods = get_mods();
            bool alt = mods & MOD_MASK_ALT;
            bool ctrl = mods & MOD_MASK_CTRL;
            bool shift = mods & MOD_MASK_SHIFT;
            bool gui = mods & MOD_MASK_GUI;

            // Detect if a normal letter key (A-Z) is being pressed
            if (keycode >= KC_A && keycode <= KC_Z) {
                // Handle Ctrl+Z, Ctrl+X, Ctrl+C, Ctrl+V, Ctrl+W, Ctrl+T, Ctrl+Y, Ctrl+A, Ctrl+S, Ctrl+F, Ctrl+/
                if (ctrl && !alt && !gui) {
                    //clear_keyboard();
                unregister_code(KC_LCTL); // Prevents double sending of Ctrl
                    switch (keycode) {
                        case KC_Z:
                            SEND_STRING(SS_LGUI("z"));
                            break;
                        case KC_X:
                            SEND_STRING(SS_LGUI("x"));
                            break;
                        case KC_C:
                            SEND_STRING(SS_LGUI("c"));
                            break;
                        case KC_V:
                            SEND_STRING(SS_LGUI("v"));
                            break;
                        case KC_W:
                            SEND_STRING(SS_LGUI("w"));
                            break;
                        case KC_T:
                            SEND_STRING(SS_LGUI("t"));
                            break;
                        case KC_Y:
                            SEND_STRING(SS_LGUI("y"));
                            break;
                        case KC_A:
                            SEND_STRING(SS_LGUI("a"));
                            break;
                        case KC_S:
                            SEND_STRING(SS_LGUI("s"));
                            break;
                        case KC_F:
                            SEND_STRING(SS_LGUI("f"));
                            break;
                        case KC_SLASH:
                            SEND_STRING(SS_LGUI("/"));
                            break;
                        case KC_N:
                            SEND_STRING(SS_LGUI("n"));
                            break;
                        case KC_P:
                            SEND_STRING(SS_LGUI("p"));
                            break;
                        default:
                            register_code(KC_LCTL); // Re-register Ctrl for other keys
                            return true; // Allow default processing for unsupported keys
                    }
                register_code(KC_LCTL); // Re-register Ctrl for other keys
                    return false;
                }
            }

            // Alt+F4
            if (keycode == KC_F4) {
                if (alt && !ctrl && !shift && !gui) {
                    unregister_code(KC_LALT); // Prevents double sending of Alt
                    SEND_STRING(SS_LGUI(SS_TAP(X_Q)));
                    register_code(KC_LALT); // Re-register Alt for other keys
                    return false;
                }
            }

            // Ctrl+backspace (delete word)
            if (keycode == KC_BSPC) {
                if (ctrl && !alt && !shift && !gui) {
                    unregister_code(KC_LCTL); // Prevents double sending of Ctrl
                    SEND_STRING(SS_LALT(SS_TAP(X_BSPC)));
                    register_code(KC_LCTL); // Re-register Ctrl for other keys
                    return false;
                }

            }

            // Cmd+L to Cmd+ctrl+Q
            if (keycode == KC_L) {
                if (!ctrl && !alt && !shift && gui) {
                    SEND_STRING(SS_LCTL(SS_TAP(X_Q)));
                    return false; // Prevent default processing
                }
            }

            // handle ctrl+arrow keys for word navigation, also set alt+left/right for home/end
            if (keycode == KC_LEFT || keycode == KC_RGHT) {
                if (ctrl && !alt && !shift && !gui) {
                    unregister_code(KC_LCTL); // Prevents double sending of Ctrl
                    switch (keycode) {
                        case KC_LEFT:
                            SEND_STRING(SS_LALT(SS_TAP(X_LEFT)));
                            break; // Prevent default processing
                        case KC_RGHT:
                            SEND_STRING(SS_LALT(SS_TAP(X_RGHT)));
                            break; // Prevent default processing
                    }
                    register_code(KC_LCTL); // Re-register Ctrl for other keys
                    return false;
                } else if (alt && !ctrl && !shift && !gui) {
                    unregister_code(KC_LALT); // Prevents double sending of Ctrl
                    switch (keycode) {
                        case KC_LEFT:
                            SEND_STRING(SS_LGUI(SS_TAP(X_LEFT)));
                            break; // Prevent default processing
                        case KC_RGHT:
                            SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
                            break; // Prevent default processing
                    }
                    register_code(KC_LALT); // Re-register Alt for other keys
                    return false; // Prevent default processing
                }
            }
            // handle alt+up/down for page up/down
            if (keycode == KC_UP || keycode == KC_DOWN) {
                if (!ctrl && alt && !shift && !gui) {
                    unregister_code(KC_LALT);
                    switch (keycode) {
                    case KC_UP:
                        SEND_STRING(SS_TAP(X_PGUP));
                        break;
                    case KC_DOWN:
                        SEND_STRING(SS_TAP(X_PGDN));
                        break;
                    }
                    register_code(KC_LALT);
                    return false;
                }
            }
            return true; // Allow default processing for other keys
        default:
            return true; // Unsupported OS, allow default processing
    }
}

