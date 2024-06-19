//==========================================================================================================
// @file	:	Snake_Stage_Module
// @author	:	NAGISA
// @data	:	2023/1/17 17:32:38
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Stage
#define __HEAD_Snake_Stage

#include "NGS/NGS.h"
#include "Snake/Snake_DisplayObject.h"
#include "Snake/Snake_Vector.h"

USE_NGS_TYPE

template<UINT16 MAX_CHILD_NUM>
class Stage{
private:
    using _this = Stage;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this*;
    using _this_ref = _this&;
    using _this_ref_cst = const _this&;

    template<class Derived> using _child        = DisplayObject<Derived>;
    template<class Derived> using _child_ptr    = _child<Derived>*;
    template<class Derived> using _child_ptr_cst= const _child<Derived>*;
    template<class Derived> using _child_ref    = _child<Derived>&;
    template<class Derived> using _child_ref_cst= const _child<Derived>&;

    using _size = UINT16;
public:
    Stage():
        _children()
    {

    }
    ~Stage() {

    }

    /*VOID AccessChildren(
        const std::function<BOOL(NGF_DisplayObject&)> callBack,
        const std::function<BOOL(const NGF_DisplayObject&)> isContinue = [](const NGF_DisplayObject&)->BOOL {return FALSE; }
    )const;*/

    template<class Derived>
    _child_ptr<Derived> AddChild(_child_ref<Derived> child) {
        _children.Push(&child);
        return &child;
    }
    template<class Derived>
    _child_ptr<Derived> AddChildAt(_child_ref<Derived> child, _size index) {
        _children.Insert(&child, index);
        return &child;
    }
    template<class Derived>
    _child_ptr<Derived> GetChildAt(_size index) {
        return reinterpret_cast<_child_ptr<Derived>>(_children[index]);
    }
    template<class Derived>
    _size GetChildIndex(_child_ref_cst<Derived> child) const {
        PVOID p = const_cast<_child_ptr<Derived>>(&child);
        return _children.IndexOf(p);
    }
    template<class Derived>
    _child_ptr<Derived> RemoveChildAt(_size index) {
        return _children.Erase(index);
    }
    template<class Derived>
    _child_ptr<Derived> RemoveChild(_child_ref_cst<Derived> child) {
        auto i = GetChildIndex(child);
        return reinterpret_cast<_child_ptr<Derived>>(_children.Erase(i));
    }

    NGS_INL_CSTEXPR _size GetNumChildren()const { return _children.GetLength(); }

protected:
    VOID _CalculateCurBounds();
private:

private:
    Vector<PVOID, MAX_CHILD_NUM> _children;
private:

};

#endif // !__HEAD_Snake_Stage
