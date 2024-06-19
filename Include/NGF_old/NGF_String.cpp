//==========================================================================================================
// @file	:	NGF_String
// @author	:	NAGISA
// @data	:	2022/12/24 11:08:04
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_String.h"
#include "NGF/NGF_Math.h"
#include "NGF/NGF_Memory.h"
#include <string>

NGF_BEGIN

INT32 NGF_LengthOfTchar(LPCTSTR ts) {
	int len = 0;
	while (ts[len++] != TEXT('\0'));
	return len - 1;
}

INT32 NGF_CopyTStr(__out LPTSTR buffer, __in LPCTSTR source) {
	if (!source) {
		buffer[0] = L'\0';
		return 0;
	}
	int count = 0;
	while (source[count] != TEXT('\0')) {
		*(buffer + count) = source[count];
		count++;
	}
	*(buffer + count) = TEXT('\0');
	return count;
}

INT32 NGF_TStrAdd(__out LPTSTR buffer, __in LPCTSTR first, __in LPCTSTR second) {
	int len = NGF_CopyTStr(buffer, first);
	return len + NGF_CopyTStr(buffer + len, second);
}
INT32 NGF_TStrPush(__out LPTSTR buffer, __in LPCTSTR push_string) {
	int len = NGF_LengthOfTchar(buffer);
	return len + NGF_CopyTStr(buffer + len, push_string);
}

INT32 NGF_TcharToChar(__in LPCTSTR tchar, __out LPSTR _char) {
	int iLength;
	//获取字节长度
	iLength = WideCharToMultiByte(CP_ACP, 0, tchar, -1, NULL, 0, NULL, NULL);
	//将tchar值赋给_char
	WideCharToMultiByte(CP_ACP, 0, tchar, -1, _char, iLength, NULL, NULL);
	return iLength - 1;
}

INT32 NGF_CharToTchar(__in LPCSTR _char, __out LPTSTR tchar) {
	int iLength;
	//获取字节长度
	iLength = MultiByteToWideChar(CP_ACP, 0, _char, -1, NULL, 0);
	//将tchar值赋给_char
	MultiByteToWideChar(CP_ACP, 0, _char, -1, tchar, iLength);
	return iLength - 1;
}

INT32 NGF_NumberToTchar(__in INT32 number, __out LPTSTR tchar) { return NGF_CharToTchar(std::to_string(number).c_str(), tchar); }
INT32 NGF_NumberToTchar(__in FLOAT number, __out  LPTSTR tchar) { return NGF_CharToTchar(std::to_string(number).c_str(), tchar); }
INT32 NGF_NumberToTchar(__in DOUBLE number, __out  LPTSTR tchar) { return NGF_CharToTchar(std::to_string(number).c_str(), tchar); }


LONG NGF_TcharToLong(LPCTSTR s, INT32 radix) { return wcstol(s, NULL, radix); }
FLOAT NGF_TcharToFloat(LPCTSTR s) { return wcstof(s, NULL); }
DOUBLE NGF_TcharToDouble(LPCTSTR s) { return wcstod(s, NULL); }

// ============================
// NGF_String
// ============================

NGF_String::NGF_String(SIZE_T extendCount, LPCTSTR format, ...)
{
	va_list args;
	va_start(args, format);
	_PrintIn(format, extendCount, args);
	va_end(args);
}

NGF_String::NGF_String(INT number)
{
	_ExtendStringCache(NGF_NumberBits(number));
	_length = NGF_NumberToTchar(number, _string);
}

NGF_String::NGF_String(FLOAT number)
{
	int pointBit = 0;
	int len = NGF_NumberBits(number, nullptr, &pointBit);
	_ExtendStringCache(static_cast<SIZE_T>(len) + (pointBit ? 1 : 0));
	_length = NGF_NumberToTchar(number, _string);
}

NGF_String::NGF_String(DOUBLE number)
{
	int pointBit = 0;
	int len = NGF_NumberBits(number, nullptr, &pointBit);
	_ExtendStringCache(static_cast<SIZE_T>(len) + (pointBit ? 1 : 0));
	_length = NGF_NumberToTchar(number, _string);
}

NGF_String::NGF_String(LPCSTR _char)
{
	_ExtendStringCache(strlen(_char));
	_length = NGF_CharToTchar(_char, _string);
}

NGF_String::NGF_String(LPCTSTR _tchar) {
	_ExtendStringCache(NGF_LengthOfTchar(_tchar));
	_length = NGF_CopyTStr(_string, _tchar);
}

NGF_String::NGF_String(const NGF_String& other) {
	_ExtendStringCache(other.GetLength());
	_length = NGF_CopyTStr(_string, other._string);
}

NGF_String::~NGF_String() {
	_max_length = _length = 0;
	/*
		这里用条件判断是因为移动语义可能使字符串引用为空，
		条件判断是一种较简单的解决方案，但可能有未知的bug
		正确的解决方案应该是在移动语义中完成引用的摧毁，
		具体可以是交换两String所引用的值，让右值析构左值原本的引用
	*/
	if(_string)_string.Delete();
}

