//==========================================================================================================
// @file	:	NGS_Defined_Module
// @author	:	NAGISA
// @data	:	2023/1/16 18:15:24
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Defined_Module
#define __HEAD_NGS_Defined_Module

#include "NGS/NGS_Module.h"
#include "NGS/NGS_Defined_Macro.h"
#include "NGS/NGS_STL_Macro.h"

NGS_EXPORT
NGS_BEGIN

NGS_TYPE
//void
typedef void                VOID, * PVOID;
typedef const VOID*         PCVOID;

//char
_NGS_TYPE_DEFINE(char, CHAR8);
_NGS_TYPE_DEFINE(char16_t, CHAR16);
_NGS_TYPE_DEFINE(char32_t, CHAR32);
typedef const CHAR8         * PCCHAR8, * PCSTR8;
typedef const CHAR16        * PCCHAR16, * PCSTR16;
typedef const CHAR32        * PCCHAR32, * PCSTR32;

_NGS_TYPE_DEFINE(wchar_t, WCHAR);
typedef PCWCHAR        PCWCHAR;

//typedef wchar_t				_CHAR, * _PCHAR, * const _PCCHAR;
//typedef _CHAR* _STRING, * _PSTRING, * const _PCSTRING;

//int
_NGS_TYPE_DEFINE(signed char, INT8);
_NGS_TYPE_DEFINE(signed short, INT16);
_NGS_TYPE_DEFINE(signed long, INT32);
_NGS_TYPE_DEFINE(signed long long, INT64);

_NGS_TYPE_DEFINE(unsigned char, UINT8);
_NGS_TYPE_DEFINE(unsigned short, UINT16);
_NGS_TYPE_DEFINE(unsigned long, UINT32);
_NGS_TYPE_DEFINE(unsigned long long, UINT64);

_NGS_TYPE_DEFINE(unsigned short, SIZE_T16);
_NGS_TYPE_DEFINE(unsigned long, SIZE_T32);
_NGS_TYPE_DEFINE(unsigned long long, SIZE_T64);

//float
_NGS_TYPE_DEFINE(float, FLOAT32);
_NGS_TYPE_DEFINE(double, FLOAT64);

//bool
_NGS_TYPE_DEFINE(bool, BOOL);
//NGS_INL_CSTEXPR const BOOL	TRUE	= 1;
//NGS_INL_CSTEXPR const BOOL	FALSE	= 0;

//word
_NGS_TYPE_DEFINE(unsigned short, WORD);

_NGS_TYPE_DEFINE(unsigned int, DWORD);
_NGS_TYPE_DEFINE(unsigned long, DWORD32);
_NGS_TYPE_DEFINE(unsigned long long, DWORD64);


//byte
_NGS_TYPE_DEFINE(unsigned char, BYTE);
/*
template<UINT8 N>
struct by
{
    NGS_TYPE_DEFINE(by, this);

    constexpr by() {};
    template<class T>
        requires std::is_arithmetic_v<T>
    consteval by(T&& v) {
        for (_TYP SIZE_T32 i = 0; i < N; i++) 
            _data[i] = BYTE(value >> (i * 8));
    }
    
    template<class T>
        requires std::is_arithmetic_v<T>
    explicit(false) consteval operator T&&()const { 
        T value;
        for (_TYP SIZE_T32 i = 0; i < N; i++)
            value |= (T(_data[i]) << (i * 8));
        return value;
    }

    template<class T>
        requires std::is_arithmetic_v<T>
    __this_ref operator=(T v) { (*(T*)_data) = v; return *this; }

    constexpr auto operator<=>(__this_ref_cst)const = default;
private:
    BYTE _data[N];
};*/
template<UINT8 N>
requires (N <= 8)
struct _BYTES { using type = BYTE; };
template<>
struct _BYTES<1> { using type = UINT8; };
template<>
struct _BYTES<2> { using type = UINT16; };
template<>
struct _BYTES<3> { using type = UINT32; };
template<>
struct _BYTES<4> { using type = UINT32; };
template<>
struct _BYTES<5> { using type = UINT64; };
template<>
struct _BYTES<6> { using type = UINT64; };
template<>
struct _BYTES<7> { using type = UINT64; };
template<>
struct _BYTES<8> { using type = UINT64; };

template<UINT8 N>
using BYTES = _BYTES<N>::type;

_NGS_TYPE_DEFINE(BYTES<sizeof(PVOID)>, PTR);

NGS_END


NGS_END

#endif // !__HEAD_NGS_Defined_Module
