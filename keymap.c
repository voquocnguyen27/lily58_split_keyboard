#include QMK_KEYBOARD_H
#define COMBO_COUNT 2

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _GAME,
};

// Định nghĩa mã phím tùy chỉnh
enum custom_keycodes {
    KC_A_ = SAFE_RANGE, // Đảm bảo mã phím tùy chỉnh không trùng với mã phím có sẵn
    KC_D_,
    LAYER3_ON,
};

// Định nghĩa các phím combo
const uint16_t PROGMEM layer_combo1[] = {KC_DEL, KC_BSPC, COMBO_END};
const uint16_t PROGMEM layer_combo2[] = {KC_BSPC, KC_DEL, COMBO_END};

// Gán combo vào một hành động
combo_t key_combos[COMBO_COUNT] = {
    COMBO(layer_combo1, LAYER3_ON),
    COMBO(layer_combo2, LAYER3_ON)
};

static uint8_t a_held = 0; 
static uint8_t d_held = 0;
static uint8_t a_script = 0; 
static uint8_t d_script = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  DEL  |    |BackSP |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE | BSPC |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
 [_QWERTY] = LAYOUT(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_DEL ,  KC_BSPC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                        KC_LALT, KC_LGUI, MO(_LOWER), KC_SPC, KC_ENT, MO(_RAISE), KC_BSPC, XXXXXXX
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   \  |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   ~  |
 * |------+------+------+------+------+------|  DEL  |    |BackSP |------+------+------+------+------+------|
 * |      |      |      |      |      | PGUP |-------|    |-------|   _  |   -  |   +  |   {  |   }  |   |  |
 * |------+------+------+------+------+------|      |      |      |------+------+------+------+------+------|
 * |      |      |      |      |      | PGDN |                    |      |      |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP|      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  KC_NUBS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
  _______, _______, _______, _______, _______, KC_PGUP,                   KC_UNDS, KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
  _______, _______, _______, _______, _______, KC_PGDN, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |-------.    ,-------|   (  | Left | Down |  Up  |Right |   )  |
 * |------+------+------+------+------+------|  DEL  |    |BackSP |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  | F10  | F11  | F12  |-------|    |-------|   +  |   -  |   =  |   [  |   ]  |   \  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RALT |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                       KC_LPRN, KC_LEFT, KC_UP,   KC_DOWN, KC_RGHT, KC_RPRN,
  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                             _______, _______, _______,  _______, _______,  _______, _______, KC_RALT
),
/* GAME
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |A_game|      |D_game|      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_GAME] = LAYOUT(
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, KC_A_  , _______, KC_D_  , _______, _______,                   _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                             KC_LALT,MO(_LOWER), KC_SPC, _______, _______,  _______, _______, _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_A_:
            if (record->event.pressed) {
                a_held = 1;

                if (d_script){ 
                    d_script = 0;
                    unregister_code16(KC_D);
                }
                if (!a_script){
                    a_script = 1;
                    register_code16(KC_A);
                }
            } else {
                a_held = 0;

                if (a_script){
                    a_script = 0;
                    unregister_code16(KC_A);
                }
                    
                if (d_held && !d_script){
                    d_script = 1;
                    register_code16(KC_D);
                }
            }
            break;
        case KC_D_:
            if (record->event.pressed) {
                d_held = 1;

                if (a_script){ 
                    a_script = 0;
                    unregister_code16(KC_A);
                }
                if (!d_script){
                    d_script = 1;
                    register_code16(KC_D);
                }
            } else {
                d_held = 0;

                if (d_script){
                    d_script = 0;
                    unregister_code16(KC_D);
                }
                    
                if (a_held && !a_script){
                    a_script = 1;
                    register_code16(KC_A);
                }
            }
            break;
        case LAYER3_ON:
            if (record->event.pressed) {
                if (IS_LAYER_ON(3)) {
                    layer_off(3);
                } else {
                    layer_on(3);
                }
            }
            return false;
        }
        return true;
    }
    
