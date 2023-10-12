#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}

enum layers {
	_BASE,
	_GAME,
  	_MIDI
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(
    KC_ESC,      KC_VOLD,        KC_VOLU,      KC_F1,         KC_F2,   KC_F3,    KC_F4,   KC_F5,    KC_F6,         KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SCROLL_LOCK, KC_MPLY,
    KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS,  KC_GRAVE,      KC_1,    KC_2,     KC_3,    KC_4,     KC_5,          KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,     KC_BSPC,  KC_DELETE,
    KC_KP_7,     KC_KP_8,        KC_KP_9,      KC_TAB,        KC_Q,    KC_W,     KC_E,    KC_R,     KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,    KC_HOME,   KC_BSLS,
    KC_KP_4,     KC_KP_5,        KC_KP_6,      KC_CAPS_LOCK,   KC_A,   KC_S,     KC_D,    KC_F,     KC_G,          KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, TD(0),      KC_END,   KC_PGUP,
    KC_KP_1,     KC_KP_2,        KC_KP_3,      KC_LSFT,       KC_Z,    KC_X,     KC_C,    KC_V,     KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_DELETE,  KC_UP,    KC_PGDN,
    KC_KP_0,     KC_KP_DOT,      KC_KP_ENTER,  KC_LCTL,       TO(2),   KC_LALT,  KC_NO,   KC_BSPC,  KC_NO,         KC_BSPC, KC_SPC,  KC_SPC,  TD(2),   KC_RALT, KC_RCTL, KC_LEFT,    KC_DOWN,  KC_RGHT
),

[_GAME] = LAYOUT(
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LSFT,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LCTL,	_______,	_______,	_______,	_______,	KC_SPC,  	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______
),

[_MIDI] = LAYOUT(
	MI_TOGG,	QK_MIDI_NOTE_C_SHARP_0,	QK_MIDI_NOTE_D_0,	QK_MIDI_NOTE_D_SHARP_0,	QK_MIDI_NOTE_E_0,	QK_MIDI_NOTE_F_0,	QK_MIDI_NOTE_F_SHARP_0,	QK_MIDI_NOTE_G_0,	QK_MIDI_NOTE_G_SHARP_0,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LSFT,	_______,	_______,	_______,	_______,	_______,	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	_______,	_______,	KC_LCTL,	_______,	_______,	_______,	_______,	KC_SPC,  	_______,			_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______
)
};
