/*
 * AWS Keyboard Customization System
 * rgb_matrix_user.h - RGB state machine declarations
 */

#pragma once

#include QMK_KEYBOARD_H

/* State definitions */
typedef enum {
    RGB_STATE_IDLE = 0,
    RGB_STATE_CMD_HELD,
    RGB_STATE_NVIM_MODE,
    RGB_STATE_BROWSER_MODE,
    RGB_STATE_MEDIA_MODE
} rgb_state_t;

/* Public functions */
void rgb_set_state(rgb_state_t state);
rgb_state_t rgb_get_state(void);
void debug_led_cycle(void);
