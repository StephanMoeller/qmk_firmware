// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "keymap_danish.h"

enum layers {
    _BASE,
    _ARROWS,
    _NUM,
    _BOTH,
};

enum custom_keycodes {
    ALT_TAB = SAFE_RANGE,
};

enum tap_dances {
    TD_GUI_EQL,
    TD_ALT_LCBR,
    TD_CTL_LPRN,
    TD_SFT_RPRN,
    TD_CTL_DQUO,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_GUI_EQL]  = ACTION_TAP_DANCE_DOUBLE(DK_EQL, KC_LGUI),
    [TD_ALT_LCBR] = ACTION_TAP_DANCE_DOUBLE(DK_LCBR, KC_LALT),
    [TD_CTL_LPRN] = ACTION_TAP_DANCE_DOUBLE(DK_LPRN, KC_LCTL),
    [TD_SFT_RPRN] = ACTION_TAP_DANCE_DOUBLE(DK_RPRN, KC_LSFT),
    [TD_CTL_DQUO] = ACTION_TAP_DANCE_DOUBLE(DK_DQUO, KC_LCTL),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * BASE
     * ┌───┬───┬───┬───┬───┐           ┌───┬───┬───┬───┬───┐
     * │ Q │ W │R/G│ P │ B │           │ K │ L │O/G│ U │ ' │
     * ├───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┤
     * │ F │A/A│S/C│T/S│ G │           │ M │N/S│E/C│I/A│ Y │
     * ├───┼───┼───┼───┼───┤           ├───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ D │ V │           │ J │ H │ , │ . │BOOT│
     * └───┴───┴───┴───┴───┘           └───┴───┴───┴───┴───┘
     *           ┌─────┬─────┐       ┌─────┬─────┐
     *           │  O  │ENT/N│       │SPC/A│  I  │
     *           └─────┴─────┘       └─────┴─────┘
     * (X/M = tap X, hold modifier M: G=gui A=alt C=ctl S=sft N=NUM ARROWS)
     */
    [_BASE] = LAYOUT(
        DK_Q,    DK_W,          LGUI_T(DK_R),   DK_P,    DK_B,                DK_K,    DK_L,          LGUI_T(DK_O),   DK_U,    DK_QUOT,
        DK_F,    LALT_T(DK_A),  LCTL_T(DK_S),   LSFT_T(DK_T), DK_G,           DK_M,    LSFT_T(DK_N),  LCTL_T(DK_E),   LALT_T(DK_I), DK_Y,
        DK_Z,    DK_X,          DK_C,           DK_D,    DK_V,                DK_J,    DK_H,          DK_COMM,        DK_DOT,  QK_BOOT,
                                 DK_O,           LT(_NUM, KC_ENT),             LT(_ARROWS, KC_SPC),    DK_I
    ),

    /*
     * ARROWS (hold right thumb)
     */
    [_ARROWS] = LAYOUT(
        DK_EXLM, DK_LABK,           TD(TD_GUI_EQL),  DK_RABK,           DK_PERC,             DK_SLSH, KC_HOME, KC_UP,   KC_END,  KC_APP,
        DK_AT,   TD(TD_ALT_LCBR),   TD(TD_CTL_LPRN), TD(TD_SFT_RPRN),   DK_RCBR,             KC_PGUP, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
        KC_TRNS, DK_HASH,           DK_LBRC,         DK_RBRC,           KC_TRNS,             KC_TRNS, KC_TAB,  TD(TD_CTL_DQUO), KC_ESC, KC_TRNS,
                                    KC_TRNS,          LT(_NUM, KC_SPC),                       KC_TRNS, KC_TRNS
    ),

    /*
     * NUM (hold left thumb)
     */
    [_NUM] = LAYOUT(
        KC_TRNS,      ALT_TAB,   DK_R,    KC_TRNS, KC_TRNS,              KC_TRNS, KC_7,          KC_8,          KC_9,          KC_TRNS,
        LGUI(KC_LEFT),LCTL(DK_Z),KC_TRNS, LCTL(DK_Y), LGUI(KC_RGHT),     KC_TRNS, LSFT_T(KC_4),  LCTL_T(KC_5),  LALT_T(KC_6),  DK_PLUS,
        KC_TRNS,      KC_ESC,    LCTL(DK_C), KC_DEL, KC_TRNS,            DB_TOGG, KC_1,          KC_2,          KC_3,          KC_TRNS,
                                  KC_TRNS,   KC_TRNS,                     LT(_ARROWS, KC_0),      KC_TRNS
    ),

    /*
     * BOTH (hold both thumbs)
     */
    [_BOTH] = LAYOUT(
        KC_VOLU, KC_F7,          KC_F8,          KC_F9,          KC_F10,       DK_TILD, KC_SPC,         KC_SPC,         KC_SPC,         DK_GRV,
        KC_VOLD, KC_F4,          LCTL_T(KC_F5),  LSFT_T(KC_F6),  KC_F11,       DK_DLR,  LSFT_T(KC_BSPC),LCTL_T(KC_BSPC),LALT_T(KC_BSPC),KC_TRNS,
        KC_TRNS, KC_F1,          KC_F2,          KC_F3,          KC_F12,       DK_CIRC, KC_DEL,         KC_DEL,         KC_DEL,         KC_TRNS,
                                 KC_TRNS,        KC_TRNS,                      DK_0,                    KC_TRNS
    ),
};

