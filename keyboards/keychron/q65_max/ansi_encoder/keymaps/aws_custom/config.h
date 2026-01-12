#pragma once

// Custom debounce: 5ms for better responsiveness in coding/terminal workflows
// Override Keychron's default 20ms which is too conservative for AWS use case
#undef DEBOUNCE
#define DEBOUNCE 5

// Tap code delay: Pause between keystrokes in macros
// Critical for Tmux sequences - 50ms works for USB, increase for BT
#define TAP_CODE_DELAY 50

// USB polling rate: 1000Hz = 1ms response time
#define USB_POLLING_INTERVAL_MS 1

// RGB Matrix optimizations
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 0
#define RGB_MATRIX_DEFAULT_VAL 0
#define RGB_DISABLE_WHEN_USB_SUSPENDED

// Disable unused features to save firmware space
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
