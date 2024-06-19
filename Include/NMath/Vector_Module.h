//==========================================================================================================
// @file	:	Vector_Module
// @author	:	NAGISA
// @data	:	2023/1/26 22:08:02
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Vector_Module
#define __HEAD_Vector_Module

#include "NGS/NGS.h"
#include "NMath/Rotation.h"

NGS_BEGIN

template<
    _TYP SIZE_T16 N,
    _CPT Arithmetic Number,
    template<typename num>class Derived
>class _Vector {
private:
    using ___this = _Vector<N, Number, Derived>;
public:
    NGS_INL_CSTEXPR static auto DIMENSIONAL = N;

    template<_CPT Arithmetic C> using __similar = _Vector<N, C, Derived>;
    template<_CPT Arithmetic C> using __similar_ref = __similar<C>&;
    template<_CPT Arithmetic C> using __similar_ref_cst = const __similar<C>&;
    template<_CPT Arithmetic C> using __similar_ptr = __similar<C>*;
    template<_CPT Arithmetic C> using __similar_ptr_cst = const __similar<C>*;

    template<_CPT Arithmetic C> using __similar_d = Derived<C>;
    template<_CPT Arithmetic C> using __similar_d_ref = __similar<C>&;
    template<_CPT Arithmetic C> using __similar_d_ref_cst = const __similar<C>&;
    template<_CPT Arithmetic C> using __similar_d_ptr = __similar<C>*;
    template<_CPT Arithmetic C> using __similar_d_ptr_cst = const __similar<C>*;

    NGS_TYPE_DEFINE(___this, this);
    NGS_TYPE_DEFINE(Derived<Number>, derived);
    NGS_TYPE_DEFINE(Number, num);
    NGS_TYPE_DEFINE(_TYP SIZE_T16, size);

public:
    //=======================================
    //	���캯��
    //=======================================
    constexpr _Vector() = default;
    constexpr _Vector(__num x):
        x(x)
    {}
    template<_CPT Arithmetic C>
    constexpr _Vector(__similar_ref_cst<C> other) { _Construct(other); }

    //=======================================
    //	���������
    //=======================================
    constexpr __num_ref    operator[](__size index) { return (&x)[index]; }
    constexpr  __num_ref_cst operator[](__size index)const { return (&x)[index]; }

    template<_CPT Arithmetic C>
    explicit(false) operator __similar_d<C>()const { return __similar_d<C>{*this}; }
    operator __derived_ref_cst()const { return static_cast<__derived_ref_cst>(*this); }
    operator __derived_ref() { return static_cast<__derived_ref>(*this); }

    auto         operator-()const{return (*this) * -1;}

    auto         operator<=>(__this_ref_cst)const = default;

    __this_ref operator=(__this_ref_cst other) { 
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] = other[i];
        return *this;
    }
    //====================================
    // �Ӽ���
    //====================================
    __derived_ref operator+=(__this_ref_cst other) { 
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] += other[i];
        return *this;
    }
    __derived operator+(__this_ref_cst other)const {
        __derived clone(*this);
        clone += other;
        return clone;
    }
    __derived_ref operator-=(__this_ref_cst other) {
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] -= other[i];
        return *this;
    }
    __derived operator-(__this_ref_cst other)const {
        __derived clone(*this);
        clone -= other;
        return clone;
    }

    //====================================
    // �˳���
    // ���壺
    // 1���˷�Ϊ�����ĸ���ά��ֱ����ˣ������������
    // 2������Ϊ�����ĸ���ά��ֱ������������������
    //====================================
    __derived_ref   operator*=(__this_ref_cst other) {
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] *= other[i];
        return *this;
    }
    __derived    operator*(__this_ref_cst other)const { return __derived{ *this } *= other; }
    __derived_ref   operator/=(__this_ref_cst other) {
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] /= other[i];
        return *this;
    }
    __derived    operator/(__this_ref_cst other)const { return __derived{ *this } /= other; }

    __derived_ref   operator*=(__num value) { 
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] *= value;
        return *this;
    }
    __derived    operator*(__num value)const { return __derived{ *this } *= value; }
    friend __derived operator*(__num value,__this_ref_cst self) {return self * value;}
    __derived_ref   operator/=(__num value) {
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] /= value;
        return *this;
    }
    __derived    operator/(__num value)const { return __derived{ *this } /= value; }
    //====================================
    // ������
    // ������
    // ��ϻ�
    //====================================
    friend constexpr __num Dot(__this_ref_cst a, __this_ref_cst b) {
        __num sum = 0;
        for (__size i = 0; i < __this::DIMENSIONAL; i++)
            sum += (a[i] * b[i]);
        return sum;
    }
    /*constexpr static __num Cross(__this_ref_cst a, __this_ref_cst b) {
        return ::sqrt(a.LengthSquard() * b.LengthSquard()) * ::sin()
        return __derived(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
    constexpr static __num Mixed(__this_ref_cst a, __this_ref_cst b, __this_ref_cst c) {

    }*/


    //=======================================
    //	�����ӿ�
    //=======================================
    NGS_CONSTEXPR _TYP VOID
    Fill(__num value) {
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] = value;
    }

    NGS_CONSTEXPR _TYP VOID SetZero() { Fill(0); }

    template<typename ...Args>
        requires (sizeof...(Args) > 0) && (sizeof...(Args) <= N)
    NGS_CONSTEXPR _TYP VOID Set(Args ...args) {_Set(args...);}

    NGS_CONSTEXPR  auto LengthSquard()const {
        __num ls;
        for(__size i = 0;i < DIMENSIONAL;i++)
            ls += (&x)[i] * (&x)[i];
        return ls;
    }
    constexpr auto Length()const { return ::sqrt(LengthSquard()); }
