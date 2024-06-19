//==========================================================================================================
// @file	:	WinParam
// @author	:	NAGISA
// @data	:	2023/2/14 13:35:34
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_WinParam
#define __HEAD_WinParam

#include "N_WIN/N_WIN_Library.h"
#include "N_WIN/Keyboard.h"

NGS_BEGIN

class Window;

struct W_Param : public Object{
public:
    _TYP UINT32 message;
    Window* pWindow;
    WPARAM wParam;
    LPARAM lParam;
    _TYP PVOID user;

    W_Param(
        _TYP UINT32 message,
        Window* pWindow,
        WPARAM wParam,
        LPARAM lParam,
        _TYP PVOID user = nullptr
    ):
        message(message),
        pWindow(pWindow),
        wParam(wParam),
        lParam(lParam),
        user(user)
    {}
};

struct KeyboardParam : W_Param{
    using W_Param::W_Param;

    Keyboard KeyCode()const { return (Keyboard)wParam; }
};

struct MouseParam : W_Param {
    using W_Param::W_Param;

    _TYP UINT16 WheelDelta()const { return HIWORD(wParam); }

    _TYP UINT16 Y()const { return HIWORD(lParam); }
    _TYP UINT16 X()const { return LOWORD(lParam); }
};

NGS_END

#endif // !__HEAD_WinParam
