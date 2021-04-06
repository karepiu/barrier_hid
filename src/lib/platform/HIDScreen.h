//
// Created by xela on 5/1/18.
//

#pragma once

#include "core/PlatformScreen.h"
#include "HIDKeyboard.h"
#include "HIDKeyState.h"
#include "HIDMouse.h"
#include "HIDTouch.h"

class HIDScreen : public PlatformScreen {
public:
    HIDScreen(const std::string & mouseDevice,
              const std::string & keyboardDevice,
              const std::string & touchDevice,
              int screenWidth, int screenHeight,
              IEventQueue *events);
    virtual ~HIDScreen();

    //! @name manipulators
    //@{

    //@}

    // IScreen overrides
    virtual void*        getEventTarget() const;
    virtual bool        getClipboard(ClipboardID id, IClipboard*) const;
    virtual void        getShape(SInt32& x, SInt32& y,
                                 SInt32& w, SInt32& h) const;
    virtual void        getCursorPos(SInt32& x, SInt32& y) const;

    // IPrimaryScreen overrides
    virtual void        reconfigure(UInt32 activeSides);
    virtual void        warpCursor(SInt32 x, SInt32 y);
    virtual UInt32        registerHotKey(KeyID key, KeyModifierMask mask);
    virtual void        unregisterHotKey(UInt32 id);
    virtual void        fakeInputBegin();
    virtual void        fakeInputEnd();
    virtual SInt32        getJumpZoneSize() const;
    virtual bool        isAnyMouseButtonDown(UInt32& buttonID) const;
    virtual void        getCursorCenter(SInt32& x, SInt32& y) const;

    // ISecondaryScreen overrides
    virtual void        fakeMouseButton(ButtonID button, bool press);
    virtual void        fakeMouseMove(SInt32 x, SInt32 y);
    virtual void        fakeMouseRelativeMove(SInt32 dx, SInt32 dy) const;
    virtual void        fakeMouseWheel(SInt32 xDelta, SInt32 yDelta) ;

    // IPlatformScreen overrides
    virtual void        enable();
    virtual void        disable();
    virtual void        enter();
    virtual bool        leave();
    virtual bool        setClipboard(ClipboardID, const IClipboard*);
    virtual void        checkClipboards();
    virtual void        openScreensaver(bool notify);
    virtual void        closeScreensaver();
    virtual void        screensaver(bool activate);
    virtual void        resetOptions();
    virtual void        setOptions(const OptionsList& options);
    virtual void        setSequenceNumber(UInt32);
    virtual bool        isPrimary() const;

protected:
    // IPlatformScreen overrides
    virtual void        handleSystemEvent(const Event&, void*);
    virtual void        updateButtons();
    virtual IKeyState*    getKeyState() const;

private:
    HIDMouse            m_mouseDevice;
    HIDTouch            m_touchDevice;
    SInt32              m_w, m_h;
    int                 m_mousex;
    int                 m_mousey;

    IEventQueue*        m_events;
    synergy::KeyMap     m_keyMap;

    HIDKeyState*        m_keyState;
};