INT64 NGF_String::IndexOf(const NGF_String& search,SIZE_T startIndex)
{
	if (_length - startIndex < search._length)return -1;

	for (SIZE_T i = startIndex; i < _length; i++)
	{
		if ((*this)[i] != search[0])continue;
		BOOL success = TRUE;
		for (SIZE_T j = 1; j < search._length; j++)
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

INT64 NGF_String::LastIndexOf(const NGF_String& search)
{
	if (_length < search._length)return -1;

	for (INT64 i = _length - search._length; i >= 0; i--)
	{
		if ((*this)[static_cast<SIZE_T>(i)] != search[0])continue;
		BOOL success = TRUE;
		for (SIZE_T j = 1; j < search._length; j++)
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

INT NGF_String::PrintIn(
	_In_											size_t         const _extendCount,
	_In_z_ _Printf_format_string_					wchar_t const* const _Format,
	...)
{
	va_list args;
	va_start(args, _Format);
	INT result = _PrintIn(_Format, _extendCount, args);
	va_end(args);
	return result;
}

VOID NGF_String::_ExtendStringCache(SIZE_T length,BOOL move)
{
	if (_string && length <= _max_length)return;
	LPTSTR t = NGF_Allocate<TCHAR>((_max_length = length) + 1);
	if (_string) {
		if (move)NGF_CopyTStr(t, _string.Value());
		_string.Delete();
	}
	_string.Reference(t);
}

INT NGF_String::_PrintIn(LPCTSTR format, SIZE_T extendCount, va_list args)
{
	INT bufferCount = NGF_LengthOfTchar(format) + extendCount;
	_ExtendStringCache(bufferCount);
	INT result = 0;
	result = _vswprintf_s_l(_string.GetPointer(), bufferCount, format, NULL, args);
	return result;
}

// 复制
NGF_String& NGF_String::operator=(const NGF_String& other) {
	if (&other == this)return *this;
	_ExtendStringCache(NGF_LengthOfTchar(other._string.Value()));
	_length = NGF_CopyTStr(_string.Value(), other._string.Value());

	return *this;
}

// 对tchar的支持
NGF_String& NGF_String::operator=(LPCTSTR other) {
	_ExtendStringCache(NGF_LengthOfTchar(other));
	_length = NGF_CopyTStr(_string.Value(), other);

	return *this;
}
// 对char 的支持
NGF_String& NGF_String::operator=(LPCSTR _char)
{
	_ExtendStringCache(strlen(_char));
	_length = NGF_CharToTchar(_char, _string.Value());

	return *this;
}

// 移动
NGF_String& NGF_String::operator=(NGF_String&& rvalue){
	if (&rvalue == this)return *this;

	if (_string)_string.Delete();
	_string.Move(rvalue._string);
	_length = rvalue._length;
	rvalue._length = 0;

	return *this;
}

NGF_String NGF_String::operator+(INT number) const
{
	NGF_String s(*this);
	return s += number;
}

NGF_String NGF_String::operator+(FLOAT number) const
{
	NGF_String s(*this);
	return s += number;
}

NGF_String NGF_String::operator+(DOUBLE number) const
{
	NGF_String s(*this);
	return s += number;
}

NGF_String NGF_String::operator+(LPCSTR _char) const
{
	NGF_String s(*this);
	return s += _char;
}

NGF_String NGF_String::operator+(LPCTSTR other) const
{
	NGF_String s(*this);
	return s += other;
}

NGF_String NGF_String::operator+(const NGF_String& other) const {
	NGF_String s(*this);

	return s += other;
}

NGF_String& NGF_String::operator+=(INT number)
{
	NGF_String s(number);
	*this += s;

	return *this;
}

NGF_String& NGF_String::operator+=(FLOAT number)
{
	NGF_String s(number);
	*this += s;

	return *this;
}

NGF_String& NGF_String::operator+=(DOUBLE number)
{
	NGF_String s(number);
	*this += s;

	return *this;
}

NGF_String& NGF_String::operator+=(LPCSTR _char)
{
	SIZE_T len = _length;
	_length += strlen(_char);
	_ExtendStringCache(_length,TRUE);
	NGF_CharToTchar(_char, &_string[len]);

	return *this;
}

NGF_String& NGF_String::operator+=(LPCTSTR other)
{
	_length += NGF_LengthOfTchar(other);
	_ExtendStringCache(_length, TRUE);
	NGF_TStrPush(_string.Value(), other);

	return *this;
}

NGF_String& NGF_String::operator+=(const NGF_String& other) {
	*this += other._string.Value();

	return *this;
}

NGF_String operator""_NS(LPCTSTR string, SIZE_T length)
{
	return NGF_String(string);
}

NGF_String operator+(LPCTSTR string, const NGF_String& other) {
	NGF_String s(string);
	return s += other;
}
NGF_String operator+(LPCSTR _char, const NGF_String& other) {
	NGF_String s(_char);
	return s += other;
}
NGF_String operator+(INT number, const NGF_String& string)
{
	NGF_String s(number);
	return s += string;
}

NGF_String operator+(FLOAT number, const NGF_String& string)
{
	NGF_String s(number);
	return s += string;
}

NGF_String operator+(DOUBLE number, const NGF_String& string)
{
	NGF_String s(number);
	return s += string;
}

std::wostream& operator<<(std::wostream& wcout, const NGF_String& string)
{
	wcout << static_cast<LPCTSTR>(string);
	return wcout;
}

NGF_END