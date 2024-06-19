//==========================================================================================================
// @file	:	NGS_TemplateMateBase_Module
// @author	:	NAGISA
// @data	:	2023/1/27 11:57:01
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_TemplateMateBase_Module
#define __HEAD_NGS_TemplateMateBase_Module

#include "NGS_Defined.h"
#include "NGS/NGS_Concepts.h"
#include "NGS/NGS_TypeTrait.h"

NGS_BEGIN

NGS_EXPORT
template<_CPT Arithmetic number1, _CPT Arithmetic number2>
using CompleteArithmetic = _TYT Conditional<
    (sizeof(number1) >= sizeof(number2)),
    _TYT Conditional<
        (sizeof(number1) != sizeof(number2)),
        number1,
        _TYT Conditional<
            _CPT FloatingPoint<number1>,
            number1,
            _TYT Conditional<
                _CPT UnsignedIntegral<number1>,
                number1,
                number2
            >
        >
    >
    , number2
>;

NGS_EXPORT
template<
    _TYP SIZE_T16 start,
    _TYP SIZE_T16 end,
    class Function,
    class...Args
>
    requires requires(Function f,_TYP SIZE_T16 index,Args... args) {
    f(index, args...);
}
NGS_INLINE _TYP VOID For(Function fn,Args... args){
    fn(start,args...);
    if NGS_CONSTEXPR(end - start >= 0 && start < end)
        For<start + 1, end>(fn,args...);
    else if NGS_CONSTEXPR(end - start < 0 && start >= end)
        For<start - 1, end>(fn, args...);
}
/*
NGS_EXPORT
template<
    _TYP SIZE_T16 start,
    _TYP SIZE_T16 end,
    class Lambda
>
NGS_INLINE _TYP VOID For(Lambda lambda) {
    lambda(start);
    if NGS_CONSTEXPR(end - start >= 0 && start < end)
        For<start + 1, end>(lambda);
    else if NGS_CONSTEXPR(end - start < 0 && start >= end)
        For<start - 1, end>(lambda);
}

//NGS_EXPORT
//template<
//    _TYP SIZE_T16 start,
//    _TYP SIZE_T16 end,
//    class ReturnType,
//    class Class,
//    _CPT Integral UINT
//>
//NGS_INLINE _TYP VOID For(ReturnType(Class::*fn)(UINT), Class* p) {
//    if NGS_CONSTEXPR(end - start >= 0) {
//        (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start < end)
//            For<start + 1, end>(fn, p);
//    } else {
//        (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start >= end) 
//            For<start - 1, end>(fn, p);
//    }
//}

//15���¿��ڱ����ڼ��㣬������constexpr
NGS_EXPORT
template<
    _TYP SIZE_T16 start,
    _TYP SIZE_T16 end,
    class ReturnType,
    _CPT Integral UINT
>
NGS_CONSTEXPR ReturnType For(ReturnType fn(UINT),ReturnType operate(ReturnType,ReturnType)) {
    ReturnType result = fn(start);
    if NGS_CONSTEXPR(end - start >= 0) {
        if NGS_CONSTEXPR(start < end)
            return operate(result, For<start + 1, end>(fn, operate));
        else
            return result;
    } else {
        if NGS_CONSTEXPR(start >= end)
            return operate(For<start - 1, end>(fn, operate), result);
        else
            return result;
    }
}

//15���¿��ڱ����ڼ��㣬������constexpr
NGS_EXPORT
template<
    _TYP SIZE_T16 start,
    _TYP SIZE_T16 end,
    class Lambda,
    class ReturnType
>
NGS_CONSTEXPR ReturnType For(Lambda lambda, ReturnType operate(ReturnType, ReturnType)) {
    ReturnType result = lambda(start);
    if NGS_CONSTEXPR(end - start >= 0) {
        if NGS_CONSTEXPR(start < end)
            return operate(result, For<start + 1, end>(lambda, operate));
        else
            return result;
    } else {
        if NGS_CONSTEXPR(start >= end)
            return operate(For<start - 1, end>(lambda, operate), result);
        else
            return result;
    }
}

//15���¿��ڱ����ڼ��㣬������constexpr
NGS_EXPORT
template<
    _TYP SIZE_T16 start,
    _TYP SIZE_T16 end,
    class Lambda,
    class Operate
>
NGS_CONSTEXPR auto For(Lambda lambda, Operate operate) {
    auto result = lambda(start);
    if NGS_CONSTEXPR(end - start >= 0) {
        if NGS_CONSTEXPR(start < end)
            return operate(result, For<start + 1, end>(lambda, operate));
        else
            return result;
    } else {
        if NGS_CONSTEXPR(start >= end)
            return operate(For<start - 1, end>(lambda, operate), result);
        else
            return result;
    }
}*/

//NGS_EXPORT
//template<
//    _TYP SIZE_T16 start,
//    _TYP SIZE_T16 end,
//    class ReturnType,
//    class Class,
//    _CPT Integral UINT
//>
//NGS_CONSTEXPR ReturnType For(ReturnType(Class::* fn)(UINT), Class* p, ReturnType operate(ReturnType, ReturnType)) {
//    if NGS_CONSTEXPR(end - start >= 0) {
//        ReturnType result = (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start < end)
//            return operate(result, For<start + 1, end>(fn, p));
//        else
//            return result;
//    } else {
//        ReturnType result = (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start >= end)
//            return operate(For<start - 1, end>(fn, p), result);
//        else
//            return result;
//    }
//}


NGS_END

#endif // !__HEAD_NGS_TemplateMateBase_Module
