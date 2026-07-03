/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include "os_detection.h"

enum custom_keycodes {
  CU_FIND = SAFE_RANGE,
  CU_UNDO,
  CU_CUT,
  CU_COPY,
  CU_PASTE,
  CU_TOGOS,
};

enum os_override {
  OS_OVERRIDE_AUTO = 0,
  OS_OVERRIDE_MAC,
  OS_OVERRIDE_LINUX,
};

typedef union {
  uint32_t raw;
  struct {
    uint8_t os_override :2;
  };
} user_config_t;

user_config_t user_config;

void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();
}

bool is_mac_mode(void) {
  switch (user_config.os_override) {
    case OS_OVERRIDE_MAC:
      return true;
    case OS_OVERRIDE_LINUX:
      return false;
    default:
      return detected_host_os() == OS_MACOS || detected_host_os() == OS_IOS;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
LT(3, KC_TAB),  KC_SCLN,  KC_COMM,  KC_DOT,  KC_P,  KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_LCTL),  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                       KC_D,    KC_H,    KC_T,    KC_N,   KC_S,   KC_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,  KC_QUOT,  KC_Q,    KC_J,    KC_K,    KC_X,                        KC_B,    KC_M,    KC_W,    KC_V,   KC_Z,   RSFT_T(KC_SLASH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  KC_SPC,     KC_SPC,   LT(2, KC_ENT), KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX,  KC_UP,  XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      CU_FIND, CU_UNDO, KC_LSFT, KC_LALT, KC_LGUI, XXXXXXX,         XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BRID, KC_BRIU, CU_CUT, CU_PASTE, CU_COPY, KC_KB_VOLUME_DOWN,            KC_KB_VOLUME_UP, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_SPC,   MO(4), KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_EXLM,  KC_AT,  KC_LPRN,  KC_RPRN, KC_PERC,                     KC_EQL,  KC_PPLS, KC_PMNS, KC_PAST, KC_NO,   KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,                      KC_EXLM, KC_HASH, KC_SLSH, KC_BSLS, KC_PIPE, KC_DLR,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,                      XXXXXXX, KC_GRV,  KC_CIRC, KC_AT,   KC_AMPR, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(4),  KC_SPC,     KC_SPC, KC_TRNS, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,  XXXXXXX,                       KC_PLUS, KC_1,    KC_2,    KC_3,    KC_MINS, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,  XXXXXXX,                       KC_PAST, KC_4,    KC_5,    KC_6,    KC_SLSH, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12, XXXXXXX,                       XXXXXXX, KC_7,    KC_8,    KC_9,    KC_0,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_SPC, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [4] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, CU_TOGOS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      UG_NEXT, UG_HUED, UG_SATD, UG_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_DVORAK 0
#define L_NAVIGATE 2
#define L_SYMBOLS 4
#define L_NUMPAD 8
#define L_ADJUST 16

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_DVORAK:
            oled_write_ln_P(PSTR("Dvorak"), false);
            break;
        case L_NAVIGATE:
            oled_write_ln_P(PSTR("Navigate"), false);
            break;
        case L_SYMBOLS:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case L_NUMPAD:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
    }
}

void oled_render_os_mode(void) {
    oled_write_P(PSTR("OS: "), false);
    switch (user_config.os_override) {
        case OS_OVERRIDE_MAC:
            oled_write_ln_P(PSTR("Mac (forced)"), false);
            break;
        case OS_OVERRIDE_LINUX:
            oled_write_ln_P(PSTR("Linux (forced)"), false);
            break;
        default:
            if (is_mac_mode()) {
                oled_write_ln_P(PSTR("Mac (auto)"), false);
            } else {
                oled_write_ln_P(PSTR("Linux (auto)"), false);
            }
            break;
    }
}


char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

bool oled_task_user(void) {
    oled_render_layer_state();
    if (is_keyboard_master()) {
        oled_render_os_mode();
        oled_render_keylog();
    }
    return false;
}
#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
#endif

  switch (keycode) {
    case CU_FIND:
      if (record->event.pressed) {
        tap_code16(is_mac_mode() ? LGUI(KC_F) : LCTL(KC_F));
      }
      return false;
    case CU_UNDO:
      if (record->event.pressed) {
        tap_code16(is_mac_mode() ? LGUI(KC_Z) : LCTL(KC_Z));
      }
      return false;
    case CU_CUT:
      if (record->event.pressed) {
        tap_code16(is_mac_mode() ? LGUI(KC_X) : LCTL(KC_X));
      }
      return false;
    case CU_COPY:
      if (record->event.pressed) {
        tap_code16(is_mac_mode() ? LGUI(KC_C) : LCTL(KC_C));
      }
      return false;
    case CU_PASTE:
      if (record->event.pressed) {
        tap_code16(is_mac_mode() ? LGUI(KC_V) : LCTL(KC_V));
      }
      return false;
    case CU_TOGOS:
      if (record->event.pressed) {
        user_config.os_override = (user_config.os_override + 1) % 3;
        eeconfig_update_user(user_config.raw);
      }
      return false;
  }
  return true;
}
