//==========================================================================================================
// @file	:	Snkae_DisplayObject
// @author	:	NAGISA
// @data	:	2023/1/17 18:15:12
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snkae_DisplayObject
#define __HEAD_Snkae_DisplayObject

#include "NGS/NGS.h"
#include "Snake/Snake_DeviceContext.h"
#include "Snake/Snake_Rectangle.h"

USE_NGS_TYPE

//使用类模板避免虚函数的开销
template<class Derived>
class DisplayObject{
public:
    using DerivedClass = Derived;
private:
    using _this = DisplayObject<Derived>;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this*;
    using _this_ref = _this&;
    using _this_ref_cst = const _this&;

    using _child = Derived;
    using _child_ptr = Derived*;
    using _child_ptr_cst = const Derived*;
    using _child_ref = Derived&;
    using _child_ref_cst = const Derived&;
protected:
    using _dc = DC;
    using _dc_ptr = _dc*;
    using _dc_ptr_cst = const _dc*;
    using _dc_ref = _dc&;
    using _dc_ref_cst = const _dc&;

    using _pos = INT16;
    using _size = UINT16;
public:
    DisplayObject():
        x(0),
        y(0),
        width(0),
        height(0)
    {

    }

    VOID Draw(_dc_ref dc) {
        (static_cast<_child_ptr>(this))->Draw(dc);
        requiredDraw = FALSE;
        _Bounds.Set(x, y, width, height);
    }
    
    NGS_INLINE VOID RecordCurBounds() {
        _Bounds |= {x, y, width, height};
        requiredDraw = TRUE;
    }
    
    NGS_INLINE const Rectangle& GetPostBounds()const {return _Bounds;}
    NGS_INLINE Rectangle GetCurBounds()const { return { x,y,width,height }; }
    NGS_INLINE VOID BoundsMove(INT32 dx, INT32 dy) {
        _Bounds.x += dx;
        _Bounds.y += dy;
    }
public:
    _pos x;
    _pos y;
    _size width;
    _size height;
    BOOL requiredDraw = TRUE;
protected:
    Rectangle _Bounds;
};

#endif // !__HEAD_Snkae_DisplayObject
