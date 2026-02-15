#ifdef OLED_ENABLE
#include QMK_KEYBOARD_H
#include <stdio.h>

// Track last pressed key
static char last_key_str[4] = "   ";

void set_last_key(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        // Handle common keys
        if (keycode >= KC_A && keycode <= KC_Z) {
            last_key_str[0] = 'a' + (keycode - KC_A);
            last_key_str[1] = '\0';
        } else if (keycode >= KC_1 && keycode <= KC_0) {
            last_key_str[0] = '1' + (keycode - KC_1);
            last_key_str[1] = '\0';
        } else {
            // Special keys
            switch (keycode) {
                case KC_SPC:  snprintf(last_key_str, sizeof(last_key_str), "SPC"); break;
                case KC_ENT:  snprintf(last_key_str, sizeof(last_key_str), "ENT"); break;
                case KC_BSPC: snprintf(last_key_str, sizeof(last_key_str), "BSP"); break;
                case KC_DEL:  snprintf(last_key_str, sizeof(last_key_str), "DEL"); break;
                case KC_TAB:  snprintf(last_key_str, sizeof(last_key_str), "TAB"); break;
                case KC_ESC:  snprintf(last_key_str, sizeof(last_key_str), "ESC"); break;
                case KC_LEFT: snprintf(last_key_str, sizeof(last_key_str), "<"); break;
                case KC_DOWN: snprintf(last_key_str, sizeof(last_key_str), "v"); break;
                case KC_UP:   snprintf(last_key_str, sizeof(last_key_str), "^"); break;
                case KC_RGHT: snprintf(last_key_str, sizeof(last_key_str), ">"); break;
                case KC_MINS: snprintf(last_key_str, sizeof(last_key_str), "-"); break;
                case KC_EQL:  snprintf(last_key_str, sizeof(last_key_str), "="); break;
                case KC_LBRC: snprintf(last_key_str, sizeof(last_key_str), "["); break;
                case KC_RBRC: snprintf(last_key_str, sizeof(last_key_str), "]"); break;
                case KC_BSLS: snprintf(last_key_str, sizeof(last_key_str), "\\"); break;
                case KC_SCLN: snprintf(last_key_str, sizeof(last_key_str), ";"); break;
                case KC_QUOT: snprintf(last_key_str, sizeof(last_key_str), "'"); break;
                case KC_GRV:  snprintf(last_key_str, sizeof(last_key_str), "`"); break;
                case KC_COMM: snprintf(last_key_str, sizeof(last_key_str), ","); break;
                case KC_DOT:  snprintf(last_key_str, sizeof(last_key_str), "."); break;
                case KC_SLSH: snprintf(last_key_str, sizeof(last_key_str), "/"); break;
                default:      snprintf(last_key_str, sizeof(last_key_str), "?"); break;
            }
        }
    }
}

// Get current RGB mode as 5-char string
const char* get_rgb_mode_name(void) {
    uint8_t mode = rgb_matrix_get_mode();
    switch (mode) {
        // Static/Basic
        case RGB_MATRIX_SOLID_COLOR:             return "SOLID";
        case RGB_MATRIX_ALPHAS_MODS:             return "A-MOD";

        // Gradients
        case RGB_MATRIX_GRADIENT_UP_DOWN:        return "GRD-V";
        case RGB_MATRIX_GRADIENT_LEFT_RIGHT:     return "GRD-H";
        case RGB_MATRIX_BREATHING:               return "BRETH";

        // Band Effects (single color variants)
        case RGB_MATRIX_BAND_SAT:                return "BND-S";
        case RGB_MATRIX_BAND_VAL:                return "BND-V";
        case RGB_MATRIX_BAND_PINWHEEL_SAT:       return "PIN-S";
        case RGB_MATRIX_BAND_PINWHEEL_VAL:       return "PIN-V";
        case RGB_MATRIX_BAND_SPIRAL_SAT:         return "SPR-S";
        case RGB_MATRIX_BAND_SPIRAL_VAL:         return "SPR-V";

        // Rainbow Cycles (full spectrum)
        case RGB_MATRIX_CYCLE_ALL:               return "CYC-A";
        case RGB_MATRIX_CYCLE_LEFT_RIGHT:        return "CYC-H";
        case RGB_MATRIX_CYCLE_UP_DOWN:           return "CYC-V";
        case RGB_MATRIX_CYCLE_OUT_IN:            return "CYC-O";
        case RGB_MATRIX_CYCLE_OUT_IN_DUAL:       return "CYC-D";
        case RGB_MATRIX_CYCLE_PINWHEEL:          return "CYC-P";
        case RGB_MATRIX_CYCLE_SPIRAL:            return "CYC-S";
        case RGB_MATRIX_RAINBOW_MOVING_CHEVRON:  return "CHVRN";

        // Beacons
        case RGB_MATRIX_DUAL_BEACON:             return "BCN-2";
        case RGB_MATRIX_RAINBOW_BEACON:          return "BCN-R";
        case RGB_MATRIX_RAINBOW_PINWHEELS:       return "PINWH";

        // Rain/Drops
        case RGB_MATRIX_RAINDROPS:               return "RAIN ";
        case RGB_MATRIX_JELLYBEAN_RAINDROPS:     return "JELLY";

        // Hue Effects (color shifting)
        case RGB_MATRIX_HUE_BREATHING:           return "H-BRE";
        case RGB_MATRIX_HUE_PENDULUM:            return "H-PND";
        case RGB_MATRIX_HUE_WAVE:                return "H-WAV";

        // Pixel Effects
        case RGB_MATRIX_PIXEL_RAIN:              return "PXRN ";
        case RGB_MATRIX_PIXEL_FLOW:              return "PXFLW";
        case RGB_MATRIX_PIXEL_FRACTAL:           return "PXFRC";

        // Reactive (keypress triggered)
        case RGB_MATRIX_SOLID_REACTIVE_SIMPLE:   return "R-SMP";
        case RGB_MATRIX_SOLID_REACTIVE:          return "REACT";
        case RGB_MATRIX_SOLID_REACTIVE_WIDE:     return "R-WID";
        case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE:return "R-MWD";
        case RGB_MATRIX_SOLID_REACTIVE_CROSS:    return "R-CRS";
        case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS:return"R-MCR";
        case RGB_MATRIX_SOLID_REACTIVE_NEXUS:    return "R-NEX";
        case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS:return"R-MNX";
        case RGB_MATRIX_SPLASH:                  return "SPLSH";
        case RGB_MATRIX_MULTISPLASH:             return "MSPLS";
        case RGB_MATRIX_SOLID_SPLASH:            return "S-SPL";
        case RGB_MATRIX_SOLID_MULTISPLASH:       return "S-MSP";

        default:                               return "-----";
    }
}

