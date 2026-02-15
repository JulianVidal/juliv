#pragma once

#ifdef OLED_ENABLE

// Initialize master OLED display
void oled_render_master(void);

// Track max WPM
void oled_update_wpm(void);

// Track last pressed key for display
void set_last_key(uint16_t keycode, keyrecord_t *record);

#endif
