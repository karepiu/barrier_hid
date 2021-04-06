//
// Created by xela on 5/3/18.
//

#include <base/Log.h>
#include "HIDKeyState.h"

HIDKeyState::HIDKeyState(
        IEventQueue* events) :
        KeyState(events),
        m_keyboardDevice("/dev/null")
{
    init();
}

HIDKeyState::HIDKeyState(
        IEventQueue* events, synergy::KeyMap& keyMap) :
        KeyState(events, keyMap),
        m_keyboardDevice("/dev/null")
{
    init();
}

HIDKeyState::HIDKeyState(
        IEventQueue *events, synergy::KeyMap& keyMap, const std::string& keyboardDevice) :
        KeyState(events, keyMap),
        m_keyboardDevice(keyboardDevice)
{
    init();
}

HIDKeyState::~HIDKeyState()
{
    // TODO
}

void HIDKeyState::init()
{
    // TODO
}

bool HIDKeyState::fakeCtrlAltDel()
{
    return false;
}

KeyModifierMask HIDKeyState::pollActiveModifiers() const
{
    // TODO
    return 0;
}

SInt32 HIDKeyState::pollActiveGroup() const
{
    // TODO
    return 0;
}

void HIDKeyState::pollPressedKeys(IKeyState::KeyButtonSet &pressedKeys) const
{
    // TODO
}

void HIDKeyState::getKeyMap(synergy::KeyMap &keyMap)
{
    // TODO
}

void HIDKeyState::fakeKeyDown(KeyID id, KeyModifierMask mask, KeyButton serverID) {
    LOG((CLOG_DEBUG "fakeKeyDown (%d, %d)", serverID, id));
    m_serverIDToKeyIDMap[serverID] = id;
    m_keyboardDevice.pressKey(id);
}

bool HIDKeyState::fakeKeyUp(KeyButton serverID) {
    LOG((CLOG_DEBUG "fakeKeyUp (%d)", serverID));
    auto id = m_serverIDToKeyIDMap.find(serverID);
    if (id == m_serverIDToKeyIDMap.end()) {
        return false;
    } else {
        m_keyboardDevice.releaseKey(id->second);
        m_serverIDToKeyIDMap.erase(serverID);
        return true;
    }
}

void HIDKeyState::fakeKey(const KeyState::Keystroke &keystroke)
{
    // TODO
}
