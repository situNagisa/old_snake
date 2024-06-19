//==========================================================================================================
// @file	:	NGS_String_Module
// @author	:	NAGISA
// @data	:	2023/1/16 18:48:31
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_String_Module
#define __HEAD_NGS_String_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Module.h"

NGS_BEGIN

NGS_EXPORT
class String
{
public:
    using __size = _TYP SIZE_T16;

    using __char = _TYP CHAR8;

    NGS_TYPE_DEFINE(String, this);
    NGS_TYPE_DEFINE(__char*, str);
    
private:
    //=======================================
    //	�ڲ�����
    //=======================================
    __size _max_length = 0;
    __size _length = 0;
    __str _string;
public:
    //=======================================
    //	�ӿڱ���
    //=======================================

public:
    //=======================================
    //	���캯��
    //=======================================

    //���캯��
    String()
    {
        //_ExtendStringCache(0);
        _string[0] = 0;
        _length = 0;
    }
    //NGS_String(SIZE_T extendCount, LPCTSTR format, ...);
    //NGS_String(INT number);
    //NGS_String(FLOAT number);
    //NGS_String(DOUBLE number);
    //NGS_String(LPCSTR s);
    //NGS_String(LPCTSTR s);
    String(__this_ref_cst other);

    ~String();

    _TYP INT64 IndexOf(__this_ref_cst search, __size startIndex = 0);
    _TYP INT64 LastIndexOf(__this_ref_cst search);
    //=======================================
    //	���������
    //=======================================

    operator _TYP BOOL() const { return _length > 0; }

    //operator LPCTSTR() const { return _string; }

    //������ֵ����
    __this_ref operator=(__this_ref_cst other);
    __this_ref operator=(__str_cst other);
    //NGS_String& operator=(LPCSTR _char);
    //�ƶ���ֵ����
    __this_ref operator=(__this&& rvalue);

    //�±����
    __char& operator[](const __size index) { return _string[index]; }
    //�����±����
    const __char& operator[](__size index) const { return _string[index]; }

    //���ַ������
    // String �� ���� ���
    //_this operator+(INT number) const;
    //_this operator+(FLOAT number) const;
    //_this operator+(DOUBLE number) const;
    //String�� �ַ����� ���
    //_this operator+(LPCSTR _char)const;
    //_this operator+(LPCTSTR other) const;
    //String �� String ���
    __this operator+(__this_ref_cst other) const;

    //
    //_this_ref operator+=(INT number);
    //_this_ref operator+= (FLOAT number);
    //_this_ref operator+=(DOUBLE number);

    //_this_ref operator+=(LPCSTR _char);
    //_this_ref operator+=(LPCTSTR other);

    __this_ref operator+=(__this_ref_cst other);


    //friend std::wostream& operator<<(std::wostream& wcout, const NGS_String& string);
    //=======================================
    //	�ӿ�
    //=======================================
    __size GetLength()const { return _length; }
    //LPCTSTR 
    /*_this ToString() const {
        _str s = TEXT("String::");
        s += static_cast<LPTSTR>(_string);
        return s;
    }*/
    /*INT PrintIn(
        _In_                                          size_t         const _ExtendCount,
        _In_z_ _Printf_format_string_                 wchar_t const* const _Format,
        ...);*/
private:
    _TYP VOID _ExtendStringCache(__size length, _TYP BOOL move = FALSE);
    /*INT _PrintIn(
        LPCTSTR format,
        SIZE_T	extendCount,
        va_list args
    );*/
};


NGS_END

#endif // !__HEAD_NGS_String_Module
