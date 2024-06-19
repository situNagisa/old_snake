//==========================================================================================================
// @file	:	NGF_String
// @author	:	NAGISA
// @data	:	2022/12/24 10:53:10
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_String
#define __HEAD_NGF_String

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Ref.h"



NGF_BEGIN

class NGF_String
{
private:
	//=======================================
	//	内部变量
	//=======================================
	SIZE_T _max_length = 0;
	SIZE_T _length = 0;
	NGF_StrictRef<TCHAR,TRUE> _string;
public:
	//=======================================
	//	接口变量
	//=======================================

public:
	//=======================================
	//	构造函数
	//=======================================

	//构造函数
	NGF_String()
	{
		_ExtendStringCache(0);
		_string[0] = TEXT('\0');
		_length = 0;
	}
	NGF_String(SIZE_T extendCount, LPCTSTR format, ...);
	NGF_String(INT number);
	NGF_String(FLOAT number);
	NGF_String(DOUBLE number);
	NGF_String(LPCSTR s);
	NGF_String(LPCTSTR s);
	NGF_String(const NGF_String& other);

	~NGF_String();

	INT64 IndexOf(const NGF_String& search, SIZE_T startIndex = 0);
	INT64 LastIndexOf(const NGF_String& search);
	//=======================================
	//	运算符重载
	//=======================================

	operator BOOL() const { return _length > 0; }

	operator LPCTSTR() const { return _string; }

	//拷贝赋值函数
	NGF_String& operator=(const NGF_String& other);
	NGF_String& operator=(LPCTSTR other);
	NGF_String& operator=(LPCSTR _char);
	//移动赋值函数
	NGF_String& operator=(NGF_String&& rvalue);

	//下标访问
	TCHAR& operator[](const SIZE_T index) { return _string[index]; }
	//常量下标访问
	const TCHAR& operator[](SIZE_T index) const { return _string[index]; }

	//两字符串相加
	// String 与 数字 相加
	NGF_String operator+(INT number) const;
	NGF_String operator+(FLOAT number) const;
	NGF_String operator+(DOUBLE number) const;
	//String与 字符常量 相加
	NGF_String operator+(LPCSTR _char)const;
	NGF_String operator+(LPCTSTR other) const;
	//String 与 String 相加
	NGF_String operator+(const NGF_String& other) const;

	//
	NGF_String& operator+=(INT number);
	NGF_String& operator+= (FLOAT number);
	NGF_String& operator+=(DOUBLE number);

	NGF_String& operator+=(LPCSTR _char);
	NGF_String& operator+=(LPCTSTR other);

	NGF_String& operator+=(const NGF_String& other);


	friend std::wostream& operator<<(std::wostream& wcout, const NGF_String& string);
	//=======================================
	//	接口
	//=======================================
	SIZE_T GetLength()const { return _length; }
	//LPCTSTR 
	NGF_String ToString() const {
		NGF_String s = TEXT("String::");
		s += static_cast<LPTSTR>(_string);
		return s;
	}
	INT PrintIn(
		_In_                                          size_t         const _ExtendCount,
		_In_z_ _Printf_format_string_                 wchar_t const* const _Format,
		...);
private:
	VOID _ExtendStringCache(SIZE_T length,BOOL move = FALSE);
	INT _PrintIn(
		LPCTSTR format,
		SIZE_T	extendCount,
		va_list args
	);
};

NGF_String operator""_NS(LPCTSTR string, SIZE_T length);

//字符常量 与 String 相加
NGF_String operator+(LPCTSTR string, const NGF_String& other);
NGF_String operator+(LPCSTR _char, const NGF_String& other);

// String 与 数字 相加
NGF_String operator+(INT number, const NGF_String& string);
NGF_String operator+(FLOAT number, const NGF_String& string);
NGF_String operator+(DOUBLE number, const NGF_String& string);



INT32 NGF_LengthOfTchar(LPCTSTR ts);
INT32 NGF_CopyTStr(__out LPTSTR buffer, __in LPCTSTR source);
INT32 NGF_TStrAdd(__out LPTSTR buffer, __in LPCTSTR first, __in LPCTSTR second);
INT32 NGF_TStrPush(__out LPTSTR buffer, __in LPCTSTR push_string);

INT32 NGF_TcharToChar(__in LPCTSTR tchar, __out LPSTR _char);
INT32 NGF_CharToTchar(__in LPCSTR _char, __out LPTSTR tchar);


INT32 NGF_NumberToTchar(__in INT32 number, __out LPTSTR tchar);
INT32 NGF_NumberToTchar(__in FLOAT number, __out LPTSTR tchar);
INT32 NGF_NumberToTchar(__in DOUBLE number, __out LPTSTR tchar);

LONG NGF_TcharToLong(LPCTSTR s, INT32 radix = 10);
FLOAT NGF_TcharToFloat(LPCTSTR s);
DOUBLE NGF_TcharToDouble(LPCTSTR s);

NGF_END

#endif // !__HEAD_NGF_String
