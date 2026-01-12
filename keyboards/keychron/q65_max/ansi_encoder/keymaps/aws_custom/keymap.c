/* Copyright 2023 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "keychron_common.h"

enum custom_keycodes {
    KC_AWS_MAC = SAFE_RANGE,  // Our custom Mac mode switch
    KC_AWS_WIN,               // Our custom Windows mode switch
    KC_DEBUG_LED,             // Debug LED cycling
};

// Modal states
enum modal_state {
    STATE_IDLE,
    STATE_NVIM_MODE,
    STATE_BROWSER_MODE,
    STATE_MEDIA_MODE,
};
enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    FN2
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_73(
        KC_MUTE,     KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_DEL,
        MC_2,        KC_TAB,   KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_HOME,
        MC_3,        KC_CAPS,  KC_A,    KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_PGUP,
        MC_4,        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,   KC_PGDN,
        MC_5,        KC_LCTL,  KC_LOPTN,KC_LCMMD,                            KC_SPC,                             KC_RCMMD, MO(MAC_FN1),MO(FN2),KC_LEFT, KC_DOWN, KC_RGHT),

    [WIN_BASE] = LAYOUT_ansi_73(
        KC_MUTE,     KC_ESC,   KC_1,    KC_2,     KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,          KC_DEL,
        MC_2,        KC_TAB,   KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,          KC_HOME,
        MC_3,        KC_CAPS,  KC_A,    KC_S,     KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT,            KC_ENT,           KC_PGUP,
        MC_4,        KC_LSFT,           KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,            KC_RSFT, KC_UP,   KC_PGDN,
        MC_5,        KC_LCTL,  KC_LGUI, KC_LALT,                             KC_SPC,                             KC_RALT,  MO(WIN_FN1),MO(FN2),KC_LEFT, KC_DOWN, KC_RGHT),

    [MAC_FN1] = LAYOUT_ansi_73(
        RGB_TOG,     KC_GRV,  KC_BRID,  KC_BRIU,  KC_MCTRL,KC_LNPAD,RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          _______,
        _______,     _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,  _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,     RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,     _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, NK_TOGG, _______, _______, _______,  _______,            _______, _______, _______,
        _______,     _______, _______,  _______,                             _______,                            _______,  _______,  _______,  _______, _______, _______),

    [WIN_FN1] = LAYOUT_ansi_73(
        RGB_TOG,     KC_GRV,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FILE, RGB_VAD, RGB_VAI, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,          _______,
        _______,     _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,  _______, _______, _______, _______, _______, _______,  _______,  _______,   _______,          _______,
        _______,     RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,     _______,           RGB_RMOD, RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, NK_TOGG, _______, _______, _______,  _______,            _______, _______, _______,
        _______,     _______, _______,  _______,                             _______,                            _______,  _______,  _______,  _______, _______, _______),

    [FN2] = LAYOUT_ansi_73(
        _______,    _______, _______,  _______,   _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,  _______,          _______,
        _______,    _______, _______,  KC_AWS_WIN,_______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______,   _______,          _______,
        _______,    _______, _______,  _______,   KC_DEBUG_LED, _______, _______, _______, _______, _______, _______, _______,  _______,            _______,          _______,
        _______,    _______,           _______,   _______, _______, _______, _______, _______, KC_AWS_MAC, _______, _______, _______,            _______, _______, _______,
        _______,    _______, _______,  _______,                              _______,                            _______,  _______,  _______,  _______, _______, _______)
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MAC_FN1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [WIN_FN1]  = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [FN2]      = {ENCODER_CCW_CW(_______, _______)},
};
#endif // ENCODER_MAP_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Keep Keychron's default processing
    if (!process_record_keychron_common(keycode, record)) {
        return false;
    }
    
    // AWS Custom overrides
    static bool prefix_held = false;
    static bool is_mac_mode = true;  // Default to Mac
    static enum modal_state current_state = STATE_IDLE;
    static bool eeprom_loaded = false;
    
    // Load OS mode from EEPROM on first run
    if (!eeprom_loaded) {
        uint8_t saved_mode = eeconfig_read_kb();
        is_mac_mode = (saved_mode == 1);
        eeprom_loaded = true;
    }
    
    // OS Mode Switching
    if (keycode == KC_AWS_MAC && record->event.pressed) {
        is_mac_mode = true;
        eeconfig_update_kb(is_mac_mode ? 1 : 0);  // Save to EEPROM
        // TODO: Use is_mac_mode for OS-specific shortcuts
        return false;
    }
    if (keycode == KC_AWS_WIN && record->event.pressed) {
        is_mac_mode = false;
        eeconfig_update_kb(is_mac_mode ? 1 : 0);  // Save to EEPROM
        // TODO: Use is_mac_mode for OS-specific shortcuts  
        return false;
    }
    
    // Debug LED cycling
    if (keycode == KC_DEBUG_LED && record->event.pressed) {
        static uint8_t debug_index = 0;
        // Cycle through LED indices for hardware verification
        rgb_matrix_set_color(debug_index, RGB_WHITE);
        wait_ms(500);
        rgb_matrix_set_color(debug_index, RGB_OFF);
        debug_index = (debug_index + 1) % RGB_MATRIX_LED_COUNT;
        return false;
    }
    
    // Intercept Left Cmd as our prefix key
    if (keycode == KC_LCMMD) {
        if (record->event.pressed) {
            prefix_held = true;
            // Set RGB to indicate prefix mode
            rgb_matrix_sethsv_noeeprom(HSV_BLUE);
        } else {
            prefix_held = false;
            // Reset RGB based on current state
            if (current_state == STATE_IDLE) {
                rgb_matrix_sethsv_noeeprom(HSV_OFF);
            }
        }
        return false; // Don't send Left Cmd to host
    }
    
    // If prefix not held, let default behavior handle it
    if (!prefix_held) {
        return true;
    }
    
    // Prefix IS held - handle custom shortcuts
    if (record->event.pressed) {
        // Mode entry keys
        if (current_state == STATE_IDLE) {
            switch (keycode) {
                case KC_N: // Enter Nvim mode
                    current_state = STATE_NVIM_MODE;
                    rgb_matrix_sethsv_noeeprom(HSV_GREEN);
                    return false;
                case KC_B: // Enter Browser mode
                    current_state = STATE_BROWSER_MODE;
                    rgb_matrix_sethsv_noeeprom(HSV_ORANGE);
                    return false;
                case KC_M: // Enter Media mode
                    current_state = STATE_MEDIA_MODE;
                    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);
                    return false;
            }
        }
        
        // Handle modal shortcuts
        if (current_state == STATE_NVIM_MODE) {
            switch (keycode) {
                case KC_H: // Tmux pane left
                    tap_code16(LCTL(KC_LBRC)); // Ctrl+[
                    wait_ms(50);
                    tap_code(KC_H);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_J: // Tmux pane down
                    tap_code16(LCTL(KC_LBRC)); // Ctrl+[
                    wait_ms(50);
                    tap_code(KC_J);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_K: // Tmux pane up
                    tap_code16(LCTL(KC_LBRC)); // Ctrl+[
                    wait_ms(50);
                    tap_code(KC_K);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_L: // Tmux pane right
                    tap_code16(LCTL(KC_LBRC)); // Ctrl+[
                    wait_ms(50);
                    tap_code(KC_L);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_S: // Split horizontal
                    tap_code16(LCTL(KC_LBRC)); // Ctrl+[
                    wait_ms(50);
                    tap_code16(LSFT(KC_QUOT)); // "
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_V: // Split vertical
                    tap_code16(LCTL(KC_LBRC)); // Ctrl+[
                    wait_ms(50);
                    tap_code16(LSFT(KC_5)); // %
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_ESC: // Exit mode
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
            }
        } else if (current_state == STATE_BROWSER_MODE) {
            switch (keycode) {
                case KC_H: // Browser back
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_LBRC)); // Mac: Cmd+[
                    } else {
                        tap_code16(LALT(KC_LEFT)); // Windows: Alt+Left
                    }
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_L: // Browser forward
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_RBRC)); // Mac: Cmd+]
                    } else {
                        tap_code16(LALT(KC_RIGHT)); // Windows: Alt+Right
                    }
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_R: // Hard reload
                    if (is_mac_mode) {
                        tap_code16(LGUI(LSFT(KC_R))); // Mac: Cmd+Shift+R
                    } else {
                        tap_code16(LCTL(LSFT(KC_R))); // Windows: Ctrl+Shift+R
                    }
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_ESC: // Exit mode
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
            }
        } else if (current_state == STATE_MEDIA_MODE) {
            switch (keycode) {
                case KC_SPC: // Play/Pause
                    tap_code(KC_MPLY);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_H: // Previous track
                    tap_code(KC_MPRV);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_L: // Next track
                    tap_code(KC_MNXT);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_J: // Volume down
                    tap_code(KC_VOLD);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_K: // Volume up
                    tap_code(KC_VOLU);
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
                case KC_ESC: // Exit mode
                    current_state = STATE_IDLE;
                    rgb_matrix_sethsv_noeeprom(HSV_OFF);
                    return false;
            }
        }
        
        // Default shortcuts (when in idle state)
        if (current_state == STATE_IDLE) {
            switch (keycode) {
                case KC_H: // Left arrow
                    tap_code(KC_LEFT);
                    return false;
                case KC_J: // Down arrow  
                    tap_code(KC_DOWN);
                    return false;
                case KC_K: // Up arrow
                    tap_code(KC_UP);
                    return false;
                case KC_L: // Right arrow
                    tap_code(KC_RIGHT);
                    return false;
                case KC_U: // Line start
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_LEFT));  // Mac: Cmd+Left
                    } else {
                        tap_code(KC_HOME);          // Windows: Home
                    }
                    return false;
                case KC_I: // Word left
                    if (is_mac_mode) {
                        tap_code16(LALT(KC_LEFT));  // Mac: Alt+Left
                    } else {
                        tap_code16(LCTL(KC_LEFT));  // Windows: Ctrl+Left
                    }
                    return false;
                case KC_O: // Word right
                    if (is_mac_mode) {
                        tap_code16(LALT(KC_RIGHT)); // Mac: Alt+Right
                    } else {
                        tap_code16(LCTL(KC_RIGHT)); // Windows: Ctrl+Right
                    }
                    return false;
                case KC_P: // Line end
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_RIGHT)); // Mac: Cmd+Right
                    } else {
                        tap_code(KC_END);           // Windows: End
                    }
                    return false;
                case KC_C: // Copy (OS-specific)
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_C));  // Mac: Cmd+C
                    } else {
                        tap_code16(LCTL(KC_C));  // Windows: Ctrl+C
                    }
                    return false;
                case KC_V: // Paste
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_V));  // Mac: Cmd+V
                    } else {
                        tap_code16(LCTL(KC_V));  // Windows: Ctrl+V
                    }
                    return false;
                case KC_X: // Cut
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_X));  // Mac: Cmd+X
                    } else {
                        tap_code16(LCTL(KC_X));  // Windows: Ctrl+X
                    }
                    return false;
                case KC_S: // Save
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_S));  // Mac: Cmd+S
                    } else {
                        tap_code16(LCTL(KC_S));  // Windows: Ctrl+S
                    }
                    return false;
                case KC_A: // Select All
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_A));  // Mac: Cmd+A
                    } else {
                        tap_code16(LCTL(KC_A));  // Windows: Ctrl+A
                    }
                    return false;
                case KC_Q: // Quit application
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_Q));     // Mac: Cmd+Q
                    } else {
                        tap_code16(LALT(KC_F4));    // Windows: Alt+F4
                    }
                    return false;
                case KC_W: // Close tab/window
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_W));     // Mac: Cmd+W
                    } else {
                        tap_code16(LCTL(KC_W));     // Windows: Ctrl+W
                    }
                    return false;
                case KC_1: // Tab 1
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_1));     // Mac: Cmd+1
                    } else {
                        tap_code16(LCTL(KC_1));     // Windows: Ctrl+1
                    }
                    return false;
                case KC_2: // Tab 2
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_2));     // Mac: Cmd+2
                    } else {
                        tap_code16(LCTL(KC_2));     // Windows: Ctrl+2
                    }
                    return false;
                case KC_3: // Tab 3
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_3));     // Mac: Cmd+3
                    } else {
                        tap_code16(LCTL(KC_3));     // Windows: Ctrl+3
                    }
                    return false;
                case KC_4: // Tab 4
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_4));     // Mac: Cmd+4
                    } else {
                        tap_code16(LCTL(KC_4));     // Windows: Ctrl+4
                    }
                    return false;
                case KC_F: // Find
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_F));     // Mac: Cmd+F
                    } else {
                        tap_code16(LCTL(KC_F));     // Windows: Ctrl+F
                    }
                    return false;
                case KC_G: // Find next
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_G));     // Mac: Cmd+G
                    } else {
                        tap_code(KC_F3);            // Windows: F3
                    }
                    return false;
                case KC_Z: // Undo
                    if (is_mac_mode) {
                        tap_code16(LGUI(KC_Z));     // Mac: Cmd+Z
                    } else {
                        tap_code16(LCTL(KC_Z));     // Windows: Ctrl+Z
                    }
                    return false;
                case KC_E: // Escape
                    tap_code(KC_ESC);
                    return false;
            }
        }
    }
    
    return true;
}
