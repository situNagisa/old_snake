//==========================================================================================================
// @file	:	NGF_Defined
// @author	:	NAGISA
// @data	:	2022/12/24 14:11:57
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Utils.h"
#include "NGF/NGF_Object.h"
#include "NGF/NGF_String.h"
#include <cassert>

NGF_BEGIN

BOOL Assert(BOOL expression, LPCTSTR text, const std::source_location& location) {
	if (expression)return TRUE;
	Trace(TEXT("\nERROR:: [ "),text,TEXT(" ]\n文件："),LPCSTR(location.file_name()),TEXT("\n函数："), LPCSTR(location.function_name()),TEXT("，第 "), INT(location.line()), TEXT(" 行，第 "),INT(location.column()), TEXT("列\n"));
	return FALSE;
}

VOID Trace(const NGF_String& message)
{
	std::wcout << message;
}
VOID Trace(const NGF_Object& message)
{
	std::wcout << message;
}

VOID Trace(LPCTSTR message)
{
	std::wcout << message;
}

NGF_END