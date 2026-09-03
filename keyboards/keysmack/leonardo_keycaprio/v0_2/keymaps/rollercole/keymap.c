// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_danish.h"
#include "timer.h"

// Ported from qmk_firmware_old/keyboards/rollercole/keymap.c, adapted to
// v0_2's physical layout: 1 thumb key per side (not 3) and 4 keys per side
// on the bottom row (not 5). The dedicated F_KEYS thumb key doesn't fit
// anymore, so F1-F12 now live on the (otherwise empty) left half of
// BS_LAYER (both thumbs held). Whatever sat in the bottom row's now-missing
// column per layer (KC_Z on BASE, DK_BSLS/DK_PIPE on ARROW, TILDE on
// NUMBERS) was dropped rather than relocated.

enum layers {
    BASE,
    ARROW,
    NUMBERS,
    BS_LAYER,  // Both thumbs held: backspace variants + F-keys
    BOOT_LAYER,
    APP_LAUNCH,
};

enum custom_keycodes {
    TUB_1 = SAFE_RANGE,
    TUB_2,
    CTL_PAR_1,
    SFT_PAR_2,
    ALT_TAB,
    ALT_TAB_REV,
    CLOSE_WIN,
    THUMB_LEFT,
    THUMB_RIGHT,
    HAT,
    STICKY_SHIFT,
};

#define _S(kc) MT(MOD_LSFT, kc)
#define _A(kc) MT(MOD_LALT, kc)
#define _C(kc) MT(MOD_LCTL, kc)
#define _W(kc) MT(MOD_LGUI, kc)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        LT(BOOT_LAYER, KC_Q), KC_W,        _W(KC_R),   KC_P,       KC_B,           KC_K,       KC_L,      _W(KC_O),   KC_U,       LT(BOOT_LAYER, DK_QUOT),
        KC_F,                 _A(KC_A),    _C(KC_S),   _S(KC_T),   KC_G,           KC_M,       _S(KC_N),  _C(KC_E),   _A(KC_I),   KC_Y,
                               KC_X,        KC_C,       KC_D,       KC_V,           KC_H,       DK_COMM,   LT(APP_LAUNCH, DK_DOT), DK_MINS,
                                                         THUMB_LEFT,                             THUMB_RIGHT
    ),
    [ARROW] = LAYOUT(
        DK_EXLM,     DK_LABK,   DK_EQL,     DK_RABK,    KC_PERC,        DK_SLSH,    KC_HOME,   KC_UP,      KC_END,     DK_QUES,
        RALT(KC_2),  TUB_1,     CTL_PAR_1,  SFT_PAR_2,  TUB_2,          KC_PGUP,    KC_LEFT,   KC_DOWN,    KC_RIGHT,   KC_PGDN,
                     DK_HASH,   DK_LBRC,    DK_RBRC,    DK_AMPR,        KC_TAB,     DK_DQUO,   DK_COLN,    DK_PLUS,
                                             KC_TRNS,                               KC_TRNS
    ),
    [NUMBERS] = LAYOUT(
        CLOSE_WIN,  ALT_TAB,    KC_TRNS,    ALT_TAB_REV, LALT(KC_PSCR),  DK_DLR,     KC_7,      KC_8,       KC_9,       KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_ESC,     STICKY_SHIFT, KC_APP,        HAT,        _S(KC_4),  _C(KC_5),   _A(KC_6),   KC_TRNS,
                    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_DEL,         KC_1,       KC_2,      KC_3,       KC_TRNS,
                                             KC_TRNS,                                KC_TRNS
    ),
    [BS_LAYER] = LAYOUT(
        KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,          KC_TRNS,    KC_NO,     KC_NO,      KC_NO,      KC_TRNS,
        KC_F6,      KC_F7,      KC_F8,      KC_F9,      KC_F10,         KC_TRNS,    _S(KC_BSPC), _C(KC_BSPC), _A(KC_BSPC), KC_TRNS,
                    KC_F11,     KC_F12,     KC_TRNS,    KC_TRNS,        KC_DEL,     KC_DEL,    KC_DEL,     KC_TRNS,
                                             KC_TRNS,                                KC_TRNS
    ),
    [BOOT_LAYER] = LAYOUT(
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
        KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
                    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,
                                             QK_BOOT,                                QK_BOOT
    ),
    [APP_LAUNCH] = LAYOUT(
        LGUI(KC_7), KC_TRNS,    LGUI(KC_1), LGUI(KC_6), KC_TRNS,        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
        LGUI(KC_4), KC_TRNS,    LGUI(KC_2), LGUI(KC_5), KC_TRNS,        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,    KC_TRNS,
                    KC_TRNS,    LGUI(KC_3), LGUI(KC_8), KC_TRNS,        KC_TRNS,    KC_TRNS,   KC_TRNS,    KC_TRNS,
                                             KC_TRNS,                                KC_TRNS
    ),
};

