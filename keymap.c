#include QMK_KEYBOARD_H
#ifdef OLED_ENABLE
#  include "oled_master.h"
#  include "oled_slave.h"
#endif

enum layer_number {
  _QWERTY = 0,
  _NUM,
  _SYM,
  _NAV,
  _FUN,
  _GAMING,
};

// Custom keycodes for independent RGB control
enum custom_keycodes {
  RGB_UGL = SAFE_RANGE,  // Toggle underglow only
  RGB_KEY,               // Toggle per-key only
};

// Track RGB state
static bool underglow_enabled = true;
static bool perkey_enabled = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      | BRIU | BRID |      |                     | PRV  |VOLDW |VOLUP | NXT  | ST/OP|      |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                     |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                     |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |--------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| GAMING |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |--------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `----------------------------------------- /      /     \      \ -----------------------------------------'
 *                   | LGUI | LALT | Space | / TAB  /       \Enter \  |BackSP|Delete| RGUI |
 *                   |      |      |       |/  NAV /         \ NUM  \ | SYM  | FUN  | RGUI |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  XXXXXXX,        XXXXXXX, XXXXXXX, KC_BRIU, KC_BRID, XXXXXXX,                  KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, XXXXXXX,
  KC_TAB,         KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  LCTL_T(KC_ESC), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,TG(_GAMING), XXXXXXX,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
            KC_LGUI, KC_LALT,  KC_SPC,   LT(_NAV, KC_TAB),         LT(_NUM, KC_ENT), LT(_SYM, KC_BSPC),  LT(_FUN, KC_DEL),  KC_RGUI
),

/* NUM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  7   |  8   |  9   |  -   |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  =   |  4   |  5   |  6   |  +   |-------.    ,-------|      |RCTRL |RSHIFT| RALT | RGUI |      |
 * |------+------+-------------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |  *   |  1   |  2   |  3   |  /   |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/      /     \      \-----------------------------------------'
 *                  |      |      |   0   | /  .   /       \       \ |      |      |      |
 *                  |      |      |       |/      /         \      \ |      |      |      |
 *                  `----------------------------'           '------''--------------------'
 */
[_NUM] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_7,    KC_8,    KC_9,    KC_MINS,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_EQL,  KC_4,    KC_5,    KC_6,    KC_PLUS,                   XXXXXXX, KC_RCTL, KC_RSFT, KC_RALT, KC_RGUI, XXXXXXX,
  XXXXXXX, KC_ASTR, KC_1,    KC_2,    KC_3,    KC_SLSH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             XXXXXXX, XXXXXXX, KC_0,    KC_DOT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* SYM
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |  '   |  <   |  >   |  "   |  .   |                    |  &   |  `   |  [   |  ]   |  %   |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |  !   |  -   |  +   |  =   |  #   |-------.    ,-------|  |   |  :   |  (   |  )   |  ?   |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LSHIFT|  ^   |  _   |  *   |  \   |  /   |-------|    |-------|  ~   |  $   |  {   |  }   |  @   |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      | Space | /      /       \       \ |      |      |      |
 *                  |      |      |       |/      /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_SYM] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_QUOT, KC_LABK, KC_RABK, KC_DQUO, KC_DOT,                    KC_AMPR, KC_GRV,  KC_LBRC, KC_RBRC, KC_PERC, XXXXXXX,
  KC_LCTL, KC_EXLM, KC_MINS, KC_PLUS, KC_EQL,  KC_HASH,                   KC_PIPE, KC_COLN, KC_LPRN, KC_RPRN, KC_QUES, XXXXXXX,
  KC_LSFT, KC_CIRC, KC_UNDS, KC_ASTR, KC_BSLS, KC_SLSH, XXXXXXX, XXXXXXX, KC_TILD, KC_DLR, KC_LCBR, KC_RCBR,  KC_AT,   XXXXXXX,
                             XXXXXXX, XXXXXXX, KC_SPC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

/* NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | PRV  |VOLDW |VOLUP | NXT  | ST/OP|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LGUI | LAlt |LSHIFT| LCTRL|      |-------.    ,-------| Left | Down |  Up  |Right | TAB  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| HOME |PGDOWN| PGUP | END  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                  |      |      |       | /      /       \       \ |      |      |      |
 *                  |      |      |       |/      /         \      \ |      |      |      |
 *                  `----------------------------'          '------''--------------------'
 */

[_NAV] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, XXXXXXX,
  XXXXXXX, KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL, XXXXXXX,                   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_TAB,  XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX, XXXXXXX,
                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* FUN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |RGBUGL|RGBKEY|      |      |      |                    |RMTOGG|RMNEXT|RMPREV|RM HU+|RM HD-|      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F7  |  F8  |  F9  | F12  |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F4  |  F5  |  F6  | F11  |-------.    ,-------|      |RCTRL |RSHIFT| LALT | RGUI |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |  F1  |  F2  |  F3  | F10  |-------|    |-------|RM SA+|RM SA-|RM VA+|RM VA-|RM SP+|RM SP-|
 * `-----------------------------------------/      /     \      \-----------------------------------------'
 *                  |      |      |       | /      /       \       \ |      |      |      |
 *                  |      |      |       |/      /         \      \ |      |      |      |
 *                  `----------------------------'           '------''--------------------'
 */
[_FUN] = LAYOUT(
  XXXXXXX, RGB_UGL, RGB_KEY, XXXXXXX, XXXXXXX, XXXXXXX,                   RM_TOGG, RM_NEXT, RM_PREV, RM_HUEU, RM_HUED, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_F7,   KC_F8,   KC_F9,   KC_F12,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_F4,   KC_F5,   KC_F6,   KC_F11,                    XXXXXXX, KC_RCTL, KC_RSFT, KC_LALT, KC_RGUI, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F10,  XXXXXXX, XXXXXXX, RM_SATU, RM_SATD, RM_VALU, RM_VALD, RM_SPDU, RM_SPDD,
                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* GAMING
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |  UP  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  | Left | Down |Right |  '   |
 * |------+------+------+------+------+------| QWERTY|    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |Space | /       /       \Enter \  | BCKSP| DEL  |      |
 *                   | RGUI | LAlt |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_GAMING] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_UP,   KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_LEFT, KC_DOWN, KC_RGHT, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   TG(_GAMING),KC_NO,KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                             KC_RGUI, KC_LALT, KC_SPC, XXXXXXX,   KC_ENT, KC_BSPC, KC_DEL, XXXXXXX
),
};

// OLED Display Configuration
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master()) {
    return OLED_ROTATION_270;  // Vertical display for master (left)
  }
  return rotation;  // Default rotation for slave (right)
}

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_render_master();     // Render master side display
  } else {
    // Only render when OLED is on - prevents animation from keeping screen awake
    if (is_oled_on()) {
      oled_render_slave();
    }
  }
  return false;
}

#endif // OLED_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_ENABLE
    set_last_key(keycode, record);  // Track last keycode for OLED
#endif
    // set_timelog();
  }

#ifdef RGB_MATRIX_ENABLE
  switch (keycode) {
    case RGB_UGL:  // Toggle underglow only
      if (record->event.pressed) {
        underglow_enabled = !underglow_enabled;
        rgb_matrix_set_flags(underglow_enabled ? LED_FLAG_ALL : (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER));
      }
      return false;

    case RGB_KEY:  // Toggle per-key only
      if (record->event.pressed) {
        perkey_enabled = !perkey_enabled;
        rgb_matrix_set_flags(perkey_enabled ? LED_FLAG_ALL : LED_FLAG_UNDERGLOW);
      }
      return false;
  }
#endif

  return true;
}
