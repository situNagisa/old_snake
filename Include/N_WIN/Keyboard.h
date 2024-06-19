//==========================================================================================================
// @file	:	Keyboard
// @author	:	NAGISA
// @data	:	2023/2/15 12:43:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Keyboard
#define __HEAD_Keyboard

#include "N_WIN/N_WIN_Library.h"

NGS_BEGIN

#undef DELETE
enum Keyboard : _TYP UINT32
{
    BACKSPACE = VK_BACK,
    TAB,
    CLEAR,
    ENTER,
    SHIFT,
    CONTROL,
    ALT,
    PAUSEBREAK,
    CAPSLOCK,

    ESCAPE = VK_ESCAPE,

    SPACE = VK_SPACE,
    PRIOR,
    NEXT,
    END,
    HOME,
    LEFT,
    UP,
    RIGHT,
    DOWN,
    SELECT,
    PRINT,
    EXECUTE,
    PRINTSCREEN,
    INSERT,
    DELETE,
    HELP,

    ZERO = 0x30,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,

    A = 0x41,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    NUMPAD_ZERO = VK_NUMPAD0,
    NUMPAD_ONE,
    NUMPAD_TWO,
    NUMPAD_THREE,
    NUMPAD_FOUR,
    NUMPAD_FIVE,
    NUMPAD_SIX,
    NUMPAD_SEVEN,
    NUMPAD_EIGHT,
    NUMPAD_NINE,
    NUMPAD_MULTIPLY,
    NUMPAD_ADD,
    NUMPAD_SPERATOR,
    NUMPAD_SUBTRACT,
    NUMPAD_DECIMAL,
    NUMPAD_DIVIDE,

    F1 = VK_F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,

    SEMICOLON = VK_OEM_1,
    PLUS,
    COMMA,
    MINUS,
    PERIOD,
    SLASH,

    LBRACKET = VK_OEM_4,
    BACKSLASH,
    RBRACKET,
    QUOTE
};

NGS_END

#endif // !__HEAD_Keyboard