// ---------------------------------------------------------------------------
// Tri-layer (NUM + ARROWS held together => BOTH), matching zig's on_event
// left_held/right_held tracking, but via the standard QMK tri-layer idiom.
// ---------------------------------------------------------------------------
layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(layer_state, _NUM) && !layer_state_cmp(state, _NUM)) {
        // Leaving NUM: make sure a held Alt from ALT_TAB doesn't get stuck.
        if (get_mods() & MOD_BIT(KC_LALT)) {
            unregister_code(KC_LALT);
        }
    }
    return update_tri_layer_state(state, _NUM, _ARROWS, _BOTH);
}

// ---------------------------------------------------------------------------
// ALT_TAB: hold Alt across repeated taps, like zig's CUSTOM_TAP_ALT_TAB.
// ---------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ALT_TAB:
            if (record->event.pressed) {
                if (!(get_mods() & MOD_BIT(KC_LALT))) {
                    register_code(KC_LALT);
                }
                tap_code(KC_TAB);
            }
            return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// Per-key tapping term: GUI home-row mods on R/O get a longer term, like zig.
// ---------------------------------------------------------------------------
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(DK_R):
        case LGUI_T(DK_O):
            return 750;
        default:
            return TAPPING_TERM;
    }
}

// ---------------------------------------------------------------------------
// Combos
// ---------------------------------------------------------------------------
enum combo_events {
    C_J_WR,
    C_HOLDMOD_BASE_AS,
    C_HOLDMOD_BASE_ST,
    C_HOLDMOD_NUM_ST,
    C_HOLDMOD_NUM_AS,
    C_HOLDMOD_ARROWS_ST,
    C_ALT_F4_BOTH,
    C_BOOT_VJ,
    C_BOOT_QB,
    C_BOOT_KQUOT,
    C_AE,
    C_OSTR,
    C_ARNG,
    C_QUES_ARROWS,
    C_EXLM_ARROWS,
    C_EXLM_BOTH,
    C_HOLDMOD_BASE_EI,
    C_PLUS_ARROWS,
    C_MINS_NUM,
    C_PIPE_ARROWS,
    C_BSLS_ARROWS,
    C_EQCOL_ARROWS,
    C_MNXT_BOTH,
    C_MPRV_BOTH,
};

