#include QMK_KEYBOARD_H

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  //debug_keyboard=true;
  //debug_mouse=true;
};


#ifdef AUDIO_ENABLE
float song0[][2] = SONG(COIN_SOUND);
float song1[][2] = SONG(ZELDA_PUZZLE);
float song2[][2] = SONG(ONE_UP_SOUND);

float tone_caps_on[][2]    = SONG(CAPS_LOCK_ON_SOUND);
float tone_caps_off[][2]   = SONG(CAPS_LOCK_OFF_SOUND);
float tone_numlk_on[][2]   = SONG(NUM_LOCK_ON_SOUND);
float tone_numlk_off[][2]  = SONG(NUM_LOCK_OFF_SOUND);
float tone_scroll_on[][2]  = SONG(SCROLL_LOCK_ON_SOUND);
float tone_scroll_off[][2] = SONG(SCROLL_LOCK_OFF_SOUND);
#endif

// We want to enable audio clicky (i.e. compile it into firmware),
// but not have it "turned on" by default.
#ifdef AUDIO_CLICKY

#include "process_clicky.h"
extern audio_config_t audio_config;

void eeconfig_init_kb(void) {
    // Reset Keyboard EEPROM value to blank, rather than to a set value
    eeconfig_update_kb(0);

    // Need to read here because this isn't done before calling eeconfig_init_kb()
    audio_config.raw = eeconfig_read_audio();
    // ...and this call needs audio_config initialized.
    clicky_off();

    eeconfig_init_user();
}
#endif // AUDIO_CLICKY



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case TO(0):
          if (record->event.pressed) {
          #ifdef AUDIO_ENABLE
          PLAY_SONG(song0);
          #endif
          break;
          }
      case TO(1):
        if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        PLAY_SONG(song1);
        #endif
        break;
        }
      case TO(2):
        if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        PLAY_SONG(song2);
        #endif
        break;
        }
    }
  // If console is enabled, it will print the matrix position and status of each key pressed
  #ifdef CONSOLE_ENABLE
  uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
  #endif 
  return true;
};

//Lock Key Feedback
bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
        //writePin(F1, led_state.caps_lock);
    }

#ifdef AUDIO_ENABLE
    static led_t old_led_state = { .raw = 0 };

    wait_ms(10); // gets rid of tick

    if (led_state.caps_lock && !old_led_state.caps_lock)
    {
        PLAY_SONG(tone_caps_on);
    }
    else if (!led_state.caps_lock && old_led_state.caps_lock)
    {
        PLAY_SONG(tone_caps_off);
    }
    else if (led_state.num_lock && !old_led_state.num_lock)
    {
        PLAY_SONG(tone_numlk_on);
    }
    else if (!led_state.num_lock && old_led_state.num_lock)
    {
        PLAY_SONG(tone_numlk_off);
    }
    else if (led_state.scroll_lock && !old_led_state.scroll_lock)
    {
        PLAY_SONG(tone_scroll_on);
    }
    else if (!led_state.scroll_lock && old_led_state.scroll_lock)
    {
        PLAY_SONG(tone_scroll_off);
    }

    old_led_state = led_state;
#endif // AUDIO_ENABLE
  return true;
}

//Custom Keycodes
enum custom_keycode {
    QMK_AC_ON = QK_USER_0, 
    QMK_AC_OFF, 
    QMK_AC_TOGG 
};

//Layer Definitions
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
