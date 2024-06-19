//==========================================================================================================
// @file	:	Snake_Color
// @author	:	NAGISA
// @data	:	2023/1/17 19:38:58
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Color
#define __HEAD_Snake_Color

#include "NGS/NGS.h"

USE_NGS_TYPE

struct UINT24
{
private:
    using _this = UINT24;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this*;
    using _this_ref = _this&;
    using _this_ref_cst = const _this&;

    UINT16 _low;
    UINT8 _high;
public:
    UINT24() = default;
    template<UnsignedIntegral UINT>
    UINT24(UINT u) {
        _low = u;
        _high = 0;
    }
    UINT24(UINT32 uint32) {
        _low = uint32 & 0x00FFFF;
        _high = static_cast<UINT8>(uint32 & 0xFF0000);
    }

    template<UnsignedIntegral UINT>
    NGS_INLINE operator UINT()const {
        return static_cast<UINT>(_low);
    }
    NGS_INLINE operator UINT32()const { return (_high << 16) & _low; }

    NGS_INLINE _this_ref operator=(UINT32 uint32) {
        _low = uint32 & 0x00FFFF;
        _high = static_cast<UINT8>(uint32 & 0xFF0000);
        return *this;
    }
    //auto operator<=>(const UINT24&)const = default;
};

template<class T,class ParsingStruct>
union Parsing
{
    ParsingStruct parsing;
    T value;
    NGS_INLINE Parsing() = default;
    NGS_INLINE Parsing(const T& value):
        value(value)
    {

    }
    NGS_INLINE operator T& () { return value; }
    NGS_INLINE operator const T& () const{ return value; }
    NGS_INLINE T& operator=(const T& other) {value = other;}

    NGS_INLINE ParsingStruct* operator->() {
        return &parsing;
    }
};
template<class T>
union Parsing<T,VOID>
{
    T value;
    NGS_INLINE Parsing() = default;
    NGS_INLINE Parsing(const T& value) :
        value(value)
    {

    }
    NGS_INLINE operator T& () { return value; }
    NGS_INLINE operator const T& () const { return value; }
    NGS_INLINE T& operator=(const T& other) {value = other;}
};

template<class UINT,class ParsingStruct = VOID>
    requires UnsignedIntegral<UINT> || NGS::concepts::IsSame<UINT24, UINT>
struct Color
{
    Parsing<UINT, ParsingStruct> color;
    NGS_INLINE Color() = default;
    NGS_INLINE Color(UINT u):
        color(Parsing<UINT,ParsingStruct>(u))
    {

    }
    NGS_INLINE operator Parsing<UINT, ParsingStruct>&() { return color; }
    NGS_INLINE operator const Parsing<UINT, ParsingStruct>& ()const { return color; }

    NGS_INLINE operator UINT& () { return color; }
    NGS_INLINE operator const UINT& ()const { return color; }
};

struct RGB
{
    BYTE b;
    BYTE g;
    BYTE r;
};
struct ARGB
{
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;
};

using RGB8 = Color<UINT8>;
using RGB16 = Color<UINT16>;
using RGB24 = Color<UINT24,RGB>;
using RGB32 = Color<UINT32, ARGB>;

//template<class T>
//concept RGB = NGS::typetrait::IsSame<T, RGB8> ||
//NGS::typetrait::IsSame<T, RGB16> ||
//NGS::typetrait::IsSame<T, RGB24> ||
//NGS::typetrait::IsSame<T, RGB32>;


#endif // !__HEAD_Snake_Color
