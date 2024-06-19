//==========================================================================================================
// @file	:	NGS_Config_Module
// @author	:	NAGISA
// @data	:	2023/2/9 17:41:59
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Setting_Module
#define __HEAD_NGS_Setting_Module

#include "NGS/NGS_Config.h"
#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Memory.h"
#include "NGS/NGS_STL_Macro.h"

NGS_BEGIN

template<typename T = _TYP VOID>
NGS_EXPORT NGS_INLINE
T* Malloc(_TYP SIZE_T32 count) { return Allocator::I().Allocate<T>(count); }

NGS_EXPORT NGS_INLINE
_TYP VOID Free(_TYP PVOID block) { Allocator::I().Free(block); }


template<typename T>
T* New(T* block, _TYP SIZE_T32 count = 1) { return Allocator::I().New(block, count); }

template<typename T>
_TYP VOID Delete(T* block) { Allocator::I().Delete(block); }

template<typename T>
_TYP VOID DeleteArray(T* block) { Allocator::I().DeleteArray(block); }




NGS_INLINE _TYP VOID Trace(_TYP PCSTR8 string) {
    std::cout << string << std::endl;
}
template<class... Args>
NGS_INLINE _TYP VOID Trace(_TYP PCSTR8 string, const Args&... args) {
    
}

#ifdef _DEBUG

NGS_INLINE _TYP VOID Assert(
    _TYP BOOL b,
    _TYP PCSTR8 text = "",
    const std::source_location& location = std::source_location::current()
) {
    if (b)return;
    _TYP CHAR8 message[300];
    sprintf_s(message,
        ""
        "\n========================="
        "\nERROR::[ %s ]"
        "\n文件：%s"
        "\n函数：%s"
        "\n第 %d 行，第 %d 列"
        "\n=========================\n",
        text,
        location.file_name(),
        location.function_name(),
        location.line(),
        location.column()
    );
    Trace(message);
    abort();
}

#else

#define Assert(...)

#endif // _DEBUG


NGS_END

#endif // !__HEAD_NGS_Setting_Module
