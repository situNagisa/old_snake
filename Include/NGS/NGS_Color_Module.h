//==========================================================================================================
// @file	:	NGS_Color_Module
// @author	:	NAGISA
// @data	:	2023/2/6 11:32:35
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Color_Module
#define __HEAD_NGS_Color_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Concepts.h"
#include "NGS/NGS_TypeTrait.h"
#include "NGS/NGS_Bit.h"
#include "NGS/NGS_TemplateMetaBase.h"

NGS_EXPORT
NGS_BEGIN

NGS_TYPE

template<_TYP SIZE_T32 BIT_COUNT,_TYP SIZE_T32>
    requires (BIT_COUNT <= 8)
struct Channel;

using Channel8 = typename Channel<8,0>;

template<_TYP SIZE_T32, _TYP SIZE_T32, _TYP SIZE_T32, _TYP SIZE_T32>
struct RGB;

using RGB32 = RGB<8, 8, 8, 8>;
using RGB24 = RGB<0, 8, 8, 8>;
using RGB16 = RGB<0, 5, 6, 5>;
using RGB15 = RGB<0, 5, 5, 5>;
using RGB8 =  RGB<0, 3, 3, 2>;
NGS_END

NGS_TYPE_TRAIT

template<class T>
struct IsChannel { constexpr static auto value = FALSE;  };
template<template<_TYP SIZE_T32, _TYP SIZE_T32>class T, _TYP SIZE_T32 B, _TYP SIZE_T32 O>
struct IsChannel<T<B,O>> {
    constexpr static auto value = _CPT Same<T<B, O>, _TYP Channel<B, O>>;
};

template<class T>
struct IsRGB { constexpr static auto value = FALSE; };
template<template<_TYP SIZE_T32, _TYP SIZE_T32, _TYP SIZE_T32, _TYP SIZE_T32>class T, _TYP SIZE_T32 A, _TYP SIZE_T32 R, _TYP SIZE_T32 G, _TYP SIZE_T32 B>
struct IsRGB<T<A,R,G,B>> {
    constexpr static auto value = _CPT Same<T<A, R, G, B>, _TYP RGB<A, R, G, B>>;
};

NGS_END


NGS_CONCEPT

template<class T>
concept Channel = _TYT IsChannel<T>::value;

template<class T>
concept RedGreenBlue = _TYT IsRGB<T>::value;

NGS_END

NGS_TYPE

template<_TYP SIZE_T32 BIT_COUNT, _TYP SIZE_T32 OFFSET = 0>
    requires (BIT_COUNT <= 8)
struct Channel {
    NGS_TYPE_DEFINE(Channel, this);
    NGS_DEFAULT_TYPE;
public:
    /*@brief 该通道占多少比特*/
    constexpr static auto count = BIT_COUNT;
    /*@brief 该通道的滤值*/
    constexpr static auto filter = bit_max(BIT_COUNT);
    /*@brief 该通道的偏移*/
    constexpr static auto offset = OFFSET;
    /*@brief 保存该通道的值至少需要几字节*/
    using type = BYTES<ByteOf(count)>;

    template<_CPT Channel IsChannel = Channel8>
    constexpr static type In(IsChannel::type value) {
        NGS_CST_IF(_CPT Same<IsChannel, __this>) {
            return value;
        }NGS_CST_ELSE{
            return (_TYP FLOAT64)value / IsChannel::filter * filter;
        }
    }
private:
    Channel() = default;
};

template<_TYP SIZE_T32 ALPHA_BITS, _TYP SIZE_T32 RED_BITS, _TYP SIZE_T32 GREEN_BITS, _TYP SIZE_T32 BLUE_BITS>
struct RGB
{
private:
    using __this = RGB<ALPHA_BITS, RED_BITS, GREEN_BITS, BLUE_BITS>;
    NGS_TYPE_DEFINE(__this, this);

public:
    using B = Channel<BLUE_BITS>;
    using G = Channel<GREEN_BITS, BLUE_BITS>;
    using R = Channel<RED_BITS, GREEN_BITS + BLUE_BITS>;
    using A = Channel<ALPHA_BITS, RED_BITS + GREEN_BITS + BLUE_BITS>;
    using type = BYTES<ByteOf(ALPHA_BITS + RED_BITS + GREEN_BITS + BLUE_BITS)>;

    template<_CPT RedGreenBlue in = RGB32>
    constexpr static type In(
        in::A::type a,
        in::R::type r,
        in::G::type g,
        in::B::type b
    ) {
        return
            ((A::In<in::A>(a) & A::filter) << A::offset) |
            ((R::In<in::R>(r) & R::filter) << R::offset) |
            ((G::In<in::G>(g) & G::filter) << G::offset) |
            ((B::In<in::B>(b) & B::filter) << B::offset)
            ;
    }
    template<_CPT RedGreenBlue in = RGB32>
    constexpr static type In(in::type argb) {
        return
            (A::In<in::A>((argb >> in::A::offset) & (in::A::filter)) << A::offset) |
            (R::In<in::R>((argb >> in::R::offset) & (in::R::filter)) << R::offset) |
            (G::In<in::G>((argb >> in::G::offset) & (in::G::filter)) << G::offset) |
            (B::In<in::B>((argb >> in::B::offset) & (in::B::filter)) << B::offset)
            ;
    }
    /**
    * @brief 生成rgb
    * 
    * @param argb 
    */
    constexpr RGB(type argb) :
        _value(argb)
    {}

