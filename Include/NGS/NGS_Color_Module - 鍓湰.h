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

template<class Derived,_CPT Integral T,_TYP UINT8 B>
struct _RGB_Base
{
    //NGS_TYPE_DEFINE(_RGB_Base<Derived,T, B>, this);
    NGS_TYPE_DEFINE(Derived, derived);
    NGS_TYPE_DEFINE(_TYP UINT8, channel);

    using type = T;
    NGS_CONSTEXPR static auto filter = bit_max(B);
    NGS_CONSTEXPR static auto bits = B;

    T color;
    _RGB_Base() = default;
    NGS_CONSTEXPR
    _RGB_Base(T color):color(color){}
    _RGB_Base(__channel a, __channel r, __channel g, __channel b);

    NGS_CONSTEXPR
    operator T()const { return color; }
    NGS_CONSTEXPR
    __derived_ref operator=(type color) { this->color = color; return static_cast<__derived>(*this); }
    //auto operator<=>(__derived_ref_cst)const = default;

    NGS_CONSTEXPR type Color(type color) { this->color = color; }
    NGS_CONSTEXPR type Color(__channel a, __channel r, __channel g, __channel b);
    NGS_CONSTEXPR type Color()const { return color; }
    NGS_CONSTEXPR type& Color() { return color; }

    NGS_CONSTEXPR __channel Alpha()const;
    NGS_CONSTEXPR type Alpha(__channel);
    NGS_CONSTEXPR __channel Red()const;
    NGS_CONSTEXPR type Red(__channel);
    NGS_CONSTEXPR __channel Green()const;
    NGS_CONSTEXPR type Green(__channel);
    NGS_CONSTEXPR __channel Blue()const;
    NGS_CONSTEXPR type Blue(__channel);
};
struct RGB32 : _RGB_Base<RGB32,_TYP UINT32,32>{
    NGS_TYPE_DEFINE(RGB32, this);
    using base = _RGB_Base<__this, type, bits>;

    using base::_RGB_Base;
};
NGS_CONSTEXPR RGB32 operator""_rgb32(_TYP UINT64 num) { return num; }

struct RGB24 : _RGB_Base<RGB24, _TYP UINT32, 24> {
    NGS_TYPE_DEFINE(RGB24, this);
    using base = _RGB_Base<__this, type, bits>;

    using base::_RGB_Base;
};
NGS_CONSTEXPR RGB24 operator""_rgb24(_TYP UINT64 num) { return num; }

struct RGB16 : _RGB_Base<RGB16, _TYP UINT16, 16> {
    NGS_TYPE_DEFINE(RGB16, this);
    using base = _RGB_Base<__this, type, bits>;

    using base::_RGB_Base;
};
NGS_CONSTEXPR RGB16 operator""_rgb16(_TYP UINT64 num) { return num; }

struct RGB15 : _RGB_Base<RGB15, _TYP UINT16, 16> {
    NGS_TYPE_DEFINE(RGB15, this);
    using base = _RGB_Base<__this, type, bits>;

    using base::_RGB_Base;
};
NGS_CONSTEXPR RGB15 operator""_rgb15(_TYP UINT64 num) { return num; }

NGS_END

NGS_CONCEPT

template<class T>
concept RGB = _CPT Base<_TYP _RGB_Base<T,typename T::type,T::bits>,T>;
NGS_END

class Color {
public:
    NGS_TYPE_DEFINE(_TYP UINT8, channel);
    NGS_TYPE_DEFINE(_TYP RGB15, rgb15);
    NGS_TYPE_DEFINE(_TYP RGB16, rgb16);
    NGS_TYPE_DEFINE(_TYP RGB24, rgb24);
    NGS_TYPE_DEFINE(_TYP RGB32, rgb32);

    enum class RGBChannel : __channel {
        B = 0,
        G,
        R,
        A
    };
    enum class ColorFlag : _TYP BYTE {
        INVERSE = bit(0)       //是否反转RGB（不会反转alpha通道，alpha通道始终在最高位）
    };

public:
    /**
    * @brief 获取RGB相应通道的位数
    * 
    * @param [template] mode RGB类型
    * @param channel 通道
    * 
    * @return 通道位数
    */
    template<_CPT RGB mode>
    NGS_CONSTEXPR static
        _TYP UINT8 RGB_BitCount(RGBChannel channel) { return 8; }
    template<>
    NGS_CONSTEXPR static
        _TYP UINT8 RGB_BitCount<__rgb15>(RGBChannel channel) { return channel == RGBChannel::A ? 1 : 5; }
    template<>
    NGS_CONSTEXPR static
        _TYP UINT8 RGB_BitCount<__rgb16>(RGBChannel channel) { return RGB_BitCount<__rgb15>(channel) + (channel == RGBChannel::G); }
    
    
    /**
    * @brief 通道有多少位低位（不包括通道本身）
    * @brief e.g : 0xFF0000 channel == R --> 16
    * 
    * @param [template] mode RGB模式
    * @param channel 通道
    * 
    * @return 通道偏移
    */
    template<_CPT RGB mode, RGBChannel channel>
    NGS_CONSTEXPR static
        _TYP UINT8 RGB_BitOffset() {
        return
            RGB_BitCount<mode>(RGBChannel::A) * (RGBChannel::A < channel) +
            RGB_BitCount<mode>(RGBChannel::R) * (RGBChannel::R < channel) +
            RGB_BitCount<mode>(RGBChannel::G) * (RGBChannel::G < channel) +
            RGB_BitCount<mode>(RGBChannel::B) * (RGBChannel::B < channel)
            ;
    }

