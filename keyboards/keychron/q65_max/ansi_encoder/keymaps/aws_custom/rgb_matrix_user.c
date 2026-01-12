/*
 * AWS Keyboard Customization System
 * rgb_matrix_user.c - Per-key RGB feedback implementation
 *
 * LED indices are based on Q65 Max ANSI encoder layout.
 * CRITICAL: Verify indices on physical hardware using debug mode (Fn+D)
 */

#include "rgb_matrix_user.h"

/* =============================================================================
 * LED INDEX DEFINITIONS
 * 
 * Actual indices from Q65 Max ANSI encoder baseline code (ansi_encoder.c)
 * Key Matrix to LED Index mapping verified from g_led_config
 * ============================================================================= */

// Row 0 (Function row)
#define LED_ESC     1
#define LED_1       2
#define LED_2       3
#define LED_3       4
#define LED_4       5

// Row 1 (Number row) 
#define LED_Q       17
#define LED_W       18
#define LED_E       19
#define LED_R       20
#define LED_T       21
#define LED_Y       22
#define LED_U       23
#define LED_I       24
#define LED_O       25
#define LED_P       26

// Row 2 (Home row)
#define LED_A       32
#define LED_S       33
#define LED_D       34
#define LED_F       35
#define LED_G       36
#define LED_H       37
#define LED_J       38
#define LED_K       39
#define LED_L       40

// Row 3 (Bottom alpha row)
#define LED_Z       48
#define LED_X       49
#define LED_C       50
#define LED_V       51
#define LED_B       52
#define LED_N       53
#define LED_M       54

// Row 4 (Bottom row)
#define LED_LCTL    61
#define LED_LCMD    64  // Left Cmd (our prefix key)
#define LED_SPC     65

/* =============================================================================
 * COLOR DEFINITIONS (RGB values)
 * ============================================================================= */

// State: CMD_HELD - Tier 1 keys
#define RGB_AWS_CYAN        0, 200, 200

// State: CMD_HELD - Mode entry keys (N, B, M)
#define RGB_AWS_YELLOW      255, 200, 0

// State: NVIM_MODE
#define RGB_AWS_GREEN       0, 200, 50

// State: BROWSER_MODE
#define RGB_AWS_BLUE        50, 100, 255

// State: MEDIA_MODE
#define RGB_AWS_PURPLE      180, 50, 255

/* =============================================================================
 * LED GROUPS
 * ============================================================================= */

// Tier 1 Navigation keys (H, J, K, L, U, I, O, P)
static const uint8_t leds_tier1_nav[] = {
    LED_H, LED_J, LED_K, LED_L, LED_U, LED_I, LED_O, LED_P
};
#define NUM_TIER1_NAV (sizeof(leds_tier1_nav) / sizeof(leds_tier1_nav[0]))

// Tier 1 Editing keys (A, S, C, V, X, Z, F, G, E, Q, W)
static const uint8_t leds_tier1_edit[] = {
    LED_A, LED_S, LED_C, LED_V, LED_X, LED_Z, LED_F, LED_G, LED_E, LED_Q, LED_W
};
#define NUM_TIER1_EDIT (sizeof(leds_tier1_edit) / sizeof(leds_tier1_edit[0]))

// Tier 1 Number keys (1, 2, 3, 4)
static const uint8_t leds_tier1_nums[] = {
    LED_1, LED_2, LED_3, LED_4
};
#define NUM_TIER1_NUMS (sizeof(leds_tier1_nums) / sizeof(leds_tier1_nums[0]))

// Mode entry keys (N, B, M)
static const uint8_t leds_mode_entry[] = {
    LED_N, LED_B, LED_M
};
#define NUM_MODE_ENTRY (sizeof(leds_mode_entry) / sizeof(leds_mode_entry[0]))

/* =============================================================================
 * STATE MANAGEMENT
 * ============================================================================= */

static rgb_state_t current_rgb_state = RGB_STATE_IDLE;

void rgb_set_state(rgb_state_t state) {
    current_rgb_state = state;
}

rgb_state_t rgb_get_state(void) {
    return current_rgb_state;
}

/* =============================================================================
 * DEBUG LED CYCLING
 * ============================================================================= */

