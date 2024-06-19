//==========================================================================================================
// @file	:	NGF_BitmapData
// @author	:	NAGISA
// @data	:	2023/1/1 18:05:08
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_BitmapData.h"

NGF_BEGIN

NGF_BitmapData* NGF_BitmapData::CreateByFile(const NGF_String& file)
{
    HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    NGF_BitmapData* bitmapData = NGF_CAllocate<NGF_BitmapData>(1, hBitmap);
    return bitmapData;
}

NGF_BitmapData* NGF_BitmapData::Create(UINT32 color, LONG width, LONG height)
{
    return nullptr;
}

NGF_BitmapData::NGF_BitmapData(const HBITMAP hBitmap) :
    _hBitmap(hBitmap)
{
    GetObject(_hBitmap, sizeof(BITMAP), &_bitmap);
    _offset.SetZero();
}

NGF_BitmapData::~NGF_BitmapData()
{
    DeleteObject(_hBitmap);
}

VOID NGF_BitmapData::Destory()
{
    NGF_Free<NGF_BitmapData>(this);
}

NGF_END


