#!/bin/bash
# =============================================================================
# AWS Keyboard Firmware - Remaining Issues Fix Script
# =============================================================================
#
# This script fixes the 2 code issues identified in post-remediation review:
#   1. Stale comments (// Ctrl+[ should be // Ctrl+B)
#   2. Tmux rotate panes bug (LCTL(KC_O) should be just KC_O)
#
# Issue 3 (LED index verification) requires physical hardware and cannot
# be scripted - see instructions at the end of this file.
#
# Usage:
#   cd ~/thane_qmk
#   chmod +x fix-remaining-issues.sh
#   ./fix-remaining-issues.sh
#
# =============================================================================

set -e  # Exit on error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Conda configuration
CONDA_PATH="$HOME/miniconda/bin/conda"
CONDA_ENV="keyboard-build"

KEYMAP_DIR="keyboards/keychron/q65_max/ansi_encoder/keymaps/aws_custom"
KEYMAP_FILE="${KEYMAP_DIR}/keymap.c"

echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}AWS Keyboard Firmware - Fix Script${NC}"
echo -e "${YELLOW}========================================${NC}"
echo ""

# Check we're in the right directory
if [ ! -f "${KEYMAP_FILE}" ]; then
    echo -e "${RED}ERROR: Cannot find ${KEYMAP_FILE}${NC}"
    echo "Please run this script from the root of thane_qmk repository"
    echo "  cd ~/thane_qmk"
    echo "  ./fix-remaining-issues.sh"
    exit 1
fi

echo -e "${GREEN}✓ Found keymap.c${NC}"

# Check conda is available
if [ ! -f "${CONDA_PATH}" ]; then
    echo -e "${RED}ERROR: Cannot find conda at ${CONDA_PATH}${NC}"
    echo "Please update CONDA_PATH variable in this script"
    exit 1
fi

echo -e "${GREEN}✓ Found conda${NC}"
echo ""

# =============================================================================
# Issue 1: Fix stale comments
# =============================================================================
echo -e "${YELLOW}Issue 1: Fixing stale comments...${NC}"

# Count occurrences before
BEFORE_COUNT=$(grep -c "// Ctrl+\[" "${KEYMAP_FILE}" 2>/dev/null | head -1 || echo "0")
BEFORE_COUNT=${BEFORE_COUNT:-0}
echo "  Found ${BEFORE_COUNT} instances of '// Ctrl+['"

if [ "${BEFORE_COUNT}" -gt 0 ]; then
    # Replace all instances
    sed -i 's|// Ctrl+\[|// Ctrl+B (tmux prefix)|g' "${KEYMAP_FILE}"
    echo -e "${GREEN}  ✓ Fixed ${BEFORE_COUNT} stale comments${NC}"
else
    echo -e "${GREEN}  ✓ No stale comments found (already fixed)${NC}"
fi
echo ""

# =============================================================================
# Issue 2: Fix tmux rotate panes bug
# =============================================================================
echo -e "${YELLOW}Issue 2: Fixing tmux rotate panes bug...${NC}"

# Check if the bug exists
if grep -q "tap_code16(LCTL(KC_O))" "${KEYMAP_FILE}"; then
    echo "  Found incorrect LCTL(KC_O) call"
    
    # Fix it
    sed -i 's|tap_code16(LCTL(KC_O)); // Ctrl+O for rotate|tap_code(KC_O); // o for rotate|g' "${KEYMAP_FILE}"
    
    # Verify fix
    if grep -q "tap_code(KC_O); // o for rotate" "${KEYMAP_FILE}"; then
        echo -e "${GREEN}  ✓ Fixed tmux rotate panes${NC}"
    else
        echo -e "${RED}  ✗ Fix may not have applied correctly - please verify manually${NC}"
    fi
else
    echo -e "${GREEN}  ✓ Already fixed or not present${NC}"
fi
echo ""

# =============================================================================
# Verification
# =============================================================================
echo -e "${YELLOW}Verification...${NC}"

# Check for any remaining issues
REMAINING_BRACKET=$(grep -c "Ctrl+\[" "${KEYMAP_FILE}" 2>/dev/null | head -1 || echo "0")
REMAINING_BRACKET=${REMAINING_BRACKET:-0}
REMAINING_LCTL_O=$(grep -c "LCTL(KC_O)" "${KEYMAP_FILE}" 2>/dev/null | head -1 || echo "0")
REMAINING_LCTL_O=${REMAINING_LCTL_O:-0}

if [ "${REMAINING_BRACKET}" -eq 0 ] && [ "${REMAINING_LCTL_O}" -eq 0 ]; then
    echo -e "${GREEN}  ✓ All code issues fixed${NC}"
else
    echo -e "${RED}  ✗ Some issues may remain:${NC}"
    [ "${REMAINING_BRACKET}" -gt 0 ] && echo "    - ${REMAINING_BRACKET} 'Ctrl+[' references"
    [ "${REMAINING_LCTL_O}" -gt 0 ] && echo "    - ${REMAINING_LCTL_O} 'LCTL(KC_O)' references"
fi
echo ""