static uint8_t debug_led_index = 0;

void debug_led_cycle(void) {
    // Turn off previous LED
    if (debug_led_index > 0) {
        rgb_matrix_set_color(debug_led_index - 1, 0, 0, 0);
    }
    
    // Light current LED white
    rgb_matrix_set_color(debug_led_index, 255, 255, 255);
    
    // Advance to next LED
    debug_led_index = (debug_led_index + 1) % RGB_MATRIX_LED_COUNT;
}

/* =============================================================================
 * RGB MATRIX INDICATORS CALLBACK
 * 
 * This function is called by QMK after RGB effects are applied.
 * We override specific LEDs based on our state machine.
 * ============================================================================= */

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    
    switch (current_rgb_state) {
        
        case RGB_STATE_IDLE:
            // No custom indicators in idle state
            return false;
        
        case RGB_STATE_CMD_HELD:
            // Clear all LEDs first
            rgb_matrix_set_color_all(0, 0, 0);
            
            // Light Tier 1 navigation keys in CYAN
            for (uint8_t i = 0; i < NUM_TIER1_NAV; i++) {
                rgb_matrix_set_color(leds_tier1_nav[i], RGB_AWS_CYAN);
            }
            
            // Light Tier 1 editing keys in CYAN
            for (uint8_t i = 0; i < NUM_TIER1_EDIT; i++) {
                rgb_matrix_set_color(leds_tier1_edit[i], RGB_AWS_CYAN);
            }
            
            // Light Tier 1 number keys in CYAN
            for (uint8_t i = 0; i < NUM_TIER1_NUMS; i++) {
                rgb_matrix_set_color(leds_tier1_nums[i], RGB_AWS_CYAN);
            }
            
            // Light mode entry keys (N, B, M) in YELLOW
            for (uint8_t i = 0; i < NUM_MODE_ENTRY; i++) {
                rgb_matrix_set_color(leds_mode_entry[i], RGB_AWS_YELLOW);
            }
            
            // Light ESC in CYAN (cancel/escape)
            rgb_matrix_set_color(LED_ESC, RGB_AWS_CYAN);
            
            return true;
        
        case RGB_STATE_NVIM_MODE:
            // Clear all LEDs
            rgb_matrix_set_color_all(0, 0, 0);
            
            // Light active keys in GREEN
            rgb_matrix_set_color(LED_H, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_J, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_K, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_L, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_S, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_V, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_T, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_W, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_Z, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_M, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_1, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_2, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_3, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_4, RGB_AWS_GREEN);
            rgb_matrix_set_color(LED_ESC, RGB_AWS_GREEN);
            
            return true;
        
        case RGB_STATE_BROWSER_MODE:
            // Clear all LEDs
            rgb_matrix_set_color_all(0, 0, 0);
            
            // Light active keys in BLUE
            rgb_matrix_set_color(LED_H, RGB_AWS_BLUE);
            rgb_matrix_set_color(LED_L, RGB_AWS_BLUE);
            rgb_matrix_set_color(LED_D, RGB_AWS_BLUE);
            rgb_matrix_set_color(LED_R, RGB_AWS_BLUE);
            rgb_matrix_set_color(LED_I, RGB_AWS_BLUE);
            rgb_matrix_set_color(LED_P, RGB_AWS_BLUE);
            rgb_matrix_set_color(LED_ESC, RGB_AWS_BLUE);
            
            return true;
        
        case RGB_STATE_MEDIA_MODE:
            // Clear all LEDs
            rgb_matrix_set_color_all(0, 0, 0);
            
            // Light active keys in PURPLE
            rgb_matrix_set_color(LED_SPC, RGB_AWS_PURPLE);
            rgb_matrix_set_color(LED_H, RGB_AWS_PURPLE);
            rgb_matrix_set_color(LED_L, RGB_AWS_PURPLE);
            rgb_matrix_set_color(LED_J, RGB_AWS_PURPLE);
            rgb_matrix_set_color(LED_K, RGB_AWS_PURPLE);
            rgb_matrix_set_color(LED_M, RGB_AWS_PURPLE);
            rgb_matrix_set_color(LED_ESC, RGB_AWS_PURPLE);
            
            return true;
    }
    
    return false;
}