void oled_render_master(void) {
    // For vertical displays, use oled_write_P instead of oled_write_ln_P
    // and manually position cursor - all text left-justified

    // Line 0: Layer name (left-justified, no leading spaces)
    oled_set_cursor(0, 0);
    switch (get_highest_layer(layer_state)) {
        case 0: oled_write_P(PSTR("QWRTY"), false); break;
        case 1: oled_write_P(PSTR("NUM  "), false); break;
        case 2: oled_write_P(PSTR("SYM  "), false); break;
        case 3: oled_write_P(PSTR("NAV  "), false); break;
        case 4: oled_write_P(PSTR("FUN  "), false); break;
        case 5: oled_write_P(PSTR("GAME "), false); break;
        default: oled_write_P(PSTR("     "), false); break;
    }

    // Line 1: Spacer (decorative)
    oled_set_cursor(0, 1);
    oled_write_P(PSTR("-----"), false);

    // Line 2: RGB Mode
    oled_set_cursor(0, 2);
    oled_write(get_rgb_mode_name(), false);

    // Line 3: Spacer
    oled_set_cursor(0, 3);
    oled_write_P(PSTR("-----"), false);

    // Line 4: Last Key (centered)
    char key_display[8];
    oled_set_cursor(0, 4);
    // Center single char: " X  ", 2-char: " XX ", 3-char: " XXX"
    if (strlen(last_key_str) == 1) {
        snprintf(key_display, sizeof(key_display), "  %s  ", last_key_str);
    } else if (strlen(last_key_str) == 2) {
        snprintf(key_display, sizeof(key_display), " %s  ", last_key_str);
    } else {
        snprintf(key_display, sizeof(key_display), " %s ", last_key_str);
    }
    oled_write(key_display, false);

    // Line 5: Spacer
    oled_set_cursor(0, 5);
    oled_write_P(PSTR("-----"), false);

    // Line 6-9: Active modifiers (left-justified)
    uint8_t mods = get_mods() | get_oneshot_mods();
    oled_set_cursor(0, 6);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("SHIFT") : PSTR("     "), false);
    oled_set_cursor(0, 7);
    oled_write_P((mods & MOD_MASK_CTRL)  ? PSTR("CTRL ") : PSTR("     "), false);
    oled_set_cursor(0, 8);
    oled_write_P((mods & MOD_MASK_ALT)   ? PSTR("ALT  ") : PSTR("     "), false);
    oled_set_cursor(0, 9);
    oled_write_P((mods & MOD_MASK_GUI)   ? PSTR("GUI  ") : PSTR("     "), false);

    // Line 10: Spacer
    oled_set_cursor(0, 10);
    oled_write_P(PSTR("-----"), false);

    // Line 11-12: Lock indicators (left-justified)
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 11);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS ") : PSTR("     "), false);
    oled_set_cursor(0, 12);
    oled_write_P(led_state.num_lock  ? PSTR("NUM  ") : PSTR("     "), false);

    // Line 13: Spacer
    oled_set_cursor(0, 13);
    oled_write_P(PSTR("-----"), false);

    // Line 14-15: Smiley face ASCII art
    oled_set_cursor(0, 14);
    oled_write_P(PSTR("(^_^)"), false);

    oled_set_cursor(0, 15);
    oled_write_P(PSTR("     "), false);
}

#endif // OLED_ENABLE
