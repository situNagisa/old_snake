//==========================================================================================================
// @file	:	Math_Module
// @author	:	NAGISA
// @data	:	2023/1/27 19:55:09
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Math_Module
#define __HEAD_Math_Module

#include "NGS/NGS.h"

NGS_BEGIN

NGS_INL_CSTEXPR auto Abs(auto v) { return abs(v); }

NGS_INLINE auto Max(auto a, auto b) { return a > b ? a : b; }
NGS_INLINE auto Min(auto a, auto b) { return a > b ? b : a; }

/* 判断点是否在区间内 */
template<_CPT Arithmetic T>NGS_INLINE _TYP BOOL In(T val, T min, T max) { return val >= min && val <= max; }
/* 点与区间的距离，若在区间内则为0 */
template<_CPT Arithmetic T>NGS_INLINE T Distance(T val, T min, T max) { return Max(0, Max(min - val, val - max)); }
/* 判断两区间是否相交 */
template<_CPT Arithmetic T>NGS_INLINE _TYP BOOL IsCross(T min0, T max0, T min1, T max1) { return min1 <= max0 && min0 <= max1; }

NGS_INL_CSTEXPR const _TYP FLOAT32 PI = 3.1415926f;
NGS_INL_CSTEXPR const _TYP FLOAT32 _degrees_to_radian = PI / 180;
NGS_INL_CSTEXPR const _TYP FLOAT32 _radian_to_degrees = 180 / PI;

auto Sin(_CPT Arithmetic auto radian) { return ::sin(radian); }
auto Cos(_CPT Arithmetic auto radian) { return ::cos(radian); }
auto Tan(_CPT Arithmetic auto radian) { return ::tan(radian); }

constexpr auto Decimals(_CPT Arithmetic auto floating) {
    return floating - _TYP INT64(floating);
}
consteval auto Power(_CPT Arithmetic auto value, _TYP SIZE_T32 power) {
    switch (power)
    {
    case 0:
        return 1;
        break;
    case 1:
        break;
    default:
        for (_TYP SIZE_T32 i = 1; i < power; i++)
            value *= value;
        break;
    }
    return value;
}
consteval auto Round(_CPT Arithmetic auto floating) {
    constexpr auto d = floating - _TYP INT64(floating);
    NGS_CST_IF (d > 0.4) {
        return _TYP INT64(floating) + 1;
    } NGS_CST_ELSE{
        return _TYP INT64(floating);
    }
}
NGS_INL_CSTEXPR auto Floor(_CPT Arithmetic auto floating) { return ::floor(floating); }
NGS_INL_CSTEXPR auto Ceil(_CPT Arithmetic auto floating) { return ::ceil(floating); }

NGS_INL_CSTEXPR _TYP FLOAT32 AsRadian(_TYP INT16 degrees) { return degrees * _degrees_to_radian; }
NGS_INL_CSTEXPR _TYP UINT16 AsDegrees(_TYP FLOAT32 radian) { return static_cast<_TYP UINT16>(radian * _radian_to_degrees); }


NGS_INL_CSTEXPR _TYP INT8 Sgn(auto num) { if (!num)return 0; return num > 0 ? 1 : -1; }

NGS_END

#endif // !__HEAD_Math_Module
