//==========================================================================================================
// @file	:	NGF_Object
// @author	:	NAGISA
// @data	:	2022/12/24 10:53:00
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Object
#define __HEAD_NGF_Object

#include <iostream>

#include "NGF/NGF_Defined.h"



NGF_BEGIN

class NGF_String;

class NGF_Object
{
public:
	//=======================================
	//	构造函数
	//=======================================

	NGF_Object() = default;
	NGF_Object(const NGF_Object& other) = default;

	virtual ~NGF_Object() = default;

	virtual operator NGF_String() const;

	friend std::wostream& operator<<(std::wostream& wcout, const NGF_Object& object);

	//=======================================
	//	接口
	//=======================================


	virtual NGF_String ToString() const;

private:

	//=======================================
	//	变量
	//=======================================
private:

public:

};

NGF_END

#endif // !__HEAD_NGF_Object
