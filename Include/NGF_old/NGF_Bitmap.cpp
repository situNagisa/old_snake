//==========================================================================================================
// @file	:	NGF_Bitmap
// @author	:	NAGISA
// @data	:	2023/1/3 11:18:45
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_Bitmap.h"
#include "NGF/NGF_Stage.h"

NGF_BEGIN

NGF_Bitmap::NGF_Bitmap(NGF_PBitmapData bd):
	NGF_Bitmap()
{
	SetBitmapData(bd);
}

VOID NGF_Bitmap::SetBitmapData(NGF_PBitmapData bd)
{
	_bitmapData = bd;
	SetSize(static_cast<FLOAT>(_bitmapData->GetWidth()), static_cast<FLOAT>(_bitmapData->GetHeight()));
}

NGF_PCanvasDC NGF_Bitmap::Draw()
{
	if (!_canvas || !_bitmapData)return nullptr;
	if (_canvas->IsSelecting())_canvas->Return();
	_canvas->Select(_bitmapData->GetHBitmap());

	return _canvas;
}

VOID NGF_Bitmap::_CalculateCurBounds()
{
	_bounds.Set(0.0f, 0.0f, _size.x, _size.y);
	NGF_DisplayObject::_CalculateCurBounds();
}

NGF_END


