//==========================================================================================================
// @file	:	NGS_Object_Module
// @author	:	NAGISA
// @data	:	2023/1/16 18:43:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Object_Module
#define __HEAD_NGS_Object_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Module.h"
#include "NGS/NGS_Bases.h"

NGS_BEGIN

class String;

class Object
{
public:
    NGS_TYPE_DEFINE(Object, this);
    NGS_TYPE_DEFINE(String, string);
public:
    //=======================================
    //	构造函数
    //=======================================

#ifdef DEBUG

    virtual ~Object() = default;

    virtual operator __string() const;

    virtual __string ToString() const;

#endif // DEBUG

    

private:

    //=======================================
    //	变量
    //=======================================
private:

public:

#ifdef _DEBUG
    //Debugger debug;
#endif // _DEBUG
};

NGS_END

#endif // !__HEAD_NGS_Object_Module
