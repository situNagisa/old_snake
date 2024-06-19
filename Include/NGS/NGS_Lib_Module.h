//==========================================================================================================
// @file	:	NGS_Lib_Module
// @author	:	NAGISA
// @data	:	2023/2/16 18:05:22
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Lib_Module
#define __HEAD_NGS_Lib_Module

#include "NGS/NGS_Defined.h"

NGS_BEGIN

template<typename T,typename Arg>
NGS_INL_CSTEXPR auto&& any_cast(const Arg& arg) {
    return const_cast<T>(*reinterpret_cast<const T*>(&arg)); 
}

NGS_END


#endif // !__HEAD_NGS_Lib_Module
