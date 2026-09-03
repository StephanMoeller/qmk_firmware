// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┐           ┌───┬───┬───┬───┬───┐
     * │ Q │ W │ R │ P │ B │           │ K │ L │ O │ U │ ' │
     * ├───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┤
     * │ F │ A │ S │ T │ G │           │ M │ N │ E │ I │ Y │
     * ├───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┤
     *     │ X │ C │ D │ V │           │ J │ H │ , │ . │
     *     └───┴───┴───┴───┘           └───┴───┴───┴───┘
     *               ┌─────┐           ┌─────┐
     *               │ ENT │           │ SPC │
     *               └─────┘           └─────┘
     */
    [0] = LAYOUT(
        KC_Q,    KC_W,    KC_R,    KC_P,    KC_B,          KC_K,    KC_L,    KC_O,    KC_U,    KC_QUOTE,
        KC_F,    KC_A,    KC_S,    KC_T,    KC_G,          KC_M,    KC_N,    KC_E,    KC_I,    KC_Y,
                 KC_X,    KC_C,    KC_D,    KC_V,          KC_J,    KC_H,    KC_COMMA,KC_DOT,
                                   KC_ENTER,                KC_SPACE
    )
};
