//==========================================================================================================
// @file	:	Function_Module
// @author	:	NAGISA
// @data	:	2023/2/16 16:18:04
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Function_Module
#define __HEAD_NGS_Function_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL_Macro.h"
#include "NGS/NGS_Concepts.h"

NGS_BEGIN

template<_CPT Function Fn>
_TYP BOOL operator==(const std::function<Fn>& a, const std::function<Fn>& b) {
    return *(a.target<Fn>()) == *(b.target<Fn>());
}

NGS_END

#endif // !__HEAD_Function_Module
