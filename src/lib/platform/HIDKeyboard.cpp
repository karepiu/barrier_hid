//
// Created by xela on 10/1/18.
//

#include <base/Log.h>
#include <X11/keysym.h>
#include "HIDKeyboard.h"

std::map<KeyID, unsigned char> HIDKeyboard::KEY_TO_USB_MODIFIER = {
        {kKeyControl_L, 0x01},
        {kKeyControl_R, 0x10},
        {kKeyShift_L, 0x02},
        {kKeyShift_R, 0x20},
        {kKeyAlt_L, 0x04},
        {kKeyAlt_R, 0x40},
        {kKeyMeta_L, 0x08},
        {kKeyMeta_R, 0x80},
};

std::map<KeyID, unsigned char> HIDKeyboard::KEY_TO_USB_VALUE = {
        {XK_a, 0x04},
        {XK_A, 0x04},
        {XK_b, 0x05},
        {XK_B, 0x05},
        {XK_c, 0x06},
        {XK_C, 0x06},
        {XK_d, 0x07},
        {XK_D, 0x07},
        {XK_e, 0x08},
        {XK_E, 0x08},
        {XK_f, 0x09},
        {XK_F, 0x09},
        {XK_g, 0x0a},
        {XK_G, 0x0a},
        {XK_h, 0x0b},
        {XK_H, 0x0b},
        {XK_i, 0x0c},
        {XK_I, 0x0c},
        {XK_j, 0x0d},
        {XK_J, 0x0d},
        {XK_k, 0x0e},
        {XK_K, 0x0e},
        {XK_l, 0x0f},
        {XK_L, 0x0f},
        {XK_m, 0x10},
        {XK_M, 0x10},
        {XK_n, 0x11},
        {XK_N, 0x11},
        {XK_o, 0x12},
        {XK_O, 0x12},
        {XK_p, 0x13},
        {XK_P, 0x13},
        {XK_q, 0x14},
        {XK_Q, 0x14},
        {XK_r, 0x15},
        {XK_R, 0x15},
        {XK_s, 0x16},
        {XK_S, 0x16},
        {XK_t, 0x17},
        {XK_T, 0x17},
        {XK_u, 0x18},
        {XK_U, 0x18},
        {XK_v, 0x19},
        {XK_V, 0x19},
        {XK_w, 0x1a},
        {XK_W, 0x1a},
        {XK_x, 0x1b},
        {XK_X, 0x1b},
        {XK_y, 0x1c},
        {XK_Y, 0x1c},
        {XK_z, 0x1d},
        {XK_Z, 0x1d},
        {XK_1, 0x1e},
        {XK_exclam, 0x1e},
        {XK_2, 0x1f},
        {XK_at, 0x1f},
        {XK_3, 0x20},
        {XK_numbersign, 0x20},
        {XK_4, 0x21},
        {XK_dollar, 0x21},
        {XK_5, 0x22},
        {XK_percent, 0x22},
        {XK_6, 0x23},
        {XK_asciicircum, 0x23},
        {XK_7, 0x24},
        {XK_ampersand, 0x24},
        {XK_8, 0x25},
        {XK_asterisk, 0x25},
        {XK_9, 0x26},
        {XK_parenleft, 0x26},
        {XK_0, 0x27},
        {XK_parenright, 0x27},
        {kKeyReturn, 0x28},
        {kKeyEscape, 0x29},
        {kKeyBackSpace, 0x2a},
        {kKeyTab, 0x2b},
        {XK_space, 0x2c},
        {XK_minus, 0x2d},
        {XK_underscore, 0x2d},
        {XK_equal, 0x2e},
        {XK_plus, 0x2e},
        {XK_bracketleft, 0x2f},
        {XK_braceleft, 0x2f},
        {XK_bracketright, 0x30},
        {XK_braceright, 0x30},
        {XK_backslash, 0x31},
        {XK_bar, 0x31},
        {XK_semicolon, 0x33},
        {XK_colon, 0x33},
        {XK_apostrophe, 0x34},
        {XK_quotedbl, 0x34},
        {XK_quoteleft, 0x35},
        {XK_asciitilde, 0x35},
        {XK_comma, 0x36},
        {XK_less, 0x36},
        {XK_period, 0x37},
        {XK_greater, 0x37},
        {XK_slash, 0x38},
        {XK_question, 0x38},
        {kKeyCapsLock, 0x39},
        {kKeyF1, 0x3a},
        {kKeyF2, 0x3b},
        {kKeyF3, 0x3c},
        {kKeyF4, 0x3d},
        {kKeyF5, 0x3e},
        {kKeyF6, 0x3f},
        {kKeyF7, 0x40},
        {kKeyF8, 0x41},
        {kKeyF9, 0x42},
        {kKeyF10, 0x43},
        {kKeyF11, 0x44},
        {kKeyF12, 0x45},
        {kKeyPrint, 0x46},
        {kKeyScrollLock, 0x47},
        {kKeyPause, 0x48},
        {kKeyInsert, 0x49},
        {kKeyHome, 0x4a},
        {kKeyPageUp, 0x4b},
        {kKeyDelete, 0x4c},
        {kKeyEnd, 0x4d},
        {kKeyPageDown, 0x4e},
        {kKeyRight, 0x4f},
        {kKeyLeft, 0x50},
        {kKeyDown, 0x51},
        {kKeyUp, 0x52},
        {kKeyNumLock, 0x53},
        {kKeyKP_Divide, 0x54},
        {kKeyKP_Multiply, 0x55},
        {kKeyKP_Subtract, 0x56},
        {kKeyKP_Add, 0x57},
        {kKeyKP_Enter, 0x58},
        {kKeyKP_1, 0x59},
        {kKeyKP_2, 0x5a},
        {kKeyKP_3, 0x5b},
        {kKeyKP_4, 0x5c},
        {kKeyKP_5, 0x5d},
        {kKeyKP_6, 0x5e},
        {kKeyKP_7, 0x5f},
        {kKeyKP_8, 0x60},
        {kKeyKP_9, 0x61},
        {kKeyKP_0, 0x62},
        {kKeyKP_Decimal, 0x63},
        //{"application", 0x65},
        //{"power", 0x66},
        {kKeyKP_Equal, 0x67},
        {kKeyF13, 0x68},
        {kKeyF14, 0x69},
        {kKeyF15, 0x6a},
        {kKeyF16, 0x6b},
        {kKeyF17, 0x6c},
        {kKeyF18, 0x6d},
        {kKeyF19, 0x6e},
        {kKeyF20, 0x6f},
        {kKeyF21, 0x70},
        {kKeyF22, 0x71},
        {kKeyF23, 0x72},
        {kKeyF24, 0x73},
        {kKeyExecute, 0x74},
        {kKeyHelp, 0x75},
        {kKeyMenu, 0x76},
        {kKeySelect, 0x77},
        {kKeyCancel, 0x78},
        {kKeyRedo, 0x79},
        {kKeyUndo, 0x7a},
        //{"cut", 0x7b},
        //{"copy", 0x7c},
        //{"paste", 0x7d},
        {kKeyFind, 0x7e},
        {kKeyAudioMute, 0x7f},
};

