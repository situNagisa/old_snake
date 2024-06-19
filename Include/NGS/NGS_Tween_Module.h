//==========================================================================================================
// @file	:	NGS_Tween_Module
// @author	:	NAGISA
// @data	:	2023/2/16 22:20:18
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGS_Tween_Module
#define __HEAD_NGS_Tween_Module

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL_Macro.h"
#include "NGS/NGS_Object.h"
#include "NGS/NGS_Movie.h"

NGS_BEGIN

struct ReservedProps {

};


class Tween : public Movie{
public:
    NGS_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(Tween, this);


public:
    //Tween()
};

NGS_END

#endif // !__HEAD_NGS_Tween_Module
