// Copyright 2022 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdint.h>
#include "color.h"
#include "eeconfig.h"
#include "keycodes.h"
#include "rgblight.h"
#include QMK_KEYBOARD_H

/** NOTE
 * Have to use HSV values to set colour
 */

enum custom_layer {
    _BASE,
    _FN1,
    _RGB,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65_with_macro(
    KC_MUTE, RGB_TOG, KC_ESC,  KC_1,     KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_MPLY,
    KC_F1,   KC_F2,   KC_TAB,  KC_Q,     KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL,
    KC_F3,   KC_F4,   KC_CAPS, KC_A,     KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGUP,
    KC_F5,   KC_F6,   KC_LSFT, KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN,
    KC_F7,   KC_F8,   KC_LCTL, MO(_FN1), KC_LOPT, KC_LCMD, KC_SPC,           KC_RCMD, KC_RCMD, MO(_FN1),KC_RCTL, _______, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    _______, RGB_MOD, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC, _______,
    _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
    _______, _______, EE_CLR,  _______, _______, _______, _______,          _______, _______, _______, EE_CLR, _______, _______, _______, _______
  ),

  [_RGB] = LAYOUT_65_with_macro(
    _______, RGB_MOD, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC, _______,
    _______, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
    _______, _______, EE_CLR,  _______, _______, _______, _______,          _______, _______, _______, EE_CLR, _______, _______, _______, _______
  ),
};

/* TODO - CURRENT TASK: CHANGE COLOUR DEPENDING ON OS
1) OS detection: the keymap should change depending on the OS
    [x] change colour depending on the OS (Apple: white, Windows: blue, linux: green)
        [ ] test that os colour does change depending on where it's plugged (laptop, PC, raspberry pi(?))
    [ ] decide on using a base alpha layer and having mods change depending on OS
     OR have a different base layer for each OS and lock that in as default
2) RGB keybinds: chandelure should change into the RGB context, with knobs doing lighting/animation, etc.
    [ ] make chandelure lead into the RGB layer.
    [ ] test chandelure leads into RGB context
    [ ] get the knobs to change different things. HSV? Brightness?
3) Alternative keybinds: swap ctrl with caps lock, etc.
4) Media control layer?
*/

void eeconfig_init_user(void) {
    printf("cleared eeprom");
}

bool process_detected_host_os_user(os_variant_t detected_os) {
    switch(detected_os) {
        case OS_IOS:
        case OS_MACOS:
            rgblight_sethsv_noeeprom(HSV_WHITE);
            break;
        case OS_WINDOWS:
            rgblight_sethsv_noeeprom(HSV_AZURE);
            break;
        case OS_LINUX:
            rgblight_sethsv_noeeprom(HSV_GREEN);
            break;
        case OS_UNSURE:
            rgblight_sethsv_noeeprom(HSV_RED);
            break;
    }

    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);

    return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_BRIGHTNESS_UP);
        } else {
            tap_code(KC_BRIGHTNESS_DOWN);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }

    return false;
}
