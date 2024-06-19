//==========================================================================================================
// @file	:	Snake_DeviceContext
// @author	:	NAGISA
// @data	:	2023/1/17 18:53:31
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_DeviceContext
#define __HEAD_Snake_DeviceContext

#include "NGS/NGS.h"
#include "Snake/Snake_Color.h"
#include "Snake/Snake_BitmapData.h"
#include "Snake/Snake_Config_Macro.h"

USE_NGS_TYPE


class DC {
private:
    using _this = DC;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this_ptr;
    using _this_ref = _this&;
    using _this_ref_cst = const _this_ref;

    using _size = UINT16;
    using _pos = INT32;

public:
    DC(
        BitmapData* pData
    ):
        _pData(pData)
    {
        
    }
    NGS_INLINE VOID DrawPoint(_pos x, _pos y,UINT16 color) {
        (*_pData)(x, y) = color;
    }
    VOID DrawLine(_pos x0, _pos y0, _pos x1, _pos y1, UINT16 color) {

    }
    VOID FillRectangle(_pos x0, _pos y0, _size width, _size height, UINT16 color) {
        for (_size i = 0; i < _pData->width; i++)
        {
            for (_size j = 0; j < _pData->height; j++)
            {
                (*_pData)(i, j) = color;
            }
        }
    }
private:
    BitmapData* _pData;
};

#endif // !__HEAD_Snake_DeviceContext
