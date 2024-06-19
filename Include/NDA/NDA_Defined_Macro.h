//==========================================================================================================
// @file	:	NDA_Macro
// @author	:	NAGISA
// @data	:	2023/1/28 1:48:49
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NDA_Defined_Macro
#define __HEAD_NDA_Defined_Macro

#include "NGS/NGS.h"

#ifdef CUSTOM_NDA_TYPE_POS
#define NDA_TYPE_POS CUSTOM_NDA_TYPE_POS
#else //CUSTOM_NDA_TYPE_POS

#if _WIN64
#define NDA_TYPE_POS _TYP FLOAT32
#elif _WIN32
#define NDA_TYPE_POS _TYP FLOAT32
#endif

#endif //CUSTOM_NDA_TYPE_POS

#ifdef CUSTOM_NDA_TYPE_SIZE
#define NDA_TYPE_SIZE CUSTOM_NDA_TYPE_SIZE
#else //CUSTOM_NDA_TYPE_SIZE

#if _WIN64
#define NDA_TYPE_SIZE _TYP SIZE_T32
#elif _WIN32
#define NDA_TYPE_SIZE _TYP SIZE_T16
#endif

#endif //CUSTOM_NDA_TYPE_SIZE

#ifdef CUSTOM_NDA_TYPE_NUM
#define NDA_TYPE_NUM CUSTOM_NDA_TYPE_NUM
#else //CUSTOM_NDA_TYPE_NUM

#if _WIN64
#define NDA_TYPE_NUM _TYP FLOAT32
#elif _WIN32
#define NDA_TYPE_NUM _TYP FLOAT32
#endif

#endif //CUSTOM_NDA_TYPE_NUM

#ifdef CUSTOM_NDA_TYPE_COLOR
#define NDA_TYPE_COLOR CUSTOM_NDA_TYPE_COLOR
#else //CUSTOM_NDA_TYPE_NUM

#if _WIN64
#define NDA_TYPE_COLOR _TYP RGB32
#elif _WIN32
#define NDA_TYPE_COLOR _TYP RGB32
#endif

#endif //CUSTOM_NDA_TYPE_NUM
#define NDA_TYPE_COLOR_T NDA_TYPE_COLOR::type


 
#define NDA_DEFAULT_TYPE                \
NGS_TYPE_DEFINE(NDA_TYPE_NUM, num);     \
NGS_TYPE_DEFINE(NDA_TYPE_SIZE, size);   \
NGS_TYPE_DEFINE(_NGS Rectangle<__num>, rect);\
NGS_TYPE_DEFINE(_NGS Matrix<__num>, matrix);\
NGS_TYPE_DEFINE(_NGS Vector2D<__num>, vector);

#endif // !__HEAD_NDA_Macro