const uint16_t PROGMEM combo_j_wr[]             = {DK_W, LGUI_T(DK_R), COMBO_END};
const uint16_t PROGMEM combo_holdmod_base_as[]  = {LALT_T(DK_A), LCTL_T(DK_S), COMBO_END};
const uint16_t PROGMEM combo_holdmod_base_st[]  = {LCTL_T(DK_S), LSFT_T(DK_T), COMBO_END};
const uint16_t PROGMEM combo_holdmod_num_st[]   = {LCTL_T(DK_S), LCTL(DK_Y), COMBO_END};
const uint16_t PROGMEM combo_holdmod_num_as[]   = {LGUI(KC_LEFT), LCTL_T(DK_S), COMBO_END};
const uint16_t PROGMEM combo_holdmod_arrows_st[]= {TD(TD_CTL_LPRN), TD(TD_SFT_RPRN), COMBO_END};
const uint16_t PROGMEM combo_alt_f4_both[]      = {LSFT_T(KC_F6), LSFT_T(KC_BSPC), COMBO_END};
const uint16_t PROGMEM combo_boot_vj[]          = {DK_V, DK_J, COMBO_END};
const uint16_t PROGMEM combo_boot_qb[]          = {DK_Q, DK_B, COMBO_END};
const uint16_t PROGMEM combo_boot_kquot[]       = {DK_K, DK_QUOT, COMBO_END};
const uint16_t PROGMEM combo_ae[]               = {DK_L, LGUI_T(DK_O), COMBO_END};
const uint16_t PROGMEM combo_ostr[]             = {DK_L, DK_U, COMBO_END};
const uint16_t PROGMEM combo_arng[]             = {LGUI_T(DK_O), DK_U, COMBO_END};
const uint16_t PROGMEM combo_ques_arrows[]      = {KC_UP, KC_END, COMBO_END};
const uint16_t PROGMEM combo_exlm_arrows[]      = {DK_LABK, TD(TD_GUI_EQL), COMBO_END};
const uint16_t PROGMEM combo_exlm_both[]        = {KC_F7, KC_F8, COMBO_END};
const uint16_t PROGMEM combo_holdmod_base_ei[]  = {LCTL_T(DK_E), LALT_T(DK_I), COMBO_END};
const uint16_t PROGMEM combo_plus_arrows[]      = {KC_DOWN, KC_RGHT, COMBO_END};
const uint16_t PROGMEM combo_mins_num[]         = {LCTL_T(KC_5), LALT_T(KC_6), COMBO_END};
const uint16_t PROGMEM combo_pipe_arrows[]      = {KC_LEFT, KC_DOWN, COMBO_END};
const uint16_t PROGMEM combo_bsls_arrows[]      = {DK_HASH, DK_LBRC, COMBO_END};
const uint16_t PROGMEM combo_eqcol_arrows[]     = {DK_LABK, DK_RABK, COMBO_END};
const uint16_t PROGMEM combo_mnxt_both[]        = {LCTL_T(KC_F5), LSFT_T(KC_F6), COMBO_END};
const uint16_t PROGMEM combo_mprv_both[]        = {KC_F4, LCTL_T(KC_F5), COMBO_END};