    /**
    * @brief 将通道各位数都取一
    * @brief e.g : mode == RGB16 channel == G -> 0x3F
    * 
    * @
    */
    template<_CPT RGB mode, RGBChannel channel>
    NGS_CONSTEXPR static
    _TYP UINT8 RGB_BitFilter() {return bit_max(RGB_BitCount<mode>(channel));}

    /**
    * @brief 不同RGB之间的通道转换
    * @brief e.g RGB32-R -> RGB15-R; RGB16-G -> RGB24-G;
    * 
    * @param value 通道值
    * 
    * @return 转换后的通道值
    */
    template<_CPT RGB mode_in,_CPT RGB mode_out, RGBChannel channel>
    NGS_CONSTEXPR static
    __channel RGB_Channel(__channel value) {
        return RGB_BitFilter<mode_out, channel>() * ((_TYP FLOAT64)(value) / (_TYP FLOAT64)RGB_BitFilter<mode_in, channel>());
    }

    /**
    * @brief 取出RGB某通道值，并转换为对应通道
    * @brief e.g RGB32 -> RGB15-R; RGB16 -> RGB24-G;
    *
    * @param rgb 颜色
    * 
    * @return rgb对应的通道值
    */
    template<_CPT RGB mode_in, _CPT RGB mode_out, RGBChannel channel>
    NGS_CONSTEXPR static
    __channel RGB_Channel(mode_in::type argb) {
        return RGB_Channel<mode_in, mode_out, channel>(__channel((argb >> RGB_BitOffset<mode_in, channel>()) & RGB_BitFilter<mode_in, channel>()));
    }
public:
    /**
    * @brief 设置RGB通道的值
    * @brief e.g RGB32-R = RGB15-R; RGB16-G = RGB24-G;
    *
    * @param [template] mode 颜色RGB类型
    * @param [template] channel 通道
    * @param [template] mode_channel 通道RGB类型
    * @param [out] rgb 颜色
    * @param [in] value 通道值
    * 
    * @return 改后的颜色
    */
    template<_CPT RGB mode_out, RGBChannel channel,_CPT RGB mode_channel = __rgb32>
    NGS_CONSTEXPR static mode_out::type RGB_Channel(mode_out::type argb, __channel value) {
        NGS_CONSTEXPR _TYP UINT8 offset = RGB_BitOffset<mode_out, channel>();
        return (argb & ~(RGB_BitFilter<mode_out, channel>() << offset)) | (RGB_Channel<mode_channel, mode_out, channel>(value) << offset);
    }

    template<_CPT RGB mode_out,_CPT RGB mode_in = __rgb32, _TYP BYTE flag = 0>
    NGS_CONSTEXPR static
        mode_out::type RGB(
        __channel alpha,
        __channel red,
        __channel green,
        __channel blue
    ) {
        return
            (
                (RGB_Channel<mode_in, mode_out, RGBChannel::A>(alpha)    << RGB_BitOffset<mode_out, RGBChannel::A>()) |
                (RGB_Channel<mode_in, mode_out, RGBChannel::R>(red)      << RGB_BitOffset<mode_out, RGBChannel::R>()) |
                (RGB_Channel<mode_in, mode_out, RGBChannel::G>(green)    << RGB_BitOffset<mode_out, RGBChannel::G>()) |
                (RGB_Channel<mode_in, mode_out, RGBChannel::B>(blue)     << RGB_BitOffset<mode_out, RGBChannel::B>())
            ) & mode_out::filter;
    }
    template<_CPT RGB mode_out, _CPT RGB mode_in = __rgb32, _TYP BYTE flag = 0>
    NGS_CONSTEXPR static
    mode_out::type RGB(
        mode_in::type argb
    ) {
        return
            (
                (RGB_Channel<mode_in, mode_out, RGBChannel::A>(argb) << RGB_BitOffset<mode_out, RGBChannel::A>()) |
                (RGB_Channel<mode_in, mode_out, RGBChannel::R>(argb) << RGB_BitOffset<mode_out, RGBChannel::R>()) |
                (RGB_Channel<mode_in, mode_out, RGBChannel::G>(argb) << RGB_BitOffset<mode_out, RGBChannel::G>()) |
                (RGB_Channel<mode_in, mode_out, RGBChannel::B>(argb) << RGB_BitOffset<mode_out, RGBChannel::B>())
                ) & mode_out::filter;
    }

