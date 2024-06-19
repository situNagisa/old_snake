//==========================================================================================================
// @file	:	WinEvent
// @author	:	NAGISA
// @data	:	2023/2/14 12:16:45
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_WinEvent
#define __HEAD_WinEvent

#include "N_WIN/N_WIN_Library.h"
#include "N_WIN/WinParam.h"

NGS_BEGIN

class WM_Event : public Event{
public:
    NGS_INL_CSTEXPR static __sign
        UPDATE = -1,
        CLOSE = WM_CLOSE,
        DESTORY = WM_DESTROY,
        PAINT = WM_PAINT
        ;
    NGS_INLINE static __string WM_EVENT_ID(__sign id) {
        _TYP WCHAR t[20];
        swprintf_s(t, L"WM_Event_%8d", id);
        return __string(t);
    }
public:
    using Event::Event;
    NGS_CONSTEXPR WM_Event(__sign id):
        Event(WM_EVENT_ID(id))
    {}
public:
    W_Param* GetParam() { return reinterpret_cast<W_Param*>(param); }
};

class KeyboardEvent : public Event {
public:
    NGS_INL_CSTEXPR static __sign
        KEY_DOWN = WM_KEYDOWN,
        KEY_UP = WM_KEYUP
        ;
public:
    using Event::Event;
    NGS_CONSTEXPR KeyboardEvent(__sign id) :
        Event(WM_Event::WM_EVENT_ID(id))
    {}
public:
    KeyboardParam* GetParam() { return reinterpret_cast<KeyboardParam*>(param); }
};

class MouseEvent : public Event {
public:
    NGS_INL_CSTEXPR static __sign
        LEFT_DOWN = WM_LBUTTONDOWN,
        LEFT_UP = WM_LBUTTONUP,
        LEFT_DOUBLE_CLICK = WM_LBUTTONDBLCLK,
        RIGHT_DOWN = WM_RBUTTONDOWN,
        RIGHT_UP = WM_RBUTTONUP,
        RIGHT_DOUBLE_CLICK = WM_RBUTTONDBLCLK,
        MIDDLE_DOWN = WM_MBUTTONDOWN,
        MIDDLE_UP = WM_MBUTTONUP,
        MIDDLE_DOUBLE_CLICK = WM_MBUTTONDBLCLK,
        WHEEL = WM_MOUSEWHEEL,
        HOVER = WM_MOUSEHOVER,
        MOVE = WM_MOUSEMOVE,
        LEAVE = WM_MOUSELEAVE
        ;
public:
    using Event::Event;
    NGS_CONSTEXPR MouseEvent(__sign id) :
        Event(WM_Event::WM_EVENT_ID(id))
    {}
public:
    MouseParam* GetParam() { return reinterpret_cast<MouseParam*>(param); }
};

NGS_END

#endif // !__HEAD_WinEvent
