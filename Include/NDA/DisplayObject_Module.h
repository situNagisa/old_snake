//==========================================================================================================
// @file	:	DisplayObject_Module
// @author	:	NAGISA
// @data	:	2023/1/26 21:16:24
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_DisplayObject_Module
#define __HEAD_DisplayObject_Module

#include "NGS/NGS.h"
#include "NDA/NDA_Defined.h"
#include "NMath/Math.h"

NGS_BEGIN



//================================================
// 显示架构可参考AS3的显示架构
// 核心类为DisplayObject DisplayObjectContainer
// 一个为显示对象，一个为显示对象容器，都应为抽象类
// 显示对象容器本身不包含任何显示图像信息（这点与AS3不同），只包含子显示对象或者子显示对象容器、
// 
// 注意：
// 当需要改变显示对象的 显示属性（例如X，Y，Scale等等） 时，需要先调用显示对象的Redraw函数
// 如果改变了显示对象的大小（显示对象相对父容器中的大小），则需要调用Resize函数
// 
// Resize函数具有以下逻辑：
// 若设置某子显示对象的Resize属性为TRUE，则该子显示对象的所有父显示对象都会被设置为TRUE
// 不需要用户设置Resize属性为FALSE，因为他应该在调用Resize()函数后被设置为FALSE
// 调用Resize()函数后仅仅只将自身的Resize属性设置为FALSE，并不会影响父显示对象容器的Resize属性，但要注意的是，如果显示对象为容器的话，则会递归调用所有子显示对象的Resize()函数
// 结果就是Resize函数过后自身的Resize属性以及所有子显示对象的Resize属性都会被设置为FALSE
// 
// Redraw函数具有以下逻辑：
// Redraw函数本身并不像Resize()函数那样包含计算，比起Resize，Redraw则算完完全全的一个属性，因为显示对象不应与绘制工作绑定在一起，显示对象只需要提供绘制所需的数据即可
// 设置Redraw属性为TRUE时，若显示对象为容器，则自身以及所有的子显示对象的Redraw属性都会被设置为TRUE
// 设置Redraw属性为FALSE时，只有自身会被设置为FALSE，如同Resize属性，用户在绘制以外的地方并不需要设置Redraw属性为FALSE
// 调用Redraw()函数不论自身是否是显示对象容器都只设置自身的Redraw属性为FALSE，请在绘制结束后调用Redraw函数
// 
// 
//================================================

NGS_CONCEPT

template<class T,class C = NDA_TYPE_COLOR_T,class N = NDA_TYPE_NUM>
concept Drawable = requires(T target, C x, C y) {
    requires Arithmetic<C>;
    //requires Arithmetic<N>;
    {target.Pixels(x, y)} -> std::convertible_to<C>;
    {target.Width()} -> std::convertible_to<C>;
    {target.Height()} -> std::convertible_to<C>;
    //{target.Bounds()} -> std::convertible_to<Rectangle<N>>;
};

NGS_END
class Stage;
class DisplayObjectContainer;

class DisplayObject :public Object{
public:

    NGS_TYPE_DEFINE(NDA_TYPE_NUM, num);
    NGS_TYPE_DEFINE(NDA_TYPE_SIZE, size);

    NGS_TYPE_DEFINE(DisplayObject, this);
    NGS_TYPE_DEFINE(DisplayObjectContainer, container);
    NGS_TYPE_DEFINE(_NGS Rectangle<__num>, rect);
    NGS_TYPE_DEFINE(_NGS Matrix<__num>, matrix);
    NGS_TYPE_DEFINE(_NGS Vector2D<__num>, vector);

    NGS_INL_CSTEXPR static const _TYP FLAG
        VISIBLE = bit(0),
        LOCK = bit(1),
        IS_CONTAINER = bit(2),//此标志的意义在于避免RTTI，增加了一定的耦合度
        DRAWABLE = bit(3),
        NEED_REDRAW = bit(4),
        NEED_RESIZE = bit(5);
public:
    DisplayObject():
        _flag(VISIBLE | LOCK | NEED_REDRAW | NEED_RESIZE),
        _position( 0,0 ),
        _bounds( 0,0,0,0 ),
        _refreshArea(0,0,0,0),
        _matrix(1,0,0,1,0,0 ),
        _parent_r(nullptr),
        _stage_r(nullptr)
    {}
    DisplayObject(__this_ref_cst other) = default;
    virtual ~DisplayObject() {
        Assert(!_parent_r,"没有将此显示对象从显示容器中删除！");
    };

