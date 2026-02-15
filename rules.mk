LTO_ENABLE = no             # Disable Link Time Optimization for LED config
BOOTMAGIC_ENABLE = no       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = no        # Disable WS2812 RGB underlight (use RGB_MATRIX instead)
RGB_MATRIX_ENABLE = yes     # Enable per-key RGB matrix lighting
RGB_MATRIX_DRIVER = ws2812  # Use WS2812 driver for RGB Matrix
SWAP_HANDS_ENABLE = no      # Enable one-hand typing
OLED_ENABLE = yes           # OLED display
WPM_ENABLE = yes            # WPM tracking for animations and stats

# Bootloader selection
BOOTLOADER = rp2040

# Source files
SRC += rgb_config.c         # RGB LED layout configuration
SRC += oled_master.c        # Master (left) OLED display
SRC += oled_slave.c         # Slave (right) OLED display with Bongo Cat
