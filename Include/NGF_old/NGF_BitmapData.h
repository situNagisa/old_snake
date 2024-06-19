//==========================================================================================================
// @file	:	NGF_BitmapData
// @author	:	NAGISA
// @data	:	2023/1/1 17:51:35
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_BitmapData
#define __HEAD_NGF_BitmapData

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Vector.h"
#include "NGF/NGF_String.h"



NGF_BEGIN

typedef class NGF_BitmapData {
public:
	static NGF_BitmapData* CreateByFile(const NGF_String& file);
	static NGF_BitmapData* Create(UINT32 color, LONG width, LONG height);
public:
	NGF_BitmapData(const HBITMAP);
	~NGF_BitmapData();

	const NGF_Vector2D<LONG>& GetOffset() const { return _offset; }
	VOID SetOffset(LONG offX, LONG offY) { _offset.Set(offX, offY); }

	LONG GetWidth() const { return _bitmap.bmWidth; }
	LONG GetHeight() const { return _bitmap.bmHeight; }

	const HBITMAP GetHBitmap() const { return _hBitmap; }

	VOID Destory();
private:
	

private:
	HBITMAP _hBitmap;
	BITMAP _bitmap;

	NGF_Vector2D<LONG> _offset;

} *NGF_PBitmapData;

NGF_END


#endif // !__HEAD_NGF_BitmapData
