//
// Created by xela on 10/1/18.
//

#pragma once

#include <string>
#include <core/key_types.h>
#include <map>
#include "HIDDevice.h"

class HIDKeyboard : public HIDDevice {
public:
    HIDKeyboard(const std::string &path);
    ~HIDKeyboard();

    void pressKey(KeyID button);
    void releaseKey(KeyID button);
    void updateKeys();

private:
    unsigned char m_modifier = 0;
    unsigned char m_pressedKeys[6] = {0};
    static const UInt32 DATA_SIZE = 8;
    static std::map<KeyID, unsigned char> KEY_TO_USB_VALUE;
    static std::map<KeyID, unsigned char> KEY_TO_USB_MODIFIER;
};
