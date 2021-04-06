//
// Created by xela on 5/3/18.
//

#include <base/Log.h>
#include "HIDMouse.h"

HIDMouse::HIDMouse(
        const std::string& path) :
    HIDDevice(path, DATA_SIZE)
{

}

HIDMouse::~HIDMouse() {

}

void HIDMouse::updateButton(ButtonID button, bool press) {

    UInt8 mask;

    switch (button){
    case kButtonLeft:
        mask = 0x01;
        break;

    case kButtonRight:
        mask = 0x02;
        break;

    case kButtonMiddle:
        mask = 0x04;
        break;

    default:
        mask = 0x00;
        break;
    }

    // Check if the button needs to be toggled
    if (press && (m_data[0] & mask) == 0) {
        m_data[0] ^= mask;
    } else if (!press && (m_data[0] & mask) != 0) {
        m_data[0] ^= mask;
    } 
    
    m_data[5] = 0x00;
        
    update();
}

void HIDMouse::updateWheel(float x, float y) {
    
    LOG((CLOG_DEBUG "%u %u", x, y));
    
    LOG((CLOG_DEBUG "%x", m_data[5]));
    
    if ( y < 0 ) {
        m_data[5] = 0xFF;
    }
    else if ( y > 0 ) {
        m_data[5] = 0x01;
    }
    
    update();
}




