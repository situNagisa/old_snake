//==========================================================================================================
// @file	:	NGS_Bit_Module
// @author	:	NAGISA
// @data	:	2023/1/16 21:00:26
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Bit_Module
#define __HEAD_NGS_Bit_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Config.h"
#include "NGS/NGS_TypeTrait.h"
#include "NGS/NGS_Concepts.h"
#include "NGS/NGS_Module.h"
#include "NGS/NGS_TemplateMetaBase.h"

NGS_EXPORT
NGS_BEGIN
NGS_TYPE

using FLAG = BYTE;

NGS_END


NGS_CONCEPT

template<class T>
concept Bit = _TYT IsINT<T> || requires(T a) {
    (int)a;
};

NGS_END

NGS_INL_CSTEXPR _TYP UINT64 bit(_TYP UINT16 n) { return static_cast<ngs::type::UINT64>(1) << n; }
NGS_INL_CSTEXPR _TYP UINT64 bit_max(_TYP UINT16 bitCount) { return bit(bitCount) - 1; }

template<_TYP BOOL B,class T>
NGS_INLINE _TYP VOID Bits(T& p, _CPT Bit auto bit) {
    if NGS_CONSTEXPR(B)
        p |= (T)bit;
    else
        p &= ~(T)bit;
}

NGS_INLINE _TYP VOID Bits(auto& p, _CPT Bit auto bit, _TYP BOOL boolean) {
    if (boolean)
        Bits<TRUE>(p, bit);
    else
        Bits<FALSE>(p, bit);
}

template<class T>
NGS_INL_CSTEXPR _TYP BOOL Bits(T p, _CPT Bit auto bit) { return p & (T)bit; }

template<_TYP SIZE_T16 start, _TYP SIZE_T16 end>
NGS_INLINE _TYP VOID Bits(auto& dest, auto source) {
    For<start, end>([&](_TYP UINT16 i) {
        _TYP BOOL b = Bits(source, bit(i));
        Bits(dest, bit(i), b);
        });
}


NGS_INL_CSTEXPR _TYP SIZE_T32 BitsOf(auto target = 0) { return sizeof(target) * 8; }
NGS_INL_CSTEXPR _TYP SIZE_T32 ByteOf(_TYP SIZE_T32 bitCount) {
    NGS_CONSTEXPR auto byteBits = BitsOf<_TYP BYTE>();
    if (bitCount % byteBits)return bitCount / byteBits + 1;
    return bitCount / byteBits;
}


NGS_END

#endif // !__HEAD_NGS_Bit_Module
