//==========================================================================================================
// @file	:	Text_Module
// @author	:	NAGISA
// @data	:	2023/2/10 14:08:19
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Text_Module
#define __HEAD_Text_Module

#include "NGS/NGS.h"
#include "NDA/Bitmap.h"
#include "NDA/Encode.h"

extern const auto GetTextFontData(_TYP CHAR8);

NGS_BEGIN

template<
    _TYP UINT32 width_,
    _TYP UINT32 height_,
    _TYP FLAG flag_ = 0,
    _CPT UnsignedIntegral DataType_ = _TYP BYTE,
    NDA_TYPE_COLOR_T yin_ = RGB_Default<NDA_TYPE_COLOR>::white,
    NDA_TYPE_COLOR_T yang_ = RGB_Default<NDA_TYPE_COLOR>::black,
    _TYP CHAR8 offset_ = 0,
    _TYP UINT32 gapx_ = 0,
    _TYP UINT32 gapy_ = 0
>struct FontMessage{
    using DataType = DataType_;
    using PDataType = DataType*;
    NGS_INL_CSTEXPR static auto width = width_;
    NGS_INL_CSTEXPR static auto height = height_;
    NGS_INL_CSTEXPR static auto gapx = gapx_;
    NGS_INL_CSTEXPR static auto gapy = gapy_;
    NGS_INL_CSTEXPR static auto yin = yin_;
    NGS_INL_CSTEXPR static auto yang = yang_;
    NGS_INL_CSTEXPR static auto flag = flag_;
    NGS_INL_CSTEXPR static auto offset = offset_;

    NGS_CONSTEXPR FontMessage() {}
};


template<class FontMessage>
struct FontCache {
#undef CreateFont
private:
    using data = FontMessage::PDataType;
public:
    template<_TYP CHAR8 c>
    NGS_INLINE static const BitmapData*
        font = Encoder::Font<Encoder::IS_VERTICAL, FontMessage::DataType, FontMessage::yin, FontMessage::yang>(
            (data)GetTextFontData(c - FontMessage::offset),
            FontMessage::width, 
            FontMessage::height
            );

private:
};

class TextFieldBase : public DisplayObject{
public:
    NGS_TYPE_DEFINE(DisplayObject, base);
    NGS_TYPE_DEFINE(std::wstring_view, text);
    NGS_TYPE_DEFINE(Vector2D<_TYP INT8>, gap);
    NGS_TYPE_DEFINE(_TYP PCSTR8, str);
    
    NGS_INL_CSTEXPR static _TYP FLAG
        F_IS_VERTICAL = bit(0),
        F_IS_CENTER_LEVEL = bit(1),
        F_IS_CENTER_VERTICAL = bit(2)
        ;

public:
    TextFieldBase(__text text = L" ") :
        _text(text)
    {
        Bits<TRUE>(_flag, DRAWABLE);
    }

    NGS_GET_REF(Text, _text);
    //__text_ref Text() { return _text; }
    //__text_ref_cst Text()const { return _text; }
    _TYP VOID Text(__text string) {
        Redraw(TRUE);
        _text = string;
    }
    NGS_FLAG(LevelCenter, _text_flag, F_IS_CENTER_LEVEL);
    NGS_FLAG(VerticalCenter, _text_flag, F_IS_CENTER_VERTICAL);

protected:
    _TYP FLAG _text_flag = 0;
    __text _text;
};

template<class FontMessage>
class TextField : public TextFieldBase{
public:
    NGS_TYPE_DEFINE(TextFieldBase, base);
    using DataType = FontMessage::DataType;
    NGS_TYPE_DEFINE(DataType, data);
    NGS_TYPE_DEFINE(__data_ptr, datas);
public:
    using __base::TextFieldBase;

    NDA_TYPE_COLOR_T Pixels(__size x, __size y)const final override {
        x -= _bounds.x;
        y -= _bounds.y;
        NGS_CONSTEXPR auto w = FontMessage::width + FontMessage::gapx;
        NGS_CONSTEXPR auto h = FontMessage::height + FontMessage::gapy;
        __size ix = x / w;
        __size iy = y / h;

        return Encoder::BitTransform<FontMessage::flag, typename FontMessage::DataType>(
            (__datas)GetTextFontData(_text[ix] - FontMessage::offset),
            FontMessage::width,
            FontMessage::height,
            x - ix * w,
            y - iy * h
            ) ? FontMessage::yin : FontMessage::yang;
    }
    using __base::Resize;
    _TYP VOID Resize()final override {
        __base::Resize();
        
        _bounds.width = (FontMessage::width + FontMessage::gapx) * _text.size();
        _bounds.height = (FontMessage::height + FontMessage::gapy) * 1;

        auto center_level = Bits(_text_flag, F_IS_CENTER_LEVEL);
        auto center_vertical = Bits(_text_flag, F_IS_CENTER_VERTICAL);
        _bounds.x = center_level * -_bounds.width / 2;
        _bounds.y = center_vertical * -_bounds.height / 2;
    }
};


NGS_END

#endif // !__HEAD_Text_Module