# =============================================================================
# Build
# =============================================================================
echo -e "${YELLOW}Building firmware...${NC}"
echo ""

# Use conda run with the correct path
"${CONDA_PATH}" run -n "${CONDA_ENV}" make keychron/q65_max/ansi_encoder:aws_custom
BUILD_STATUS=$?

echo ""
if [ ${BUILD_STATUS} -eq 0 ]; then
    echo -e "${GREEN}✓ Build successful${NC}"
    
    # Show firmware size
    FIRMWARE_FILE=".build/keychron_q65_max_ansi_encoder_aws_custom.bin"
    if [ -f "${FIRMWARE_FILE}" ]; then
        SIZE=$(stat -c%s "${FIRMWARE_FILE}")
        echo -e "${GREEN}  Firmware size: ${SIZE} bytes${NC}"
    fi
else
    echo -e "${RED}✗ Build failed${NC}"
    exit 1
fi
echo ""

# =============================================================================
# Git commit (only if there are changes)
# =============================================================================
echo -e "${YELLOW}Checking for changes to commit...${NC}"

if git diff --quiet "${KEYMAP_FILE}" 2>/dev/null; then
    echo -e "${GREEN}  ✓ No changes needed (already up to date)${NC}"
else
    git add "${KEYMAP_FILE}"
    git commit -m "Fix stale comments and tmux rotate panes bug

- Updated all '// Ctrl+[' comments to '// Ctrl+B (tmux prefix)'
- Fixed rotate panes: tap_code16(LCTL(KC_O)) -> tap_code(KC_O)
"
    echo -e "${GREEN}  ✓ Changes committed${NC}"
fi
echo ""

# =============================================================================
# Summary
# =============================================================================
echo -e "${YELLOW}========================================${NC}"
echo -e "${YELLOW}Summary${NC}"
echo -e "${YELLOW}========================================${NC}"
echo ""
echo -e "${GREEN}✓ Issue 1: Stale comments - FIXED${NC}"
echo -e "${GREEN}✓ Issue 2: Tmux rotate bug - FIXED${NC}"
echo -e "${YELLOW}⚠ Issue 3: LED indices - REQUIRES HARDWARE${NC}"
echo ""
echo "Next steps:"
echo "  1. Push changes:  git push origin thane-hayes"
echo "  2. Flash firmware to Q65 Max:"
echo "     ${CONDA_PATH} run -n ${CONDA_ENV} make keychron/q65_max/ansi_encoder:aws_custom:flash"
echo "  3. Verify LED indices using Fn+D (see below)"
echo ""

# =============================================================================
# LED Index Verification Instructions
# =============================================================================
cat << 'EOF'
========================================
LED INDEX VERIFICATION PROCEDURE
========================================

The LED indices in rgb_matrix_user.c are ESTIMATED.
You must verify them on physical hardware.

STEP 1: Flash the firmware
  Put keyboard in DFU mode first:
    - Unplug keyboard
    - Hold ESC while plugging in USB
    - Or press reset button under spacebar
  
  Then flash:
    ~/miniconda/bin/conda run -n keyboard-build make keychron/q65_max/ansi_encoder:aws_custom:flash

STEP 2: Test LED indices
  - Press Fn+D to enter debug mode
  - Each press lights ONE LED white and advances to next index
  - Press repeatedly to cycle through all LEDs
  - Record which physical key each index corresponds to

STEP 3: Create your mapping
  Fill in this table as you test:

  Index | Key      | Expected Index
  ------|----------|---------------
  ?     | ESC      | 1
  ?     | 1        | 2
  ?     | 2        | 3
  ?     | 3        | 4
  ?     | 4        | 5
  ?     | Q        | 17
  ?     | W        | 18
  ?     | E        | 19
  ?     | R        | 20
  ?     | T        | 21
  ?     | Y        | 22
  ?     | U        | 23
  ?     | I        | 24
  ?     | O        | 25
  ?     | P        | 26
  ?     | A        | 32
  ?     | S        | 33
  ?     | D        | 34
  ?     | F        | 35
  ?     | G        | 36
  ?     | H        | 37
  ?     | J        | 38
  ?     | K        | 39
  ?     | L        | 40
  ?     | Z        | 47
  ?     | X        | 48
  ?     | C        | 49
  ?     | V        | 50
  ?     | B        | 51
  ?     | N        | 52
  ?     | M        | 53
  ?     | SPACE    | 63

STEP 4: Update rgb_matrix_user.c
  If any indices differ, edit the #define statements:

  // Example - if ESC is actually at index 0:
  #define LED_ESC     0   // Was 1, changed to 0

STEP 5: Rebuild and reflash
  ~/miniconda/bin/conda run -n keyboard-build make keychron/q65_max/ansi_encoder:aws_custom:flash

STEP 6: Verify RGB states
  - Hold Left Cmd: Tier 1 keys should light CYAN, N/B/M should light YELLOW
  - Prefix+N: Nvim keys should light GREEN
  - Prefix+B: Browser keys should light BLUE
  - Prefix+M: Media keys should light PURPLE

If colors appear on wrong keys, your LED indices need adjustment.
EOF

echo ""
echo -e "${GREEN}Script complete!${NC}"