    /**
    * @brief 是否需要重绘，为否则在下一帧会跳过绘制
    */
    _TYP BOOL NeedRedraw()const { return Bits(_flag, NEED_REDRAW); }
    /**
    * @brief 设置显示对象是否需要重绘
    * 
    * @param v TRUE为需要重绘，FALSE为不需要重绘（一般情况下不需要用户设置为FALSE，在每次Redraw过后会自动设置为FALSE）
    */
    virtual _TYP VOID Redraw(_TYP BOOL v) { Bits(_flag, NEED_REDRAW, v); }
    /**
    * @brief 重绘该显示对象
    * 
    * @note 调用此函数过后自动设置Redraw为FALSE
    */
    _TYP VOID Redraw() { Redraw(FALSE); }

    /**@brief 是否是可绘制的显示对象*/
    _TYP BOOL Drawable()const { return Bits(_flag, DRAWABLE); }
    _TYP VOID Drawable(_TYP BOOL v) { Bits(_flag, DRAWABLE, v); }

    /**@brief 是否需要重新计算该显示对象的大小*/
    _TYP BOOL NeedResize()const { return Bits(_flag, NEED_RESIZE); }
    /**
    * @brief 设置是否需要重新计算显示对象边界
    * 
    * @param v TRUE 为需要，FALSE为不需要（一般情况下不需要用户设置为FALSE，在每次Resize过后会自动设置为FALSE）
    * 
    * @note 当v 为TRUE时，会将自己和父级所有显示对象设置为TRUE，而为FALSE时，只是设置自己为FALSE
    */
    _TYP VOID Resize(_TYP BOOL v);
    /**
    * @brief 重新计算显示对象边界
    * 
    * @note 调用此函数过后自动设置Resize为FALSE
    */
    virtual _TYP VOID Resize() = 0 { Resize(FALSE); };

    /**@brief 该显示对象是否是容器（只有该标志为TRUE时才会尝试遍历子对象）*/
    _TYP BOOL IsContainer()const { return Bits(_flag, IS_CONTAINER); }

    _TYP BOOL Visible()const { return Bits(_flag, VISIBLE); }
    _TYP VOID Visible(_TYP BOOL b) { Bits(_flag, VISIBLE,b); }

    __num Width()const { Assert(!NeedResize()); return _bounds.width; }
    _TYP VOID Width(__num w) { _bounds.width = w; }
    __num Height()const { Assert(!NeedResize()); return _bounds.height; }
    _TYP VOID Height(__num h) { _bounds.height = h; }

    __num ScaleX()const { return _matrix.ScaleX(); }
    _TYP VOID ScaleX(__num);
    __num ScaleY()const { return _matrix.ScaleY(); }
    _TYP VOID ScaleY(__num);
    
    virtual NDA_TYPE_COLOR_T Pixels(__size x, __size y)const = 0;

    __matrix_ref Matrix() { return _matrix; }
    __matrix_ref_cst Matrix()const { return _matrix; }
    __matrix GlobalMatrix()const;

    __num_ref X() { return _position.x; }
    __num_ref_cst X()const { return _position.x; }
    __num_ref Y() { return _position.y; }
    __num_ref_cst Y()const { return _position.y; }

    __vector_ref Position() { return _position; }
    __vector_ref_cst Position()const { return _position; }

    __container_ptr Parent()const { return _parent_r; }
    __rect_ref_cst Bounds()const { return _bounds; }
    __rect_ref_cst RefreshArea()const { return _refreshArea; }
    _TYP VOID RefreshArea(__rect_ref_cst area) { _refreshArea = area; }

    _TYP VOID StartChangeDisplay() {
        
    }
    _TYP VOID EndChangeDisplay() {
    }
    _TYP BOOL IsLocked()const { return Bits(_flag, LOCK); }
    _TYP VOID Lock() { Bits<TRUE>(_flag, LOCK); }
    _TYP VOID Unlock() { Bits<FALSE>(_flag, LOCK); }
protected:
    

    virtual _TYP VOID _SetStage(Stage* pStage) { _stage_r = pStage; }
private:

public:
    
    
protected:
    _TYP FLAG _flag;

    __vector _position;

    __rect _bounds;
    __rect _refreshArea;//全局

    __matrix _matrix;

    __container_ptr _parent_r;
    Stage* _stage_r;

    friend class __container;
}; 