    struct Blend {
    public:
        template<_CPT RGB mode = __rgb32>
        NGS_CONSTEXPR static __channel RGB_AlphaBlend(__channel alphaA, __channel alphaB) {
            _TYP UINT16 a = alphaA + 1;
            _TYP UINT16 b = alphaB + 1;
            return a + b - ((a * b) >> RGB_BitCount<mode>(RGBChannel::A)) - 1;
        }
        template<_CPT RGB mode = __rgb32>
        NGS_CONSTEXPR static __channel RGB_AlphaBlend(__channel fore, __channel back, __channel alphaF,__channel alphaB) {
            NGS_CONSTEXPR auto alpha_bitcount = RGB_BitCount<mode>(RGBChannel::A);
            NGS_CONSTEXPR auto alpha_bitmax = RGB_BitFilter<mode, RGBChannel::A>();
            auto alpha_blend = RGB_AlphaBlend<mode>(alphaF, alphaB);

            return ((fore * alphaF + (back * alphaB * (alpha_bitmax - alphaF) >> alpha_bitcount)) * alpha_blend) >> (alpha_bitcount << 1);
        }

        template<_CPT RGB mode = __rgb32>
        NGS_CONSTEXPR static mode::type RGB_AlphaBlend(mode::type fore, mode::type back) {
            mode result;
            mode foreground = fore;
            mode background = back;
            result.Alpha(RGB_AlphaBlend<mode>(foreground.Alpha(), background.Alpha()));
            result.Red(RGB_AlphaBlend<mode>(foreground.Red(),background.Red(), foreground.Alpha(), background.Alpha()));
            result.Green(RGB_AlphaBlend<mode>(foreground.Green(),background.Green(), foreground.Alpha(), background.Alpha()));
            result.Blue(RGB_AlphaBlend<mode>(foreground.Blue(),background.Blue(), foreground.Alpha(), background.Alpha()));
            return result;
        }
    };
};

template<_CPT RGB mode>
struct RGB_Default {
    NGS_INL_CSTEXPR static auto
        white = Color::RGB<mode>(0xFF,0xFF,0xFF,0xFF),//白色
        black = Color::RGB<mode>(0xFF,0x00,0x00,0x00),//黑色
        red = Color::RGB<mode>(0xFF,0xFF,0x00,0x00),//红色
        green = Color::RGB<mode>(0xFF,0x00,0xFF,0x00),//绿色
        blue = Color::RGB<mode>(0xFF,0x00,0x00,0xFF),//蓝色
        cyan = Color::RGB<mode>(0xFF,0x00,0xFF,0xFF),//青色
        purple = Color::RGB<mode>(0xFF,0xFF,0x00,0xFF),//紫色
        yellow = Color::RGB<mode>(0xFF,0xFF,0xFF,0x00),//黄色
        gray = Color::RGB<mode>(0xFF,0xC0,0xC0,0xC0),//灰色
        orange = Color::RGB<mode>(0xFF,0xFF,0x61,0x00),//橙色
        turquoise = Color::RGB<mode>(0xFF,0x40,0xE0,0xD0),//青蓝色
        pink = Color::RGB<mode>(0xFF,0xFF,0xC0,0xCB),//粉色
        transparency = Color::RGB<mode>(0x00,0x00,0x00,0x00)//透明
        ;
};
NGS_TYPE

template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INLINE _RGB_Base<Derived, T, B>::_RGB_Base(__channel a, __channel r, __channel g, __channel b) {
    Color(a, r, g, b);
}

template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::type _RGB_Base<Derived, T, B>::Color(__channel a, __channel r, __channel g, __channel b){
    return color = Color::RGB<Derived>(a, r, g, b);
}

template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::__channel _RGB_Base<Derived, T, B>::Alpha() const{
    return Color::RGB_Channel<Derived, Derived, Color::RGBChannel::A>(color);
}
template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::type _RGB_Base<Derived, T, B>::Alpha(__channel value){
    return color = Color::RGB_Channel<Derived, Color::RGBChannel::A, Derived>(color, value);
}

template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::__channel _RGB_Base<Derived, T, B>::Red() const {
    return Color::RGB_Channel<Derived, Derived, Color::RGBChannel::R>(color);
}
template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::type _RGB_Base<Derived, T, B>::Red(__channel value) {
    return color = Color::RGB_Channel<Derived, Color::RGBChannel::R, Derived>(color, value);
}

template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::__channel _RGB_Base<Derived, T, B>::Green() const {
    return Color::RGB_Channel<Derived, Derived, Color::RGBChannel::G>(color);
}
template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::type _RGB_Base<Derived, T, B>::Green(__channel value) {
    return color = Color::RGB_Channel<Derived, Color::RGBChannel::G,Derived>(color, value);
}

template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::__channel _RGB_Base<Derived, T, B>::Blue() const {
    return Color::RGB_Channel<Derived, Derived, Color::RGBChannel::B>(color);
}
template<class Derived, _CPT Integral T, _TYP UINT8 B>
NGS_INL_CSTEXPR _RGB_Base<Derived, T, B>::type _RGB_Base<Derived, T, B>::Blue(__channel value) {
    return color = Color::RGB_Channel<Derived, Color::RGBChannel::B, Derived>(color, value);
}

NGS_END

NGS_END

#endif // !__HEAD_NGS_Color_Module
