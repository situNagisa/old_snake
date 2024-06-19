//==========================================================================================================
// @file	:	NGS_Concepts_Module
// @author	:	NAGISA
// @data	:	2023/1/16 20:53:28
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Concepts_Module
#define __HEAD_NGS_Concepts_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_TypeTrait.h"
#include "NGS/NGS_Module.h"

NGS_EXPORT
NGS_BEGIN
NGS_CONCEPT

template< class... Types,class T>
concept Any = _TYT IsAnyOf<T, Types...>;

template<class Base_, class Derived>
concept Base = _TYT IsBaseOf<Base_, Derived>;

template<class T1, class T2>
concept Same = _TYT IsSame<T1, T2>;

template<class T1,class T2>
concept Different = !Same<T1, T2>;

template<class T>
concept Integral = _TYT IsINT<T>;

template<class T>
concept UnsignedIntegral = _TYT IsUINT<T>;

template<class T>
concept SignedIntegral = !(_TYT IsUINT<T>) && _TYT IsINT<T>;

template<class T>
concept FloatingPoint = _TYT IsFLOAT<T>;

template<class T>
concept Arithmetic = _TYT IsArithmetic<T>;

template<class T>
concept Function = _TYT IsFunction<T>;



NGS_END
NGS_END

#endif // !__HEAD_NGS_Concepts_Module
