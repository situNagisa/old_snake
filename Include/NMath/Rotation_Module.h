//==========================================================================================================
// @file	:	Rotation_Module
// @author	:	NAGISA
// @data	:	2023/2/25 12:46:45
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Rotation_Module
#define __HEAD_Rotation_Module

#include "NGS/NGS.h"

NGS_BEGIN

template<_CPT FloatingPoint Number = _TYP FLOAT32>
struct Rotation {
    constexpr Rotation() = default;
    constexpr Rotation(_TYP FLOAT32 angle) {
        sin = ::sin(angle);
        cos = ::cos(angle);
    }
    constexpr Rotation(Number sin,Number cos)
        :sin(sin)
        ,cos(cos)
    {}

    _TYP VOID Identity() {
        sin = 0;
        cos = 1;
    }
    constexpr _TYP FLOAT32 Angle()const { return ::atan2(sin, cos); }

    Number sin, cos;
};

NGS_END

#endif // !__HEAD_Rotation_Module
