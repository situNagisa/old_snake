//==========================================================================================================
// @file	:	InputConfig
// @author	:	NAGISA
// @data	:	2023/2/19 22:55:53
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_InputConfig
#define __HEAD_InputConfig

#include "NGS/NGS.h"

struct InputConfig
{

    NGS_CONSTEXPR InputConfig(
        auto up,
        auto left,
        auto down,
        auto right,
        auto select
    ):
        up(up),
        left(left),
        down(down),
        right(right),
        select(select)
    {}

    _TYP FLAG
        up,
        left,
        down,
        right,
        select
        ;
};

#endif // !__HEAD_InputConfig
