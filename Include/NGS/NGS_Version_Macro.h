//==========================================================================================================
// @file	:	NGS_Header
// @author	:	NAGISA
// @data	:	2023/1/14 17:14:27
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_VERSION_MACRO
#define __HEAD_NGS_VERSION_MACRO

//_MSC_VER		MSVC
//__clang__		clang
//__GNUC__		gcc

#if defined(__clang__) || defined(__GNUC__)
#define _NGS_CPP_STANDARD __cplusplus
#elif defined(_MSC_VER)
#define _NGS_CPP_STANDARD _MSVC_LANG
#endif

#if _NGS_CPP_STANDARD >= 202300L

#define NGS_CPP_23 1
#define NGS_HAS_CPP_23 1
#define NGS_HAS_CPP_20 1
#define NGS_HAS_CPP_17 1
#define NGS_HAS_CPP_14 1
#define NGS_HAS_CPP_11 1
#define NGS_HAS_CPP_03 1

#elif _NGS_CPP_STANDARD >= 202002L

#define NGS_CPP_20 1
#define NGS_HAS_CPP_20 1
#define NGS_HAS_CPP_17 1
#define NGS_HAS_CPP_14 1
#define NGS_HAS_CPP_11 1
#define NGS_HAS_CPP_03 1

#elif _NGS_CPP_STANDARD >= 201703L

#define NGS_CPP_17 1
#define NGS_HAS_CPP_17 1
#define NGS_HAS_CPP_14 1
#define NGS_HAS_CPP_11 1
#define NGS_HAS_CPP_03 1

#elif _NGS_CPP_STANDARD >= 201402L

#define NGS_CPP_14 1
#define NGS_HAS_CPP_14 1
#define NGS_HAS_CPP_11 1
#define NGS_HAS_CPP_03 1

#elif _NGS_CPP_STANDARD >= 201103L

#define NGS_CPP_11 1
#define NGS_HAS_CPP_11 1
#define NGS_HAS_CPP_03 1

#elif _NGS_CPP_STANDARD >= 199711L

#defined NGS_CPP_03 1
#define NGS_HAS_CPP_03 1

#endif

#endif // !__HEAD_NGS_VERSION_MACRO
