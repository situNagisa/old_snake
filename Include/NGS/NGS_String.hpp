//==========================================================================================================
// @file	:	NGS_String
// @author	:	NAGISA
// @data	:	2023/1/16 19:28:37
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_String_HPP
#define __HEAD_NGS_String_HPP

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_String.h"

NGS_BEGIN
USE_NGS_TYPE

String::String(__this_ref_cst other)
{
}
String::~String() {
    _max_length = _length = 0;
    /*
        这里用条件判断是因为移动语义可能使字符串引用为空，
        条件判断是一种较简单的解决方案，但可能有未知的bug
        正确的解决方案应该是在移动语义中完成引用的摧毁，
        具体可以是交换两String所引用的值，让右值析构左值原本的引用
    */
    //if (_string)_string.Delete();
}

INT64 String::IndexOf(__this_ref_cst search, __size startIndex)
{
    if (_length - startIndex < search._length)return -1;

    for (__size i = startIndex; i < _length; i++)
    {
        if ((*this)[i] != search[0])continue;
        BOOL success = TRUE;
        for (__size j = 1; j < search._length; j++)
        {
            if ((*this)[i + j] != search[j]) {
                success = FALSE;
                break;
            }
        }
        if (!success)continue;
        return i;
    }
    return -1;
}

INT64 String::LastIndexOf(__this_ref_cst search)
{
    if (_length < search._length)return -1;

    for (INT64 i = _length - search._length; i >= 0; i--)
    {
        if ((*this)[static_cast<__size>(i)] != search[0])continue;
        BOOL success = TRUE;
        for (__size j = 1; j < search._length; j++)
        {
            if ((*this)[i + j] != search[j]) {
                success = FALSE;
                break;
            }
        }
        if (!success)continue;
        return i;
    }
    return -1;
}

NGS_END



#endif // !__HEAD_NGS_String_Impl
