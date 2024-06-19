//==========================================================================================================
// @file	:	Encode_Module
// @author	:	NAGISA
// @data	:	2023/2/5 22:52:00
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Encode_Module
#define __HEAD_Encode_Module

#include "NGS/NGS.h"
#include "NDA/Bitmap.h"

NGS_BEGIN

class Encoder {
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(BitmapData, data);

    NGS_INL_CSTEXPR static auto
        IS_VERTICAL = bit(0),
        RIGHT_TO_LEFT = bit(1),
        BOTTOM_TO_TOP = bit(2),
        BYTE_INVERSE = bit(3),
        IS_BIT = bit(4),
        SET = bit(5)
        ;

private:
    template<_TYP FLAG flag = 0>
    NGS_CONSTEXPR static _TYP VOID _PositionTrans(
        __size width, __size height,
        __size& x, __size& y
    ) {
        if NGS_CONSTEXPR(Bits(flag, RIGHT_TO_LEFT))
            x = width - x;
        if NGS_CONSTEXPR(Bits(flag, BOTTOM_TO_TOP))
            y = height - y;
    }


    template<_TYP FLAG flag = 0>
    NGS_CONSTEXPR static auto _DirectTrans(
        __size width, __size height,
        __size x, __size y
    ) {
        if NGS_CONSTEXPR(Bits(flag, IS_VERTICAL))
            return x * height + y;
        else
            return y * width + x;
    }


    template<_TYP FLAG flag = 0, _CPT UnsignedIntegral DataType>
    NGS_CONSTEXPR static _TYP VOID _EndianTrans(
        DataType& data
    ) {
        if NGS_CONSTEXPR(std::endian::native == std::endian::little)
            ByteInverse(data);
        if NGS_CONSTEXPR(Bits(flag, BYTE_INVERSE))
            ByteInverse(data);
    }


    template<_TYP FLAG flag = 0, _CPT UnsignedIntegral DataType>
    NGS_CONSTEXPR static __size _DataTrans(
        DataType data = 0
    ) {
        if NGS_CONSTEXPR(Bits(flag, IS_BIT))
            return BitsOf<DataType>();
        else
            return sizeof(DataType);
    }


public:
    template<_TYP FLAG flag = 0, _CPT UnsignedIntegral DataType = _TYP BYTE>
    NGS_CONSTEXPR static DataType ByteTransform(
        const DataType* data,
        __size width,
        __size height,
        __size x,
        __size y
    ) {
        _PositionTrans<flag>(width, height, x, y);
        __size sz = _DirectTrans<flag>(width, height, x, y);
        NGS_CONSTEXPR auto unit = _DataTrans<flag,DataType>();

        DataType byte = data[sz];

        _EndianTrans<flag>(byte);

        if NGS_CONSTEXPR(Bits(flag, SET)) {
            auto setData = const_cast<DataType*>(data);
            setData[sz] = byte;
        }

        return byte;
    }

    template<_TYP FLAG flag = 0, _CPT UnsignedIntegral DataType = _TYP BYTE>
    NGS_CONSTEXPR static _TYP BYTE BitTransform(
        const DataType* data,
        __size width,
        __size height,
        __size x,
        __size y
    ) {
        _PositionTrans<flag | IS_BIT>(width, height, x, y);
        __size sz = _DirectTrans<flag | IS_BIT>(width, height, x, y);
        NGS_CONSTEXPR auto unit = _DataTrans<flag | IS_BIT, DataType>();

        DataType byte = data[sz / unit];

        _EndianTrans<flag>(byte);

        __size mode = (unit - 1) - (sz % unit);

        if NGS_CONSTEXPR(Bits(flag, SET)) {
            auto setData = const_cast<DataType*>(data);
            Bits(setData[sz / unit], bit(mode), Bits(byte, bit(mode)));
        }

        return Bits(byte, bit(mode));
    }

    

    template<_TYP FLAG flag = 0,_CPT UnsignedIntegral DataType = _TYP BYTE, NDA_TYPE_COLOR_T yin = RGB_Default<NDA_TYPE_COLOR>::white, NDA_TYPE_COLOR_T yang = RGB_Default<NDA_TYPE_COLOR>::black>
    static __data_ptr Font(
        const DataType* data,
        __size width,
        __size height
    ) {
        __data_ptr bitmapData = New(new BitmapData(width, height, (BitmapData::__color)0));
        for (__size y = 0; y < height; y++){
            for (__size x = 0; x < width; x++){
                (*bitmapData)(x, y) = BitTransform<flag,DataType>(data,width,height,x, y) ? yang : yin;
            }
        }

        return bitmapData;
    }
    template<_CPT UnsignedIntegral DataType = _TYP BYTE, _TYP FLAG flag = 0>
    static _TYP VOID Font_ModelTrans(
        _TYP PCVOID data,
        __size width,
        __size height
    ) {
        for (__size y = 0; y < height; y++) {
            for (__size x = 0; x < width; x++) {
                BitTransform<flag | SET, DataType>((DataType*)data, width, height, x, y);
            }
        }
    }

    template<_CPT RedGreenBlue rgb, _TYP FLAG flag = 0>
    static __data_ptr RGB_Model(
        _TYP PCVOID data,
        __size width,
        __size height
    ) {
        using DataType = typename rgb::type;
        __data_ptr bitmapData = New(new BitmapData(width, height, (BitmapData::__color)0));
        for (__size y = 0; y < height; y++) {
            for (__size x = 0; x < width; x++) {
                auto color = ByteTransform<flag, DataType>((DataType*)data, width, height, x, y);
                (*bitmapData)(x, y) = BitmapData::__rgb::In<rgb>(color);
            }
        }

        return bitmapData;
    }
    template<_CPT RedGreenBlue mode, _TYP FLAG flag = 0>
    static _TYP VOID RGB_ModelTrans(
        _TYP PCVOID data,
        __size width,
        __size height
    ) {
        using DataType = typename mode::type;
        for (__size y = 0; y < height; y++) {
            for (__size x = 0; x < width; x++) {
                ByteTransform<flag | SET, DataType>((DataType*)data, width, height, x, y);
            }
        }
    }
};

NGS_END

#endif // !__HEAD_Encode_Module