combo_t key_combos[] = {
    [C_J_WR]              = COMBO(combo_j_wr, DK_J),
    [C_HOLDMOD_BASE_AS]   = COMBO_ACTION(combo_holdmod_base_as),
    [C_HOLDMOD_BASE_ST]   = COMBO_ACTION(combo_holdmod_base_st),
    [C_HOLDMOD_NUM_ST]    = COMBO_ACTION(combo_holdmod_num_st),
    [C_HOLDMOD_NUM_AS]    = COMBO_ACTION(combo_holdmod_num_as),
    [C_HOLDMOD_ARROWS_ST] = COMBO_ACTION(combo_holdmod_arrows_st),
    [C_ALT_F4_BOTH]       = COMBO(combo_alt_f4_both, LALT(KC_F4)),
    [C_BOOT_VJ]           = COMBO(combo_boot_vj, QK_BOOT),
    [C_BOOT_QB]           = COMBO(combo_boot_qb, QK_BOOT),
    [C_BOOT_KQUOT]        = COMBO(combo_boot_kquot, QK_BOOT),
    [C_AE]                = COMBO(combo_ae, DK_AE),
    [C_OSTR]              = COMBO(combo_ostr, DK_OSTR),
    [C_ARNG]              = COMBO(combo_arng, DK_ARNG),
    [C_QUES_ARROWS]       = COMBO(combo_ques_arrows, DK_QUES),
    [C_EXLM_ARROWS]       = COMBO(combo_exlm_arrows, DK_EXLM),
    [C_EXLM_BOTH]         = COMBO(combo_exlm_both, DK_EXLM),
    [C_HOLDMOD_BASE_EI]   = COMBO_ACTION(combo_holdmod_base_ei),
    [C_PLUS_ARROWS]       = COMBO(combo_plus_arrows, DK_PLUS),
    [C_MINS_NUM]          = COMBO(combo_mins_num, DK_MINS),
    [C_PIPE_ARROWS]       = COMBO(combo_pipe_arrows, DK_PIPE),
    [C_BSLS_ARROWS]       = COMBO(combo_bsls_arrows, DK_BSLS),
    [C_EQCOL_ARROWS]      = COMBO_ACTION(combo_eqcol_arrows),
    [C_MNXT_BOTH]         = COMBO(combo_mnxt_both, KC_MNXT),
    [C_MPRV_BOTH]         = COMBO(combo_mprv_both, KC_MPRV),
};

// A handful of combos behave like a mod-tap: tap the chord quickly to send a
// plain key, hold it to apply a modifier to whatever is typed next. Mirrors
// zig's Combo_Tap_HoldMod combos.
typedef struct {
    uint16_t tap_keycode;
    uint8_t  hold_mods;
} combo_hold_mod_t;

static const combo_hold_mod_t combo_hold_mod_table[6] = {
    [0] = {DK_Z,       MOD_BIT(KC_RCTL) | MOD_BIT(KC_RALT)}, // base A+S
    [1] = {DK_V,       MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)}, // base S+T
    [2] = {LCTL(DK_V), MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)}, // num S+T
    [3] = {LCTL(DK_X), MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)}, // num A+S
    [4] = {DK_AMPR,    MOD_BIT(KC_LCTL) | MOD_BIT(KC_LSFT)}, // arrows S+T
    [5] = {DK_MINS,    MOD_BIT(KC_LCTL) | MOD_BIT(KC_LALT)}, // base E+I
};

static bool     combo_hold_active[6]   = {false};
static bool     combo_hold_resolved[6] = {false};
static uint16_t combo_hold_timer[6];

void process_combo_event(uint16_t combo_index, bool pressed) {
    int8_t slot = -1;
    switch (combo_index) {
        case C_HOLDMOD_BASE_AS:   slot = 0; break;
        case C_HOLDMOD_BASE_ST:   slot = 1; break;
        case C_HOLDMOD_NUM_ST:    slot = 2; break;
        case C_HOLDMOD_NUM_AS:    slot = 3; break;
        case C_HOLDMOD_ARROWS_ST: slot = 4; break;
        case C_HOLDMOD_BASE_EI:   slot = 5; break;
        case C_EQCOL_ARROWS:
            if (pressed) {
                tap_code16(KC_SPC);
                tap_code16(DK_COLN);
                tap_code16(DK_EQL);
                tap_code16(KC_SPC);
            }
            return;
        default:
            return;
    }

    if (pressed) {
        combo_hold_active[slot]   = true;
        combo_hold_resolved[slot] = false;
        combo_hold_timer[slot]    = timer_read();
    } else {
        combo_hold_active[slot] = false;
        if (combo_hold_resolved[slot]) {
            unregister_mods(combo_hold_mod_table[slot].hold_mods);
        } else {
            tap_code16(combo_hold_mod_table[slot].tap_keycode);
        }
    }
}

void matrix_scan_user(void) {
    for (uint8_t i = 0; i < 6; i++) {
        if (combo_hold_active[i] && !combo_hold_resolved[i] && timer_elapsed(combo_hold_timer[i]) > TAPPING_TERM) {
            register_mods(combo_hold_mod_table[i].hold_mods);
            combo_hold_resolved[i] = true;
        }
    }
}
