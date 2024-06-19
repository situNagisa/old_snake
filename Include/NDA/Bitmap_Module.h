//==========================================================================================================
// @file	:	Bitmap_Module
// @author	:	NAGISA
// @data	:	2023/1/30 14:41:00
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Bitmap_Module
#define __HEAD_Bitmap_Module

#include "NGS/NGS.h"
#include "NDA/DisplayObject.h"
#include "NDA/NDA_Defined.h"


NGS_BEGIN
struct BitmapData
{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(BitmapData, this);
    NGS_TYPE_DEFINE(DisplayObject, display);
    NGS_TYPE_DEFINE(_TYP SIZE_T16, size);
    NGS_TYPE_DEFINE(NDA_TYPE_COLOR, rgb);
    NGS_TYPE_DEFINE(NDA_TYPE_COLOR_T, color);

    NGS_INL_CSTEXPR static auto
        IS_MONOCHROME = bit(0),
        NEED_DISPOSE = bit(1)
        ;
public:
    BitmapData(
        __size width,
        __size height,
        __color_ptr data
    ):
        width(width),
        height(height),
        _width(width),
        _flag(0),
        _data(data)
    {}
    BitmapData(
        __size width,
        __size height,
        __color color,
        _TYP BOOL isMonochrome = FALSE
    ) :
        width(width),
        height(height),
        _width(isMonochrome ? 0 : width),
        _flag(isMonochrome ? (IS_MONOCHROME) : (NEED_DISPOSE)),
        _data(Malloc<__color>(isMonochrome ? 1 : width * height))
    {
        MemorySet<__color>(_data, color, isMonochrome ? 1 : width * height);
    }
    ~BitmapData() {
        if (Bits(_flag, NEED_DISPOSE))Dispose();
    }

    __color_ref operator()(__size x, __size y) { return _data[y * _width + x * !Bits(_flag,IS_MONOCHROME)]; }
    __color_ref_cst operator()(__size x, __size y)const { return _data[y * _width + x * !Bits(_flag, IS_MONOCHROME)]; }
    __color_ref operator[](__size index) { return _data[index]; }
    __color_ref_cst operator[](__size index)const { return _data[index]; }

    __color_ref Pixels(__size x, __size y) { return (*this)(x, y); }
    __color_ref_cst Pixels(__size x, __size y)const { return (*this)(x, y); }

    _TYP VOID DrawPoint(__color color ,__size x, __size y) {(*this)(x, y) = color;}
    _TYP VOID DrawPoint(__color color ,__vector_ref_cst pos) {(*this)(pos.x, pos.y) = color;}

    _TYP VOID DrawLine_Level(__color color , __size x, __size y, __size width) {
#pragma omp parallel for
        for (int i = 0; i < width; i++)
            DrawPoint(color,x + i, y);
    }
    _TYP VOID DrawLine_Vertical(__color color , __size x, __size y, __size height) {
#pragma omp parallel for
        for (int i = 0; i < height; i++)
            DrawPoint(color,x, y + i);
    }
    _TYP VOID DrawLine(__color color , __size x1, __size y1, __size x2, __size y2) {
        __size dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
        __size dy = abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
        int erro = (((dx > dy) ? dx : -dy) / 2);

        if (!dy) {
            DrawLine_Level(color,x1, y1, dx + 1);
            return;
        }
        if (!dx) {
            DrawLine_Vertical(color,x1, y1, dy + 1);
            return;
        }
        while ((x1 != x2) || (y1 != y2)) {
            int e2 = erro;
            DrawPoint(color,x1, y1 );
            if (e2 > -dx) {
                erro -= dy;
                x1 += sx;
            }
            if (e2 < dy) {
                erro += dx;
                y1 += sy;
            }
        }
    }
    _TYP VOID DrawLine(__color color, __vector_ref_cst a, __vector_ref_cst b) {
        DrawLine(color, a.x, a.y, b.x, b.y);
    }
    _TYP VOID DrawRect(__color color , __size x, __size y, __size width, __size height) {
        DrawLine_Level(color,x,y,width);
        DrawLine_Level(color,x,y + height - 1,width);
        DrawLine_Vertical(color , x, y, height);
        DrawLine_Vertical(color, x + width - 1, y, height);
    }
    _TYP VOID DrawRect(__color color, __rect_ref_cst rect) {
        DrawRect(color, rect.x, rect.y, rect.width, rect.height);
    }
    _TYP VOID DrawRect(__color color, __rect_ref_cst rect, __matrix_ref_cst matrix) {
        auto&& lt = rect.LeftTop() << matrix;
        auto&& lb = rect.LeftBottom() << matrix;
        auto&& rt = rect.RightTop() << matrix;
        auto&& rb = rect.RightBottom() << matrix;

        DrawLine(color, lt, rt);
        DrawLine(color, lb, rb);
        DrawLine(color, lt, lb);
        DrawLine(color, rt, rb);
    }

    _TYP VOID BlendPoint(__color color , __size x, __size y) {
        (*this)(x, y) = Color::Blend::RGB_AlphaBlend<__rgb>(color, (*this)(x, y)); 
    }

    _TYP VOID Fill(__color color, __size x, __size y, __size width, __size height) {
//#pragma omp parallel for
        for (int y_ = 0; y_ < height; y_++){
//#pragma omp parallel for
            for (int x_ = 0; x_ < width; x_++)
                DrawPoint(color,x + x_, y + y_);
        }
    }
    _TYP VOID Fill(__color color) {
        Fill(color, 0, 0, width, height);
    }
    _TYP VOID Fill(__color color, __rect_ref_cst rect) {
        Fill(color, rect.x, rect.y, rect.width, rect.height);
    }
    _TYP VOID Fill(__color color, __rect_ref_cst rect, __matrix_ref_cst matrix) {
        __size w = rect.width;
        __size h = rect.height;
//#pragma omp parallel for
        for (int y_ = 0; y_ < w; y_++) {
//#pragma omp parallel for
            for (int x_ = 0; x_ < h; x_++) {
                DrawPoint(color, matrix.TransformPoint({ rect.x + x_ , rect.y + y_ }));
            }
        }
    }

