//==========================================================================================================
// @file	:	NGF_Transform
// @author	:	NAGISA
// @data	:	2023/1/7 0:06:28
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Transform
#define __HEAD_NGF_Transform

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Object.h"



NGF_BEGIN

NGF_INTERNAL_BEGIN

NGF_END

typedef class NGF_Transform :virtual public NGF_Object {
public:

	NGF_String ToString()const override;
private:


} *NGF_PTransform;

NGF_END

#endif // !__HEAD_NGF_Transform
