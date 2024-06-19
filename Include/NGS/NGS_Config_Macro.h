//==========================================================================================================
// @file	:	NGS_Config_Macro
// @author	:	NAGISA
// @data	:	2023/1/15 0:14:26
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Config_Macro
#define __HEAD_NGS_Config_Macro

#include "NGS/NGS_Version_Macro.h"

#ifdef NGS_HAS_CPP_17
#define NGS_INLINE inline
#elif //NGS_HAS_CPP17
#define NGS_INLINE
#endif  //NGS_HAS_CPP17

#ifdef NGS_HAS_CPP_17

#define NGS_INL_CSTEXPR inline constexpr
#define NGS_INLINE inline
#define NGS_CONSTEXPR constexpr
#define NGS_CST_IF  if constexpr
#define NGS_CST_EIF else if constexpr
#define NGS_CST_ELSE else

#elif //NGS_HAS_CPP17

#define NGS_INL_CSTEXPR
#define NGS_INLINE
#define NGS_CONSTEXPR
#define NGS_CST_IF
#define NGS_CST_EIF
#define NGS_CST_ELSE

#endif  //NGS_HAS_CPP17


#endif // !__HEAD_NGS_Config_Macro