    template<_CPT Drawable Display>
    __this_ref Draw(
        const Display& display,
        __rect_ref_cst rect,
        __matrix_ref_cst matrix
    ) {
        auto&& area = Bounds();
        area.width--;
        area.height--;
        area &= rect;
        if (!area)return *this;

        __num deter = matrix.Determinant();
        __rect e(matrix.TransformPoint({ 0,0 }), matrix.TransformPoint({ 1,1 }));
        __rect bounds = display.Bounds();
        int l = bounds.Left();
        int t = bounds.Top();
        int b = bounds.Bottom();
        int r = bounds.Right();

        if (!deter)return *this;
        else if (matrix.b || matrix.c) {
            if (deter <= 1) {
                for (int y = t; y < b; y++) {
                    //#pragma omp parallel for
                    for (int x = l; x < r; x++) {
                        auto color = display.Pixels(x, y);
                        //бли╚узуж
                        if (color == NDA_TYPE_COLOR(0x00, 0x00, 0xFF, 0x00))continue;

                        __vector position(x,y);
                        position <<= matrix;
                        position.x = ::round(position.x);
                        position.y = ::round(position.y);
                        if (!area.Contain(position.x, position.y))continue;

                        DrawPoint(color, position);
                        //canvas.BlendPoint(display.Pixels(x, y) , static_cast<__size>(position.x), static_cast<__size>(position.y));
                    }
                }
                return *this;
            }
            int sx = Ceil(matrix.ScaleX());
            int sy = Ceil(matrix.ScaleY());
            for (int y = t; y < b; y++) {
                //#pragma omp parallel for
                for (int x = l; x < r; x++) {
                    auto color = display.Pixels(x, y);
                    //бли╚узуж
                    if (color == NDA_TYPE_COLOR(0x00, 0x00, 0xFF, 0x00))continue;

                    __vector position(x, y);
                    position <<= matrix;
                    position.x = ::round(position.x);
                    position.y = ::round(position.y);
                    __rect drawRect(position.x,position.y, sx,sy);
                    drawRect.Normalize();
                    if (!(drawRect &= area))continue;
                    Fill(color, drawRect);
                }
            }
            return *this;
        }
        else if (deter <= 1) {
            for (int y = t; y < b; y++) {
                //#pragma omp parallel for
                for (int x = l; x < r; x++) {
                    auto color = display.Pixels(x, y);
                    //бли╚узуж
                    if (color == NDA_TYPE_COLOR(0x00, 0x00, 0xFF, 0x00))continue;

                    __vector position(e.x + e.width * x, e.y + e.height * y);
                    //
                    if (!area.Contain(position.x, position.y))continue;

                    DrawPoint(color, position);
                    //canvas.BlendPoint(display.Pixels(x, y) , static_cast<__size>(position.x), static_cast<__size>(position.y));
                }
            }
            return *this;
        }
        e.width = ::round(e.width);
        e.height = ::round(e.height);
        for (int y = t; y < b; y++) {
            //#pragma omp parallel for
            for (int x = l; x < r; x++) {
                auto color = display.Pixels(x, y);
                //бли╚узуж
                if (color == NDA_TYPE_COLOR(0x00, 0x00, 0xFF, 0x00))continue;

                __rect drawRect(
                    e.x + e.width * x,
                    e.y + e.height * y,
                    e.width, e.height
                );
                if (!(drawRect &= area))continue;
                Fill(color, drawRect);
            }
        }
        return *this;
    }

    template<_CPT Drawable Display>
    __this_ref Draw(
        const Display& display,
        __matrix_ref_cst matrix
    ) {
        return Draw(display, display.Bounds() << matrix, matrix);
    }
    _TYP VOID Dispose() { Free(_data); }

    __rect Bounds()const { return { 0,0,(__num)width,(__num)height }; }

    __size Width()const { return width; }
    __size Height()const { return height; }
private:

public:
    __size_cst width;
    __size_cst height;

private:
    __size_cst _width;
    _TYP BYTE _flag;
    const __color_ptr _data;
};

class Bitmap : public DisplayObject {
public:
    NGS_TYPE_DEFINE(DisplayObject,base)
    NGS_TYPE_DEFINE(Bitmap, this);
    NGS_TYPE_DEFINE(BitmapData, data);

public:
    Bitmap() = default;
    Bitmap(__data_ref bd) {
        Data(bd);
    }
    Bitmap(__this_ref_cst) = default;

    _TYP VOID Data(__data_ref bitmapData) {
        _bitmapData_r = &bitmapData;

        Drawable(TRUE);
        Resize(TRUE);
    }
    __data_ref Data() { return *_bitmapData_r; }
    __data_ref_cst Data()const { return *_bitmapData_r; }
    __data::__color_ref Data(__size x, __size y) { return (*_bitmapData_r)(x, y); }
    __data::__color_ref_cst Data(__size x, __size y)const { return (*_bitmapData_r)(x, y); }

    __data::__color Pixels(__size x, __size y)const final override { return (*_bitmapData_r)(x, y); }

    using __base::Resize;
    _TYP VOID Resize()override final{
        __base::Resize();
        _bounds.width = _bitmapData_r->width;
        _bounds.height = _bitmapData_r->height;
    }
private:

private:
    __data_ptr _bitmapData_r = nullptr;
};



NGS_END

#endif // !__HEAD_Bitmap_Module
