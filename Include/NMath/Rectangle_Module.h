//==========================================================================================================
// @file	:	Rectangle_Module
// @author	:	NAGISA
// @data	:	2023/1/27 20:27:48
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Rectangle_Module
#define __HEAD_Rectangle_Module

#include "NGS/NGS.h"
#include "NMath/Math_Module.h"
#include "NMath/Vector.h"

NGS_BEGIN

template<_CPT Arithmetic Number>
class Rectangle {
public:

    NGS_TYPE_DEFINE(Rectangle<Number>, this);
    NGS_TYPE_DEFINE(Vector2D<Number>, vector);
    NGS_TYPE_DEFINE(Number, num);

public:
    NGS_CONSTEXPR
    Rectangle(__num x = 0, __num y = 0, __num width = 0, __num height = 0) :x(x), y(y), width(width), height(height) {}
    NGS_CONSTEXPR
    Rectangle(__vector_ref_cst leftTop, __vector_ref_cst rightBottom) :x(leftTop.x), y(leftTop.y), width(rightBottom.x - leftTop.x), height(rightBottom.y - leftTop.y) {}

    NGS_CONSTEXPR
    Rectangle(__this_ref_cst other) = default;

    __this_ref operator=(__this_ref_cst) = default;

    __this_ref operator|=(__this_ref_cst rect) {
        __num right = Right(), bottom = Bottom();
        x = Min(Left(), rect.Left());
        width = Max(right, rect.Right()) - Left();
        y = Min(Top(), rect.Top());
        height = Max(bottom, rect.Bottom()) - Top();
        return *this;
    }
    __this_ref operator&=(__this_ref_cst rect) {
        if (!Intersect(rect)) {
            SetZero();
            return *this;
        }
        __num right = Right(), bottom = Bottom();
        x = Max(Left(), rect.Left());
        width = Min(right, rect.Right()) - Left();
        y = Max(Top(), rect.Top());
        height = Min(bottom, rect.Bottom()) - Top();
        return *this;
    }

    __this operator|(__this_ref_cst rect)const { __this copy = *this; return (copy |= rect); }
    __this operator&(__this_ref_cst rect)const { __this copy = *this; return (copy &= rect); }

    auto operator<=>(__this_ref_cst other)const {return Area() - other.Area();}

    NGS_CONSTEXPR operator _TYP BOOL() const { return !Empty(); }
    NGS_CONSTEXPR _TYP BOOL Empty() const { return !width || !height; }

    NGS_INL_CSTEXPR __num Top() const { return y; }
    NGS_INL_CSTEXPR __num Bottom() const { return y + height; }
    NGS_INL_CSTEXPR __num Right() const { return x + width; }
    NGS_INL_CSTEXPR __num Left() const { return x; }

    __vector LeftTop()const { return { Left(),Top() }; }
    __vector LeftBottom()const { return { Left(),Bottom() }; }
    __vector RightTop()const { return { Right(),Top() }; }
    __vector RightBottom()const { return { Right(),Bottom() }; }

    __num CenterX()const { return x + width / 2; }
    __num CenterY()const { return y + height / 2; }
    __vector Center()const { return { CenterX(),CenterY() }; }

    _TYP BOOL Intersect(__this_ref_cst other)const{ return IsCross(Left(), Right(), other.Left(), other.Right()) && IsCross(Top(), Bottom(), other.Top(), other.Bottom()); }
    _TYP BOOL Contain(__num x, __num y)const { return In(x, Left(), Right()) && In(y, Top(), Bottom()); }
    _TYP BOOL Contain(__vector_ref_cst pos)const { return Contain(pos.x,pos.y); }
    _TYP BOOL Contain(__this_ref_cst other)const { return Contain(other.Left(), other.Top()) && Contain(other.Right(), other.Bottom()); }

    _TYP VOID Set(__num x_, __num y_, __num width_, __num height_) {
        x = x_;
        y = y_;
        width = width_;
        height = height_;
    }
    _TYP VOID Set(__this_ref_cst other) {
        x = other.x;
        y = other.y;
        width = other.width;
        height = other.height;
    }
    _TYP VOID SetZero() { x = y = width = height = 0.0f; }
    _TYP VOID Normalize() {
        if (width < 0) {
            x += width;
            width = -width;
        }
        if (height < 0) {
            y += height;
            height = -height;
        }
    }
    NGS_CONSTEXPR __num Area()const { return width * height; }
public:
    __num x, y;
    __num width, height;
};

NGS_END

#endif // !__HEAD_Rectangle_Module
