//
// Created by xela on 5/1/18.
//

#include "base/Log.h"
#include "base/TMethodEventJob.h"
#include "HIDScreen.h"

HIDScreen::HIDScreen(
        const std::string& mouseDevice,
        const std::string& keyboardDevice,
        const std::string& touchDevice,
        SInt32 screenWidth,
        SInt32 screenHeight,
        IEventQueue *events) :
    PlatformScreen(events),
    m_mouseDevice(mouseDevice),
    m_touchDevice(touchDevice),
    m_w(screenWidth),
    m_h(screenHeight),
    m_mousex(-1),
    m_mousey(-1),
    m_events(events),
    m_keyState(nullptr)
{
    // TODO

    m_keyState = new HIDKeyState(events, m_keyMap, keyboardDevice);

    // install event handlers
    m_events->adoptHandler(Event::kSystem, m_events->getSystemTarget(),
                           new TMethodEventJob<HIDScreen>(this,
                               &HIDScreen::handleSystemEvent));

    LOG((CLOG_DEBUG "HIDScreen constructed"));

}

HIDScreen::~HIDScreen()
{
    // TODO
    delete m_keyState;

    m_events->removeHandler(Event::kSystem, m_events->getSystemTarget());
}

void *HIDScreen::getEventTarget() const
{
    return const_cast<HIDScreen*>(this);
}

bool HIDScreen::getClipboard(ClipboardID /*unused*/, IClipboard* /*unused*/) const
{
    // Not supported
    return false;
}

void HIDScreen::getShape(SInt32 &x, SInt32 &y, SInt32 &w, SInt32 &h) const
{
    x = 0;
    y = 0;
    w = m_w;
    h = m_h;
}

void HIDScreen::getCursorPos(SInt32 &x, SInt32 &y) const
{
    x = 0;
    y = 0;
    // TODO
}

void HIDScreen::reconfigure(UInt32 /*unused*/)
{
    // Not supported
}

void HIDScreen::warpCursor(SInt32 /*unused*/, SInt32 /*unused*/)
{
    // Not supported
}

UInt32 HIDScreen::registerHotKey(KeyID /*unused*/, KeyModifierMask /*unused*/)
{
    // Not supported
    return 0;
}

void HIDScreen::unregisterHotKey(UInt32 /*unused*/)
{
    // Not supported
}

void HIDScreen::fakeInputBegin()
{
    // Not supported
}

void HIDScreen::fakeInputEnd()
{
    // Not supported
}

SInt32 HIDScreen::getJumpZoneSize() const
{
    // Not supported
    return 0;
}

bool HIDScreen::isAnyMouseButtonDown(UInt32 &buttonID) const
{
    // Not supported
    return false;
}

void HIDScreen::getCursorCenter(SInt32 &x, SInt32 &y) const
{
    // Not supported
}

void HIDScreen::fakeMouseButton(ButtonID button, bool press)
{
    LOG((CLOG_DEBUG "fakeMouseButton: (%d %d)", button, press));
    m_mouseDevice.updateButton(button, press);
}

void HIDScreen::fakeMouseMove(SInt32 x, SInt32 y)
{
    LOG((CLOG_DEBUG "fakeMouseMove: (%d %d)", x, y));
    m_touchDevice.move(((float) x) / m_w, ((float) y) / m_h);
}

void HIDScreen::fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const
{
    LOG((CLOG_DEBUG "fakeMouseRelativeMove: (%d %d)", dx, dy));
    // TODO
}

void HIDScreen::fakeMouseWheel(SInt32 xDelta, SInt32 yDelta) 
{
    LOG((CLOG_DEBUG "fakeMouseWheel: (%d %d)", xDelta, yDelta));
    float x = (float) xDelta;
    float y = (float) yDelta;
    m_mouseDevice.updateWheel( x, y );
    // TODO
}

void HIDScreen::enable()
{
    // Do nothing
}

void HIDScreen::disable()
{
    // Do nothing
}

void HIDScreen::enter()
{
    // Assume the mouse location is unknown again
    m_mousex = -1;
    m_mousey = -1;
}

bool HIDScreen::leave()
{
    return true;
}

bool HIDScreen::setClipboard(ClipboardID, const IClipboard *)
{
    // Not supported
    return false;
}

void HIDScreen::checkClipboards()
{
    // Not supported
}

void HIDScreen::openScreensaver(bool /*unused*/)
{
    // Not supported
}

void HIDScreen::closeScreensaver()
{
    // Not supported
}

void HIDScreen::screensaver(bool /*unused*/)
{
    // Not supported
}

void HIDScreen::resetOptions()
{
    // TODO
}

void HIDScreen::setOptions(const OptionsList &options)
{
    // TODO
}

void HIDScreen::setSequenceNumber(UInt32)
{
    // TODO
}

bool HIDScreen::isPrimary() const
{
    return false;
}

void HIDScreen::handleSystemEvent(const Event &, void *)
{
    // TODO
}

void HIDScreen::updateButtons()
{
    // TODO
}

IKeyState *HIDScreen::getKeyState() const
{
    return m_keyState;
}
