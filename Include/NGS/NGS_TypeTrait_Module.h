//==========================================================================================================
// @file	:	NGS_TypeTrait_Module
// @author	:	NAGISA
// @data	:	2023/1/16 20:48:34
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_TypeTrait_Module
#define __HEAD_NGS_TypeTrait_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Config.h"
#include "NGS/NGS_Module.h"

#include "NGS/NGS_STL_Macro.h"

NGS_BEGIN

NGS_TYPE_TRAIT

//template<class T, T val>
//struct INT_CST
//{
//    static NGS_CONSTEXPR T value = val;
//
//    using value_type = T;
//    using type = INT_CST;
//
//    NGS_CONSTEXPR operator value_type()const noexcept {
//        return value;
//    }
//
//    NGS_CONSTEXPR value_type operator()()const noexcept {
//        return value;
//    }
//};
//
//template<_TYP BOOL val>
//using BOOL_CST = INT_CST<_TYP BOOL, val>;
//using TRUE_CST = BOOL_CST<TRUE>;
//using FALSE_CST = BOOL_CST<FALSE>;
//
//NGS_EXPORT
//template<class, class>
//NGS_INL_CSTEXPR const _TYP BOOL IsSame = FALSE;
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR const _TYP BOOL IsSame<T, T> = TRUE;
//
//template<class T1, class T2>
//struct _IsSame : BOOL_CST < IsSame<T1, T2>> {};
//
//
//template<class T>
//struct Remove_cv {
//    using type = T;
//};
//template<class T>
//struct Remove_cv<const T> {
//    using type = T;
//};
//template<class T>
//struct Remove_cv<volatile T> {
//    using type = T;
//};
//template<class T>
//struct Remove_cv<const volatile T> {
//    using type = T;
//};
//
//NGS_EXPORT
//template<class T>
//using Remove_cv_t = Remove_cv<T>::type;
//
//condition:true
template<_TYP BOOL First_value, class First, class... Rest>
struct _Disjuction {
    using type = First;
};
//condition:false
template<class First, class Next, class... Rest>
struct _Disjuction<FALSE, First, Next, Rest...> {
    using type = typename _Disjuction<Next::value, Next, Rest...>::type;
};

template<class... Types>
struct Disjuction :std::integral_constant<_TYP BOOL,FALSE> {};
template<class First, class... Types>
struct Disjuction<First, Types...> :_Disjuction<First::value, First, Types...>::type {};

template<class...Traits>
NGS_INL_CSTEXPR _TYP BOOL Disjuction_v = Disjuction<Traits...>::value;

//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR _TYP BOOL IsINT = IsAnyOf<Remove_cv_t<T>, bool, char, signed char, unsigned char,
//    wchar_t,
//#ifdef __cpp_char8_t
//    char8_t,
//#endif // __cpp_char8_t
//    char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>;
//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR _TYP BOOL IsUINT = IsAnyOf<Remove_cv_t<T>, bool, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long>;
//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR _TYP BOOL IsFLOAT = IsAnyOf<Remove_cv_t<T>, float, double, long double>;
//
//NGS_EXPORT
//template<class T>
//NGS_INL_CSTEXPR _TYP BOOL IsArithmetic = IsFLOAT<T> || IsINT<T>;


//真正的完美转发

NGS_EXPORT
template<class Base, class Derived>
NGS_INL_CSTEXPR _TYP BOOL IsBaseOf = std::is_base_of_v<Base, Derived>;


NGS_EXPORT
template<class A, class B>
NGS_INL_CSTEXPR _TYP BOOL IsSame = std::is_same_v<A, B>;

NGS_EXPORT
template<class A, class... Types>
NGS_INL_CSTEXPR _TYP BOOL IsAnyOf = Disjuction_v<IsSame<A, Types>...>;


NGS_EXPORT
template<class T>
NGS_INL_CSTEXPR _TYP BOOL IsINT = std::is_integral_v<T>;

NGS_EXPORT
template<class T>
NGS_INL_CSTEXPR _TYP BOOL IsUINT = std::is_unsigned_v<T> && IsINT<T>;

template<class T>
NGS_EXPORT NGS_INL_CSTEXPR _TYP BOOL IsUnsigned = std::is_unsigned_v<T>;


template<class T>
NGS_EXPORT NGS_INL_CSTEXPR 
_TYP BOOL IsFLOAT = std::is_floating_point_v<T>;

template<class T>
NGS_EXPORT NGS_INL_CSTEXPR 
_TYP BOOL IsArithmetic = std::is_arithmetic_v<T>;

template<class T>
NGS_EXPORT NGS_INL_CSTEXPR
_TYP BOOL IsFunction = std::is_function_v<T>;

template<_TYP BOOL b,class T1,class T2>
NGS_EXPORT
using Conditional = std::conditional_t<b, T1, T2>;

template<typename Type>
struct TemplateEX;

template<template<typename...>class Template, typename ...Args>
struct TemplateEX<Template<Args...>>
{
    template<typename...NewArgs>
    using type = Template<NewArgs...>;
    template<template<typename...>class NewTemplate>
    using apply = NewTemplate<Args...>;

    constexpr static auto size = sizeof... (Args);
};

//=======================================
//	Function
//=======================================

NGS_EXPORT
template<typename Fn>
struct FunctionTrait {};

NGS_EXPORT
template<typename ReturnType, typename... Args>
struct FunctionTrait<ReturnType(Args...)> {
    using type = ReturnType(*)(Args...);
    using return_type = ReturnType;

    NGS_INL_CSTEXPR static _TYP SIZE_T16 param_num = sizeof...(Args);
};

NGS_EXPORT
template<typename ReturnType, typename Class, typename... Args>
struct FunctionTrait<ReturnType(Class::*)(Args...)> {
    using type = ReturnType(*)(Class*, Args...);
    using return_type = ReturnType;

    NGS_INL_CSTEXPR static _TYP SIZE_T16 param_num = sizeof...(Args);
};

NGS_EXPORT
template<typename Fn>
using FunctionReturnType = FunctionTrait<Fn>::return_type;

NGS_EXPORT
template<typename Fn>
NGS_INL_CSTEXPR _TYP SIZE_T16 FunctionParamsNum = FunctionTrait<Fn>::param_num;

NGS_END
NGS_END

#endif // !__HEAD_NGS_TypeTrait_Module
