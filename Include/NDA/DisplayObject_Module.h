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
// ��ʾ�ܹ��ɲο�AS3����ʾ�ܹ�
// ������ΪDisplayObject DisplayObjectContainer
// һ��Ϊ��ʾ����һ��Ϊ��ʾ������������ӦΪ������
// ��ʾ�����������������κ���ʾͼ����Ϣ�������AS3��ͬ����ֻ��������ʾ�����������ʾ����������
// 
// ע�⣺
// ����Ҫ�ı���ʾ����� ��ʾ���ԣ�����X��Y��Scale�ȵȣ� ʱ����Ҫ�ȵ�����ʾ�����Redraw����
// ����ı�����ʾ����Ĵ�С����ʾ������Ը������еĴ�С��������Ҫ����Resize����
// 
// Resize�������������߼���
// ������ĳ����ʾ�����Resize����ΪTRUE���������ʾ��������и���ʾ���󶼻ᱻ����ΪTRUE
// ����Ҫ�û�����Resize����ΪFALSE����Ϊ��Ӧ���ڵ���Resize()����������ΪFALSE
// ����Resize()���������ֻ�������Resize��������ΪFALSE��������Ӱ�츸��ʾ����������Resize���ԣ���Ҫע����ǣ������ʾ����Ϊ�����Ļ������ݹ������������ʾ�����Resize()����
// �������Resize�������������Resize�����Լ���������ʾ�����Resize���Զ��ᱻ����ΪFALSE
// 
// Redraw�������������߼���
// Redraw������������Resize()���������������㣬����Resize��Redraw��������ȫȫ��һ�����ԣ���Ϊ��ʾ����Ӧ����ƹ�������һ����ʾ����ֻ��Ҫ�ṩ������������ݼ���
// ����Redraw����ΪTRUEʱ������ʾ����Ϊ�������������Լ����е�����ʾ�����Redraw���Զ��ᱻ����ΪTRUE
// ����Redraw����ΪFALSEʱ��ֻ������ᱻ����ΪFALSE����ͬResize���ԣ��û��ڻ�������ĵط�������Ҫ����Redraw����ΪFALSE
// ����Redraw()�������������Ƿ�����ʾ����������ֻ���������Redraw����ΪFALSE�����ڻ��ƽ��������Redraw����
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
        IS_CONTAINER = bit(2),//�˱�־���������ڱ���RTTI��������һ������϶�
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
        Assert(!_parent_r,"û�н�����ʾ�������ʾ������ɾ����");
    };

    /**
    * @brief �Ƿ���Ҫ�ػ棬Ϊ��������һ֡����������
    */
    _TYP BOOL NeedRedraw()const { return Bits(_flag, NEED_REDRAW); }
    /**
    * @brief ������ʾ�����Ƿ���Ҫ�ػ�
    * 
    * @param v TRUEΪ��Ҫ�ػ棬FALSEΪ����Ҫ�ػ棨һ������²���Ҫ�û�����ΪFALSE����ÿ��Redraw������Զ�����ΪFALSE��
    */
    virtual _TYP VOID Redraw(_TYP BOOL v) { Bits(_flag, NEED_REDRAW, v); }
    /**
    * @brief �ػ����ʾ����
    * 
    * @note ���ô˺��������Զ�����RedrawΪFALSE
    */
    _TYP VOID Redraw() { Redraw(FALSE); }

    /**@brief �Ƿ��ǿɻ��Ƶ���ʾ����*/
    _TYP BOOL Drawable()const { return Bits(_flag, DRAWABLE); }
    _TYP VOID Drawable(_TYP BOOL v) { Bits(_flag, DRAWABLE, v); }

    /**@brief �Ƿ���Ҫ���¼������ʾ����Ĵ�С*/
    _TYP BOOL NeedResize()const { return Bits(_flag, NEED_RESIZE); }
    /**
    * @brief �����Ƿ���Ҫ���¼�����ʾ����߽�
    * 
    * @param v TRUE Ϊ��Ҫ��FALSEΪ����Ҫ��һ������²���Ҫ�û�����ΪFALSE����ÿ��Resize������Զ�����ΪFALSE��
    * 
    * @note ��v ΪTRUEʱ���Ὣ�Լ��͸���������ʾ��������ΪTRUE����ΪFALSEʱ��ֻ�������Լ�ΪFALSE
    */
    _TYP VOID Resize(_TYP BOOL v);
    /**
    * @brief ���¼�����ʾ����߽�
    * 
    * @note ���ô˺��������Զ�����ResizeΪFALSE
    */
    virtual _TYP VOID Resize() = 0 { Resize(FALSE); };

    /**@brief ����ʾ�����Ƿ���������ֻ�иñ�־ΪTRUEʱ�Ż᳢�Ա����Ӷ���*/
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
    __rect _refreshArea;//ȫ��

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

    using __base::Resize;//ʹ����Resize�ɼ�
    /**
    * @brief ���¼������ʾ����ı߽�
    * 
    * @note ��ʾ������������߽�ʱ��������������ʾ����ı߽磬������ʾ����ҲΪ��������ݹ�������������ʾ����ı߽磬�˺����ᵼ����������ʾ����ı߽綼���¼��㣬Ҳ����Resize���Զ�ΪFALSE
    */
    _TYP VOID Resize()override final;
    //using __base::Redraw;
    /**
    * @brief �����Լ��Լ���������ʾ�����Redraw����
    * 
    * @param v ΪTRUEʱ�������Լ��Լ���������ʾ�����Redraw����ΪTRUE��ΪFALSEʱ��ֻ�����Լ���Redraw����ΪFALSE
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
