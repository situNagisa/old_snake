//==========================================================================================================
// @file	:	NGF_Bitmap
// @author	:	NAGISA
// @data	:	2022/12/28 10:40:45
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Bitmap
#define __HEAD_NGF_Bitmap


#include "NGF/NGF_Defined.h"
#include "NGF/NGF_DisplayObject.h"
#include "NGF/NGF_BitmapData.h"



NGF_BEGIN

typedef class NGF_Bitmap:public NGF_DisplayObject {
public:
	NGF_Bitmap():
		NGF_DisplayObject(),
		_bitmapData(nullptr)
	{

	}

	NGF_Bitmap(NGF_PBitmapData bd);

	VOID SetBitmapData(NGF_PBitmapData bd);

	NGF_PCanvasDC Draw() override;
	
private:
	VOID _CalculateCurBounds() override;
private:
	NGF_PBitmapData _bitmapData;

} *NGF_PBitmap;

NGF_END

#endif // !__HEAD_NGF_Bitmap