protected:
    //=======================================
    //	ʵ��
    //=======================================
    template<typename ...Args>
        requires (sizeof...(Args) <= DIMENSIONAL)
    NGS_CONSTEXPR _TYP VOID _Construct(Args ...args) { 
        __size i = 0;
        (((&x)[i] = args, i++), ...);
    }
    
    template<_CPT Arithmetic C>
    NGS_CONSTEXPR _TYP VOID _Construct(__similar_ref_cst<C> other) {
        for (__size i = 0; i < DIMENSIONAL; i++)
            (&x)[i] = static_cast<__num>(other[i]);
    }

    template<__size index = 0,typename... Args>
        requires (index < N) && (sizeof...(Args) <  N)
    NGS_CONSTEXPR _TYP VOID _Set(__num Value,Args... args) {
        (&x)[index] = Value;
        if NGS_CONSTEXPR(index < N - 1 && (sizeof...(args) > 0))_Set<index + 1>(args...);
    }

public:
    __num x;
};

NGS_EXPORT
template<_CPT Arithmetic Number = _TYP FLOAT32>
class Vector2D : public _Vector<2, Number, Vector2D> {
private:
    using __base = _Vector<2, Number, Vector2D>;
public:
    NGS_TYPE_DEFINE(Vector2D<Number>, this);
    NGS_TYPE_DEFINE(Number, num);

public:
    using __base::_Vector;
    constexpr Vector2D(__num x, __num y) :
        __base(x),
        y(y)
    {}

    friend constexpr __num Cross(__this_ref_cst a, __this_ref_cst b) { return a.x * b.y - a.y * b.x; }
    friend constexpr __this Cross(__this_ref_cst a, __num s) { return __this(s * a.y, -s * a.x); }
    friend constexpr __this Cross( __num s, __this_ref_cst a) { return __this(-s * a.y, s * a.x); }
    friend constexpr __this_ref CrossEq(__this_ref a, __num s) { a.Set(s * a.y, -s * a.x); return a; }
    friend constexpr __this_ref CrossEq(__num s , __this_ref a) { a.Set(-s * a.y, s * a.x); return a; }

    constexpr __num operator^(__this_ref_cst other)const { return Cross(*this, other); }
    constexpr __this operator^(__num s)const { return Cross(*this, s); }
    friend constexpr __this operator^(__num s,__this_ref_cst a) { return Cross(s , *this); }
    constexpr __this_ref operator^=(__num s) { return CrossEq(*this, s); }
public:
    __num y;
};


NGS_EXPORT
template<_CPT Arithmetic Number = _TYP FLOAT32>
class Vector3D : public _Vector<3, Number, Vector3D> {
private:
    using __base = _Vector<3, Number, Vector3D>;
public:
    NGS_TYPE_DEFINE(Vector3D<Number>, this);
    NGS_TYPE_DEFINE(Number, num);

public:
    using __base::_Vector;
    constexpr Vector3D(__num x, __num y, __num z) 
        :__base(x)
        ,y(y)
        ,z(z)
    {}

    friend constexpr __this Cross(__this_ref_cst a, __this_ref_cst b) {
        return __this(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
    }
    friend constexpr __this_ref CrossEq(__this_ref a, __this_ref_cst b) { return a = Cross(a, b); }

    constexpr __this operator^(__this_ref_cst other)const { return Cross(*this, other); }
    constexpr __this_ref operator^=(__this_ref_cst other) { return CrossEq(*this, other); }
public:
    __num y;
    __num z;
};


NGS_END

#endif // !__HEAD_Vector_Module
