// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#ifdef PERMISSIVE_HOLD_PER_KEY
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(U_MEDIA,KC_ESC):
        case LT(U_NAV,KC_SPC):
        case LT(U_MOUSE,KC_TAB):
        case LT(U_SYM,KC_ENT):
        case LT(U_NUM,KC_BSPC):
        case LT(U_FUN,KC_DEL):
            // Immediately select the hold action when another key is tapped.
            return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}
#endif

#ifdef TAPPING_TERM_PER_KEY
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
//        case LGUI_T(KC_O):
//            return TAPPING_TERM + 800;
        default:
            return TAPPING_TERM;
    }}
#endif


// Define custom keycodes (max 4-letter suffixes)
enum custom_keycodes {
    OP_UNDO = SAFE_RANGE,
    OP_REDO,
    OP_CUT,
    OP_COPY,
    OP_PAST,
    OP_SAVE,
    OP_SAPP,
    OP_SWIN,
    OP_CLOS,
    TH_ESC_TAB,
    TH_ENT_ALT,
};

static inline void handle_tap_hold(uint16_t tap_key, uint16_t hold_key, keyrecord_t *record) {
    if (record->event.pressed) {
        if (record->tap.count) {
            tap_code16(tap_key);
        } else {
            register_code(hold_key);
        }
    } else {
        unregister_code(hold_key);
    }
}

static inline bool handle_os_shortcut(int mac_key, int win_key, os_variant_t os, keyrecord_t *record) {
    if (record->event.pressed) {
        if (os == OS_MACOS && mac_key >= 0) {
            tap_code16(mac_key);
        } else if (os == OS_WINDOWS && win_key >= 0) {
            tap_code16(win_key);
        } else {
            return true;
        }
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    os_variant_t os = detected_host_os();

    switch (keycode) {
        case LT(0, TH_ESC_TAB):
            handle_tap_hold(KC_ESC, KC_TAB, record);
            return false;

        case LT(0, TH_ENT_ALT):
            handle_tap_hold(KC_ENT, KC_LALT, record);
            return false;

        case OP_UNDO:
            return handle_os_shortcut(LGUI(KC_Z), LCTL(KC_Z), os, record);

        case OP_REDO:
            return handle_os_shortcut(SGUI(KC_Z), LCTL(KC_Y), os, record);

        case OP_CUT:
            return handle_os_shortcut(LGUI(KC_X), LCTL(KC_X), os, record);

        case OP_COPY:
            return handle_os_shortcut(LGUI(KC_C), LCTL(KC_C), os, record);

        case OP_PAST:
            return handle_os_shortcut(LGUI(KC_V), LCTL(KC_V), os, record);

        case OP_SAVE:
            return handle_os_shortcut(LGUI(KC_S), LCTL(KC_S), os, record);

        case OP_SAPP:
            return handle_os_shortcut(LGUI(KC_TAB), LALT(KC_TAB), os, record);

        case OP_SWIN:
            return handle_os_shortcut(LGUI(KC_TILD), -1, os, record);

        case OP_CLOS:
            return handle_os_shortcut(LGUI(KC_Q), LALT(KC_F4), os, record);
    }

    return true;
}


const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R',
                       '*', '*', '*',  '*', '*', '*'
    );