    constexpr RGB(
        A::type a,
        R::type r,
        G::type g,
        B::type b
    ) :
        _value(In<RGB32>(a, r, g, b))
    {}

    constexpr operator type() const noexcept { return _value; }

    template<_CPT RedGreenBlue out = __this>
    constexpr out::A::type Alpha()const { return out::A::In<A>((_value >> A::offset) & A::filter); }
    template<_CPT RedGreenBlue in = __this>
    constexpr _TYP VOID Alpha(in::A::type a)const { (_value & ~(in::A::filter << in::A::offset)) | (a << in::A::offset); }

    template<_CPT RedGreenBlue out = __this>
    constexpr out::R::type Red()const { return out::R::In<R>((_value >> R::offset) & R::filter); }
    template<_CPT RedGreenBlue in = __this>
    constexpr _TYP VOID Red(in::R::type r)const { (_value & ~(in::R::filter << in::R::offset)) | (r << in::R::offset); }

    template<_CPT RedGreenBlue out = __this>
    constexpr out::G::type Green()const { return out::G::In<G>((_value >> G::offset) & G::filter); }
    template<_CPT RedGreenBlue in = __this>
    constexpr _TYP VOID Green(in::G::type g)const { (_value & ~(in::G::filter << in::G::offset)) | (g << in::G::offset); }

    template<_CPT RedGreenBlue out = __this>
    constexpr out::B::type Blue()const { return out::B::In<B>((_value >> B::offset) & B::filter); }
    template<_CPT RedGreenBlue in = __this>
    constexpr _TYP VOID Blue(in::B::type b)const { (_value & ~(in::B::filter << in::B::offset)) | (b << in::B::offset); }
private:
    type _value = 0;
};

NGS_END

class Color {
public:
    NGS_TYPE_DEFINE(_TYP UINT8, channel);

    struct Blend {
    public:
        template<_CPT RedGreenBlue rgb = _TYP RGB32>
        constexpr static rgb::A::type RGB_AlphaBlend(rgb::A::type alphaA, rgb::A::type alphaB) {
            _TYP UINT16 a = alphaA + 1;
            _TYP UINT16 b = alphaB + 1;
            return a + b - ((a * b) >> rgb::A::count) - 1;
        }
        template<_CPT RedGreenBlue rgb = _TYP RGB32>
        NGS_CONSTEXPR static __channel RGB_AlphaBlend(__channel fore, __channel back, __channel alphaF, __channel alphaB) {
            NGS_CONSTEXPR auto alpha_bitcount = rgb::A::count;
            NGS_CONSTEXPR auto alpha_bitmax = rgb::A::filter;
            auto alpha_blend = RGB_AlphaBlend<rgb>(alphaF, alphaB);

            return ((fore * alphaF + (back * alphaB * (alpha_bitmax - alphaF) >> alpha_bitcount)) * alpha_blend) >> (alpha_bitcount << 1);
        }

        template<_CPT RedGreenBlue rgb = _TYP RGB32>
        constexpr static rgb::type RGB_AlphaBlend(rgb::type fore, rgb::type back) {
            rgb result{ 0 };
            rgb foreground = fore;
            rgb background = back;
            result.Alpha(RGB_AlphaBlend<rgb>(foreground.Alpha(), background.Alpha()));
            result.Red(RGB_AlphaBlend<rgb>(foreground.Red(), background.Red(), foreground.Alpha(), background.Alpha()));
            result.Green(RGB_AlphaBlend<rgb>(foreground.Green(), background.Green(), foreground.Alpha(), background.Alpha()));
            result.Blue(RGB_AlphaBlend<rgb>(foreground.Blue(), background.Blue(), foreground.Alpha(), background.Alpha()));
            return result;
        }
    };
};

template<_CPT RedGreenBlue rgb>
struct RGB_Default {
    NGS_INL_CSTEXPR static rgb::type
        white   = rgb(0xFF,0xFF,0xFF,0xFF),//白色
        black   = rgb(0xFF,0x00,0x00,0x00),//黑色
        red     = rgb(0xFF,0xFF,0x00,0x00),//红色
        green   = rgb(0xFF,0x00,0xFF,0x00),//绿色
        blue    = rgb(0xFF,0x00,0x00,0xFF),//蓝色
        cyan    = rgb(0xFF,0x00,0xFF,0xFF),//青色
        purple  = rgb(0xFF,0xFF,0x00,0xFF),//紫色
        yellow  = rgb(0xFF,0xFF,0xFF,0x00),//黄色
        gray    = rgb(0xFF,0xC0,0xC0,0xC0),//灰色
        orange  = rgb(0xFF,0xFF,0x61,0x00),//橙色
        turquoise = rgb(0xFF,0x40,0xE0,0xD0),//青蓝色
        pink    = rgb(0xFF,0xFF,0xC0,0xCB),//粉色
        transparency = rgb(0x00,0x00,0x00,0x00)//透明
        ;
};

NGS_END

#endif // !__HEAD_NGS_Color_Module