bool is_pressed(uint16_t mod_keycode) {
    return (get_mods() & (MOD_BIT(mod_keycode)));
}

void ensure_state(uint16_t mod_keycode, bool state) {
    if (is_pressed(mod_keycode) != state) {
        if (state) {
            register_code(mod_keycode);
        } else {
            unregister_code(mod_keycode);
        }
    }
}
void ensure_pressed(uint16_t mod_keycode) {
    ensure_state(mod_keycode, true);
}
void ensure_released(uint16_t mod_keycode) {
    ensure_state(mod_keycode, false);
}

void tap_with_altgr(uint16_t keycode) {
    bool apply_alt = !is_pressed(KC_RALT);
    if (apply_alt) { register_code(KC_RALT); }

    tap_code(keycode);

    if (apply_alt) { unregister_code(KC_RALT); }
}

void tap_with_shift(uint16_t keycode) {
    bool apply_shift = !is_pressed(KC_LSFT);
    if (apply_shift) { register_code(KC_LSFT); }

    tap_code(keycode);

    if (apply_shift) { unregister_code(KC_LSFT); }
}

uint16_t last_pressed_keycode = 0;
uint16_t last_released_keycode = 0;
bool tap_detected = false;
uint16_t last_key_press_time = 0;

uint32_t retro_activate_time = 0;
bool retro_mod_already_pressed = false;
#define RETRO_WITH_MOD(mod_keycode, tap_code) RETRO2(mod_keycode, -1, tap_code)

#define RETRO2(mod_keycode, counterpart_keycode, tap_code) { \
   if (record->event.pressed) { \
       if(!is_pressed(mod_keycode)){\
           register_code(mod_keycode);\
           retro_mod_already_pressed = false;\
       }else{\
           retro_mod_already_pressed = true;\
       }\
       retro_activate_time = timer_read();\
    } else {\
        if(!retro_mod_already_pressed){\
            unregister_code(mod_keycode);\
        }\
        if(timer_read() - retro_activate_time < 250)\
        {\
            if(last_pressed_keycode == keycode || last_pressed_keycode == counterpart_keycode) {\
            tap_code \
            } \
        }; \
    }\
    return false;\
}

bool left_down = false;
bool right_down = false;

void set_layer_state(uint8_t layer, bool state) {
    if (state) {
        layer_on(layer);
    } else {
        layer_off(layer);
    }
}

bool alt_tab_active = false;
bool handle_alt_tab(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Alt tab section
        case ALT_TAB:
        case ALT_TAB_REV:
            alt_tab_active = true;
            if (record->event.pressed == true) {
                ensure_pressed(KC_LALT);
                if (keycode == ALT_TAB_REV) { ensure_pressed(KC_LSFT); }
                tap_code(KC_TAB);
                if (keycode == ALT_TAB_REV) { ensure_released(KC_LSFT); }
            }
            return false;
        case CLOSE_WIN:
            if (record->event.pressed == true) {
                if (alt_tab_active) {
                    ensure_pressed(KC_LCTL);
                    tap_code(KC_W);
                    ensure_released(KC_LCTL);
                } else {
                    ensure_pressed(KC_LALT);
                    tap_code(KC_F4);
                    ensure_released(KC_LALT);
                }
            }
            return false;
        case KC_LSFT:
            return false;
        case _S(KC_4):
            return true;  // Holding down shift while alt+tabbing should be possible without having the alt+tab closed
        default:
            if (alt_tab_active) {
                ensure_released(KC_LALT);
                alt_tab_active = false;
            }
            return true;
    }
}

