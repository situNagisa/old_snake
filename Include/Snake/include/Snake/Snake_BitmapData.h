//==========================================================================================================
// @file	:	Snake_BitmapData
// @author	:	NAGISA
// @data	:	2023/1/17 19:36:46
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_BitmapData
#define __HEAD_Snake_BitmapData

#include "NGS/NGS.h"
#include "Snake/Snake_Color.h"
#include "Snake/Snake_Config_Macro.h"

USE_NGS_TYPE

class BitmapData {
private:
    using _size = SIZE_T16;
public:
    NGS_INL_CSTEXPR
    BitmapData(
        _size width,
        _size height,
        GAME_RGB* pData
    ):
        width(width),
        height(height),
        _pData(pData)
    {

    }
    NGS_INLINE GAME_RGB& operator()(_size x, _size y) {
        return _pData[x * height + y];
    }
    NGS_INLINE const GAME_RGB& operator()(_size x, _size y) const{
        return _pData[x * height + y];
    }
public:
    const _size width;
    const _size height;
private:
    GAME_RGB* _pData = nullptr;
};

#endif // !__HEAD_Snake_BitmapData
