//==========================================================================================================
// @file	:	Snake_Food
// @author	:	NAGISA
// @data	:	2023/1/19 15:25:20
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Food
#define __HEAD_Snake_Food

#include "NGS/NGS.h"
#include "Snake/Snake_Rectangle.h"
#include "Snake/Snake_Bitmap.h"

USE_NGS_TYPE

struct Food
{
private:
    using _pos = INT16;
public:
    INT8 power;
    Bitmap bitmap;
private:

public:
    NGS_INLINE
    Food(
        INT8 power = 1
    ):
        power(power),
        bitmap()
    {}
    NGS_INLINE VOID SetPosition(_pos x, _pos y) {
        x -= bitmap.x;
        y -= bitmap.y;
        bitmap.BoundsMove(x, y);

        bitmap.x += x;
        bitmap.y += y;
    }

    NGS_INLINE BOOL operator==(const Food& food)const { return this == &food; }
};

#endif // !__HEAD_Snake_Food
