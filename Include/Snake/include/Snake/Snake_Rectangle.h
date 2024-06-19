//==========================================================================================================
// @file	:	Snake_Rectangle
// @author	:	NAGISA
// @data	:	2023/1/18 20:20:37
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Rectangle
#define __HEAD_Snake_Rectangle

#include "NGS/NGS.h"
#include "Snake/Snake_Math.h"

USE_NGS_TYPE

struct Rectangle {
private:
    using _this = Rectangle;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this*;
    using _this_ref = _this&;
    using _this_ref_cst = const _this&;

    using _pos = INT16;
    using _size = UINT16;
public:
    NGS_INL_CSTEXPR
    Rectangle(
        _pos x = 0, _pos y = 0, 
        _size width = 0, _size height = 0
    ) :
        x(x), 
        y(y), 
        width(width), 
        height(height) 
    {}

    _this_ref operator|=(_this_ref_cst rect) {
        _this c_this = *this;
        x = Min(c_this.x, rect.x);
        width = Max(c_this.x + c_this.width, rect.x + rect.width) - x;
        y = Min(c_this.y, rect.y);
        height = Max(c_this.y + c_this.height, rect.y + rect.height) - y;
        return *this;
    }
    _this_ref operator&=(_this_ref_cst rect) {
        _this c_this = *this;

        if (!IsCross(rect)) {
            SetZero();
            return *this;
        }
        x = Max(c_this.x, rect.x);
        width = Min(c_this.x + c_this.width,rect.x + rect.width) - x;
        y = Max(c_this.y, rect.y);
        height = Min(c_this.y + c_this.height, rect.y + rect.height) - y;
        return *this;
    }

    NGS_INLINE _this operator|(_this_ref_cst rect)const {
        _this r(*this);
        r |= rect;
        return r;
    }
    NGS_INLINE _this operator&(_this_ref_cst rect)const {
        _this r(*this);
        r &= rect;
        return r;
    }
    NGS_INLINE BOOL IsCross(_this_ref_cst rect)const {
        return ::IsCross(x, _pos(x + width), rect.x, _pos(rect.x + rect.width)) && ::IsCross(y, _pos(y + height), rect.y, _pos(rect.y + rect.height));
    }
    NGS_INLINE BOOL Contain(_pos posx, _pos posy)const {
        return ::InInterval(posx, x,_pos(x + width)) && ::InInterval(posy,y,_pos(y + height));
    }

    _this_ref operator=(_this_ref_cst other) = default;
    //auto operator<=>(_this_ref_cst other)const = default;

    NGS_INLINE
    operator BOOL() const { return width && height; }
    NGS_INLINE
    BOOL Empty() const { return !width || !height; }

    NGS_INL_CSTEXPR _pos GetTop() const { return height > 0 ? y : y + height; }
    NGS_INL_CSTEXPR _pos GetBottom() const { return height > 0 ? y + height : y; }
    NGS_INL_CSTEXPR _pos GetRight() const { return width > 0 ? x + width : x; }
    NGS_INL_CSTEXPR _pos GetLeft() const { return width > 0 ? x : x + width; }

    NGS_INLINE
    VOID Set(_pos x_, _pos y_, _size width_, _size height_) {
        x = x_;
        y = y_;
        width = width_;
        height = height_;
    }
    NGS_INLINE
    VOID SetZero() {
        x = y = 0;
        width = height = 0;
    }
    NGS_INLINE
    VOID Normalize() {
        
    }
public:
    _pos x, y;
    _size width, height;
};

#endif // !__HEAD_Snake_Rectangle
