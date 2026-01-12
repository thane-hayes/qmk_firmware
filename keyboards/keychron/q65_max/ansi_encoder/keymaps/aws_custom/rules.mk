# Enable encoder map for rotary knob
ENCODER_MAP_ENABLE = yes

# Disable unused features to reduce size
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no

# Include custom RGB implementation
SRC += rgb_matrix_user.c
