//==========================================================================================================
// @file	:	NGF_GDI
// @author	:	NAGISA
// @data	:	2023/1/5 22:11:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_GDI
#define __HEAD_NGF_GDI

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Vector_import.h"

NGF_BEGIN

class NGF_BitmapData;
class NGF_Rectangle;

typedef class NGF_DC {
	
public:
	NGF_DC() = delete;
	NGF_DC(HDC dc);
	NGF_DC(HWND hwnd);
	virtual ~NGF_DC();
	
	VOID Select(HGDIOBJ obj);
	VOID Return();
	VOID ReturnAndDelete();

	BOOL IsSelecting() const{ return _old != nullptr; }

	HDC GetDC() const { return _dc; }

	VOID BitBlt(const NGF_Vector2D<LONG>& aimPos, const NGF_Vector2D<LONG>& size, const NGF_DC& srcDC, const NGF_Vector2D<LONG>& srcPos);
	VOID StretchBlt(const NGF_Rectangle& aimRect, const NGF_DC& srcDC, const NGF_Rectangle& srcRect);
	VOID StretchBlt(const NGF_Rectangle& aimRect, const HDC srcDC, const NGF_Rectangle& srcRect);

	operator HDC()const { return _dc; }
protected:
	HDC _dc;
private:
	HGDIOBJ _old;
	HWND _wnd;

} *NGF_PDC;

typedef class NGF_CanvasDC:public NGF_DC {
public:
	NGF_CanvasDC(HDC dc):
		NGF_DC(dc),
		_data(nullptr),
		_offX(0L),
		_offY(0L)
	{

	}
	~NGF_CanvasDC() override;

	VOID CreateCanvas(LONG x,LONG y,LONG width, LONG height);
	VOID Release();

	NGF_Vector2D<LONG> GetOffset() const;
	
private:
	PBYTE _data;
	LONG _offX;
	LONG _offY;

} *NGF_PCanvasDC;

HBITMAP CreateDIB(_In_ LONG width, _In_ LONG height, _Outptr_ PBYTE* pImageData = nullptr);

NGF_END


#endif // !__HEAD_NGF_GDI
