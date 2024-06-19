//==========================================================================================================
// @file	:	NGF_Defined
// @author	:	NAGISA
// @data	:	2022/12/24 10:54:33
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Defined
#define __HEAD_NGF_Defined

#include <Windows.h>

#pragma warning(disable:4005 5106)//导入Windows头文件编译器会警报宏重定义

#define NGF_BEGIN namespace nagisa{
#define NGF_END };

#define NGF_INTERNAL nagisa_internal
#define NGF_INTERNAL_BEGIN namespace nagisa_internal{
#define NGF_USE_INTERNAL using namespace ::nagisa::nagisa_internal;


#define NGF_MAIN NGF_main

#define NGF_WINDOWS_TITLE TEXT("NGF DEFAULT TITLE")

#define NGF_REGISTE_WINDOWS_CLASS TEXT("NGF nbnb")


#endif // !__HEAD_NGF_Defined