void update_last_keycodes_and_check_tapped(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        last_pressed_keycode = keycode;
    } else {
        last_released_keycode = keycode;
    }
    uint16_t now = timer_read();
    bool within_tap_period = now - last_key_press_time < 250;
    last_key_press_time = now;

    if (record->event.pressed == false  // key is released
        && last_pressed_keycode == keycode  // key released is the same as last one pressed
        && within_tap_period) {
        tap_detected = true;
    } else {
        tap_detected = false;
    }
}

bool sticky_shift_on = false;

static uint16_t key_timer;
static bool key_held = false;
static int repeat_interval = 0;
static uint16_t keycode_held = 0;
void matrix_scan_user(void) {
    if (key_held && timer_elapsed(key_timer) > repeat_interval) {  // check if the key is still held after 200ms
        tap_code(keycode_held);  // send the key again
        key_timer = timer_read();  // reset the timer
        repeat_interval = 50;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_last_keycodes_and_check_tapped(keycode, record);

    if (!handle_alt_tab(keycode, record)) { return false; }
    switch (keycode) {
        case STICKY_SHIFT:
            if (tap_detected) {
                ensure_pressed(KC_RSFT);
                sticky_shift_on = true;
                set_layer_state(NUMBERS, false);
            }
            return false;
        case KC_UP:
        case KC_DOWN:
        case KC_LEFT:
        case KC_RIGHT:
        case KC_W:
        case KC_B:
            if (record->event.pressed) {
                key_held = true;
                repeat_interval = 100;
                keycode_held = keycode;
                key_timer = timer_read();  // Start the timer when the key is pressed
                tap_code(keycode);  // Tap the key once immediately
            } else {
                key_held = false;  // Key released, stop repeating
            }
            return false;
        case THUMB_LEFT:
        case THUMB_RIGHT:
            if (keycode == THUMB_LEFT) { left_down = record->event.pressed; }
            if (keycode == THUMB_RIGHT) { right_down = record->event.pressed; }

            if (sticky_shift_on && !left_down) {  // Set sticky shift to off, when left_down is released
                sticky_shift_on = false;
                ensure_released(KC_RSFT);
            }

            set_layer_state(NUMBERS, left_down && !sticky_shift_on);
            set_layer_state(ARROW, right_down);  // Right press only: arrow
            set_layer_state(BS_LAYER, left_down && right_down);  // Double press: backspace / F-keys

            if (tap_detected) {
                if (keycode == THUMB_LEFT && right_down) { tap_code(KC_SPACE); }
                if (keycode == THUMB_LEFT && !right_down) { tap_code(KC_ENTER); }
                if (keycode == THUMB_RIGHT && !left_down) { tap_code(KC_SPACE); }
                if (keycode == THUMB_RIGHT && left_down) {
                    if (sticky_shift_on) {
                        tap_code(KC_SPACE);
                    } else {
                        tap_code(KC_0);
                    }
                }
            }

            return false;

        case TUB_1:
            if (record->event.pressed == false) { tap_with_altgr(KC_7); }
            return false;
        case TUB_2:
            if (record->event.pressed == false) { tap_with_altgr(KC_0); }
            return false;
        case CTL_PAR_1:
            RETRO2(KC_LCTL, SFT_PAR_2, tap_with_shift(KC_8);)
            return false;
        case SFT_PAR_2:
            RETRO_WITH_MOD(KC_LSFT, register_code(KC_LSFT); tap_code(KC_9); unregister_code(KC_LSFT);)
            return false;

        // S(DK_DIAE)
        case HAT:
            // Ensure ~ is a single keypress in windows
            if (record->event.pressed == true) {
                tap_code16(S(DK_DIAE));
                tap_code16(S(DK_DIAE));
                tap_code(KC_BSPC);
            }
            return false;
    }

    return true;
}

const uint16_t PROGMEM combo_j[]  = {KC_W, _W(KC_R), COMBO_END};
const uint16_t PROGMEM combo_lo[] = {KC_L, _W(KC_O), COMBO_END};
const uint16_t PROGMEM combo_ou[] = {_W(KC_O), KC_U, COMBO_END};
const uint16_t PROGMEM combo_lu[] = {KC_L, KC_U, COMBO_END};

combo_t key_combos[] = {
    COMBO(combo_j, KC_J),
    COMBO(combo_lo, DK_AE),
    COMBO(combo_ou, DK_ARNG),
    COMBO(combo_lu, DK_OSTR),
};
