//==========================================================================================================
// @file	:	Snake_Bitmap
// @author	:	NAGISA
// @data	:	2023/1/17 18:38:24
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Snake_Bitmap
#define __HEAD_Snake_Bitmap

#include "NGS/NGS.h"
#include "Snake/Snake_DisplayObject.h"
#include "Snake/Snake_BitmapData.h"

USE_NGS_TYPE

class Bitmap final:public DisplayObject<Bitmap> {
private:
    using _this = Bitmap;
    using _this_ptr = _this*;
    using _this_ptr_cst = const _this*;
    using _this_ref = _this&;
    using _this_ref_cst = const _this&;
public:

    NGS_INLINE VOID SetBitmapData(BitmapData* pData) {
        _pBitmapData = pData;
        if (!_pBitmapData)return;
        width = _pBitmapData->width;
        height = _pBitmapData->height;
        _Bounds.Set(x, y, width, height);
        requiredDraw = TRUE;
    }
    VOID Draw(_dc_ref dc) {
        for (_size iy = 0; iy < height; iy++)
        {
            for (_size ix = 0; ix < width; ix++) {
                dc.DrawPoint(x + ix,y + iy,(*_pBitmapData)(ix, iy));
            }
        }
    }
public:
    BitmapData* _pBitmapData = nullptr;
};

#endif // !__HEAD_Snake_Bitmap
