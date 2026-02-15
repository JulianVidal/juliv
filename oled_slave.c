#include QMK_KEYBOARD_H
#include "oled_slave.h"
#include "animation_frames.h"  // Bongo Cat animation data

#ifdef OLED_ENABLE

// Bongo Cat Animation - WPM-responsive
#define IDLE_SPEED 20   // below this wpm value your animation will idle
#define TAP_SPEED 40    // above this wpm value typing animation to trigger
#define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms

static uint32_t anim_timer = 0;
// static uint8_t current_idle_frame = 0;  // Unused - idle is now static
static uint8_t current_tap_frame = 0;
static uint8_t last_wpm = 1;  // Start non-zero so idle frame renders on boot (wpm starts at 0)

// Render slave side OLED (right side - Bongo Cat)
void oled_render_slave(void) {
    bool cat_rendered = false;
    // Update animation frame based on timer
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        
        // Select and render animation based on WPM
        uint8_t wpm = get_current_wpm();
        if (wpm <= IDLE_SPEED) {
            // Idle - show static frame, only write once
            // current_idle_frame = (current_idle_frame + 1) % IDLE_FRAMES;  // Old cycling animation
            // oled_write_raw_P(idle[abs((IDLE_FRAMES - 1) - current_idle_frame)], ANIM_SIZE);
            if (last_wpm != 0) {  // Only write when transitioning to idle
                oled_write_raw_P(idle[0], ANIM_SIZE);
                last_wpm = 0;
                cat_rendered = true;
            }
        } else if (wpm < TAP_SPEED) {
            oled_write_raw_P(prep[0], ANIM_SIZE);
            last_wpm = wpm;
            cat_rendered = true;
        } else {
            current_tap_frame = (current_tap_frame + 1) % TAP_FRAMES;
            oled_write_raw_P(tap[abs((TAP_FRAMES - 1) - current_tap_frame)], ANIM_SIZE);
            last_wpm = wpm;
            cat_rendered = true;
        }
    }
    
    // Display WPM when cat renders (overwrites it) OR when WPM value changes
    uint8_t current_wpm = get_current_wpm();
    if (cat_rendered || current_wpm != last_wpm) {
        char wpm_str[10];
        oled_set_cursor(0, 0);
        snprintf(wpm_str, sizeof(wpm_str), "WPM:%03d", current_wpm);
        oled_write(wpm_str, false);
        // last_wpm updated in animation logic above
    }
}

#endif
