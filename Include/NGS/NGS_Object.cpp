//==========================================================================================================
// @file	:	NGS_Object
// @author	:	NAGISA
// @data	:	2022/12/24 11:08:16
// @brief	:	
//==========================================================================================================

#include "NGS/NGS_String.h"
#include "NGS/NGS_Defined.h"
#include "NGS/NGS_Object.h"

NGS_BEGIN

#ifdef DEBUG

Object::operator String() const
{
    return ToString();
}

String Object::ToString() const
{
    return String();// TEXT("Object::");
}

#endif // DEBUG



NGS_END
