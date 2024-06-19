//==========================================================================================================
// @file	:	NGF_Object
// @author	:	NAGISA
// @data	:	2022/12/24 11:08:16
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Object.h"
#include "NGF/NGF_String.h"

NGF_BEGIN

std::wostream& operator<<(std::wostream& wcout, const NGF_Object& object)
{
	return wcout << object.ToString();
}

NGF_Object::operator NGF_String() const
{
	return ToString();
}

NGF_String NGF_Object::ToString() const
{
	return TEXT("Object::");
}

NGF_END