HIDKeyboard::HIDKeyboard(
        const std::string& path) :
        HIDDevice(path, DATA_SIZE)
{

}

HIDKeyboard::~HIDKeyboard() {

}

void HIDKeyboard::pressKey(KeyID button) {
    auto modifierIter = KEY_TO_USB_MODIFIER.find(button);
    if (modifierIter != KEY_TO_USB_MODIFIER.end()) {
        unsigned char modifier = modifierIter->second;
        m_modifier |= modifier;
        updateKeys();
        return;
    }

    auto valueIter = KEY_TO_USB_VALUE.find(button);
    if (valueIter == KEY_TO_USB_VALUE.end()) {
        return;
    }
    unsigned char value = valueIter->second;
    for (unsigned char &pressedKey : m_pressedKeys) {
        if (pressedKey == 0) {
            pressedKey = value;
            updateKeys();
            return;
        }
    }
}

void HIDKeyboard::releaseKey(KeyID button) {
    auto modifierIter = KEY_TO_USB_MODIFIER.find(button);
    if (modifierIter != KEY_TO_USB_MODIFIER.end()) {
        unsigned char modifier = modifierIter->second;
        m_modifier |= modifier;
        m_modifier ^= modifier;
        updateKeys();
        return;
    }

    auto valueIter = KEY_TO_USB_VALUE.find(button);
    if (valueIter == KEY_TO_USB_VALUE.end()) {
        return;
    }
    unsigned char key = valueIter->second;
    for (unsigned char &pressedKey : m_pressedKeys) {
        if (pressedKey == key) {
            pressedKey = 0;
            updateKeys();
            return;
        }
    }
}

void HIDKeyboard::updateKeys() {
    m_data[0] = m_modifier;
    for (int i = 0; i < 6; ++i) {
        m_data[i + 2] = m_pressedKeys[i];
    }
    update();
}