class DisplayObjectContainer :public DisplayObject {
public:
    NGS_TYPE_DEFINE(DisplayObject, base);
    NGS_TYPE_DEFINE(DisplayObjectContainer, this);

    NGS_TYPE_DEFINE(NDA_TYPE_POS, pos);
    NGS_TYPE_DEFINE(int, sign);

public:
    DisplayObjectContainer() :
        _numChildren(0),
        _children({})
    {
        Bits<TRUE>(_flag,IS_CONTAINER);
        Bits<FALSE>(_flag,DRAWABLE);
    }
    DisplayObjectContainer(__this_ref_cst) = default;

    _TYP VOID AccessChildren(
        const std::function<_TYP BOOL(__base_ref)> callBack,
        const std::function<_TYP BOOL(__base_ref_cst)> isContinue = [](__base_ref_cst)->_TYP BOOL {return FALSE; }
    )const;

    __base_ptr& operator[](__size index) { return _children[index]; }
    const __base_ptr& operator[](__size index)const { return _children[index]; }

    __base_ptr AddChild(__base_ref child) {
        Assert(!child.Parent());
        _children.push_back(&child);
        _AddChild(child);
        return &child;
    }
    __base_ptr AddChildAt(__base_ref child, __size index) {
        if (index >= _numChildren) {
            AddChild(child);
            return &child;
        }
        auto it = _children.begin();
        it += index;
        _children.insert(it, 1, &child);
        _AddChild(child);
        return &child;
    }
    __base_ptr GetChildAt(__size index) const{ return _children.at(index); }
    __sign GetChildIndex(__base_ref child) const {
        for (__size i = 0; i < _numChildren; i++)
            if (_children[i] == &child)return i;
        return -1;
    }
    __base_ptr RemoveChildAt(__size index) {
        auto& child = *_children.at(index);
        Assert(child.Parent() == this);
        _children.erase(_children.begin() + index);
        _RemoveChild(child);
        return &child;
    }
    __base_ptr RemoveChild(__base_ref child) {
        __sign index = GetChildIndex(child);
        if (index == -1)return nullptr;
        return RemoveChildAt(index);
    }
    _TYP VOID RemoveChildren() {
        for (auto it : _children) {
            _RemoveChild(*it);
        }
        _children.clear();
    }

    NDA_TYPE_COLOR_T Pixels(__size, __size)const final override { return 0; }

    __size GetNumChildren(_TYP BOOL includeChildsChildren = FALSE)const {
        if (!includeChildsChildren)return _numChildren;
        __size num = _numChildren;
        for (auto& it : _children) {
            if (!it->IsContainer())continue;
            __this_ptr container = static_cast<__this_ptr>(it);
            if (!container)continue;
            num += container->GetNumChildren(TRUE);
        }
        return num;
    }

    _TYP BOOL Contain(__base_ref_cst display)const {
        __base_ptr_cst p = &display;
        do{
            if (p == this)return TRUE;
            p = p->Parent();
        } while (p);
        return FALSE;
    }

    using __base::Resize;//使父类Resize可见
    /**
    * @brief 重新计算该显示对象的边界
    * 
    * @note 显示对象容器计算边界时会连带计算子显示对象的边界，若子显示对象也为容器，则递归设置所有子显示对象的边界，此函数会导致所有子显示对象的边界都重新计算，也就是Resize属性都为FALSE
    */
    _TYP VOID Resize()override final;
    //using __base::Redraw;
    /**
    * @brief 设置自己以及所有子显示对象的Redraw属性
    * 
    * @param v 为TRUE时，设置自己以及所有子显示对象的Redraw属性为TRUE，为FALSE时，只设置自己的Redraw属性为FALSE
    */
    _TYP VOID Redraw(_TYP BOOL v)override final;

protected:
    _TYP VOID _SetStage(Stage* pStage) override
    {
        __base::_SetStage(pStage);
        if (!_numChildren)return;
        for (auto& it : _children)
            it->_SetStage(_stage_r);
    }
private:
    _TYP VOID _AddChild(__base_ref child) {
        child._parent_r = this;
        child._SetStage(_stage_r);
        _numChildren++;
    }
    _TYP VOID _RemoveChild(__base_ref child) {
        child._parent_r = nullptr;
        child._SetStage(nullptr);
        _numChildren--;
    }

private:
    __size _numChildren;
    std::vector<__base_ptr> _children;
};





NGS_END

#endif // !__HEAD_DisplayObject_Module
