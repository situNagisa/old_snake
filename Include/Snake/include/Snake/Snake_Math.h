//==========================================================================================================
// @file	:	Snake_Math
// @author	:	NAGISA
// @data	:	2023/1/19 14:49:35
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Math
#define __HEAD_Snake_Math

#include "NGS/NGS.h"

USE_NGS_TYPE

NGS_INL_CSTEXPR auto Max(Arithmetic auto a, Arithmetic auto b) {
    return a > b ? a : b;
}
NGS_INL_CSTEXPR auto Min(Arithmetic auto a, Arithmetic auto b) {
    return a < b ? a : b;
}
template<Arithmetic T>
NGS_INL_CSTEXPR BOOL InInterval(T val, T min, T max) {
    return val >= min && val <= max;
}

template<Arithmetic T>
NGS_INL_CSTEXPR T DistInterval(T val, T min,T max) {
    return Max(0, Max(min - val, val - max));
}

template<Arithmetic T>
NGS_INL_CSTEXPR BOOL IsCross(T min0, T max0, T min1, T max1) {
    return min1 <= max0 && min0 <= max1;
}

static BYTE _randoms[10] = {
    2,
    3,
    1,
    5,
    6,
    4,
    7,
    9,
    0
};
static BYTE i = 0;

NGS_INLINE FLOAT32 Random(UINT8 range = 10) {
    i %= 10;
    return _randoms[i++] / 10.0 * range;
}

#endif // !__HEAD_Snake_Math
