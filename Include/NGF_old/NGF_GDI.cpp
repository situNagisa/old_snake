//==========================================================================================================
// @file	:	NGF_GDI
// @author	:	NAGISA
// @data	:	2023/1/5 22:14:40
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_GDI.h"
#include "NGF/NGF_Rectangle.h"
#include "NGF/NGF_BitmapData.h"
#include "NGF/NGF_Vector.h"


NGF_BEGIN

NGF_DC::NGF_DC(HDC dc) :
	_old(nullptr),
	_wnd(nullptr)
{
	_dc = ::CreateCompatibleDC(dc);
}

NGF_DC::NGF_DC(HWND hwnd) :
	_old(nullptr),
	_wnd(hwnd),
	_dc(::GetDC(hwnd))
{
	
}

NGF_DC::~NGF_DC()
{
	Assert_Dynamic(!IsSelecting(), TEXT("请在释放前先调用Return函数"));
	if (_wnd) {
		::ReleaseDC(_wnd, _dc);
		_wnd = nullptr;
		_dc = nullptr;
		return;
	}
	DeleteDC(_dc);
	_dc = nullptr;
}

VOID NGF_DC::Select(HGDIOBJ obj)
{
	Assert_Dynamic(!IsSelecting(), TEXT("存在未释放的GDI对象"));
	_old = ::SelectObject(_dc,obj);
}

VOID NGF_DC::Return()
{
	Assert_Dynamic(IsSelecting(), TEXT("无法回退旧的GDI对象"));
	::SelectObject(_dc,_Notnull_ _old);
	_old = nullptr;
}

VOID NGF_DC::ReturnAndDelete()
{
	Assert_Dynamic(IsSelecting(), TEXT("无法回退旧的GDI对象"));
	::DeleteObject(::SelectObject(_dc, _Notnull_ _old));
	_old = nullptr;
}

NGF_CanvasDC::~NGF_CanvasDC()
{
	if (IsSelecting()) {
		NGF_DC::ReturnAndDelete();
		_data = nullptr;
	}
}

VOID NGF_CanvasDC::CreateCanvas(LONG x,LONG y,LONG width, LONG height)
{
	Release();
	_offX = x;
	_offY = y;
	NGF_DC::Select(CreateDIB(width, height,&_data));
}

VOID NGF_CanvasDC::Release()
{
	if (IsSelecting()) {
		_offX = _offY = 0L;
		NGF_DC::ReturnAndDelete();
		_data = nullptr;
	}
}

NGF_Vector2D<LONG> NGF_CanvasDC::GetOffset() const
{
	return {_offX,_offY};
}

VOID NGF_DC::BitBlt(const NGF_Vector2D<LONG>& aimPos, const NGF_Vector2D<LONG>& size, const NGF_DC& srcDC, const NGF_Vector2D<LONG>& srcPos)
{
	::BitBlt(_dc,
		static_cast<int>(aimPos.x),
		static_cast<int>(aimPos.y),
		static_cast<int>(size.x),
		static_cast<int>(size.y),
		srcDC._dc,
		static_cast<int>(srcPos.x),
		static_cast<int>(srcPos.y),
		SRCCOPY
	);
}

VOID NGF_DC::StretchBlt(const NGF_Rectangle& aimRect, const NGF_DC& srcDC, const NGF_Rectangle& srcRect)
{
	StretchBlt(aimRect, srcDC._dc, srcRect);
}

VOID NGF_DC::StretchBlt(const NGF_Rectangle& aimRect, const HDC srcDC, const NGF_Rectangle& srcRect)
{
	::StretchBlt(
		_dc,
		static_cast<int>(aimRect.x),
		static_cast<int>(aimRect.y),
		static_cast<int>(aimRect.width),
		static_cast<int>(aimRect.height),

		srcDC,
		static_cast<int>(srcRect.x),
		static_cast<int>(srcRect.y),
		static_cast<int>(srcRect.width),
		static_cast<int>(srcRect.height),

		SRCCOPY
	);
}

HBITMAP CreateDIB(_In_ LONG width, _In_ LONG height, _Outptr_ PBYTE* pImageData) {
	HBITMAP hBitmap = nullptr;
	BITMAPINFO bmi = { {0} };
	PBYTE bmp_buf = nullptr;

	/*PUINT32 pMask = reinterpret_cast<PUINT32>(&bmi.bmiColors[0]);
	*pMask++ = 0x00FF0000;
	*pMask++ = 0x0000FF00;
	*pMask++ = 0x000000FF;
	*pMask++ = 0xFF000000;*/

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biCompression = BI_RGB;//指定位图是否压缩，有效的值为BI_RGB(不压缩)，BI_RLE8，BI_RLE4，BI_BITFIELDS。要说明的是，Windows位图可以采用RLE4，和RLE8的压缩格式，但用的不多。
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;// 指定目标设备的水平分辨率，单位是每米的象素个数，关于分辨率的概念。 
	bmi.bmiHeader.biYPelsPerMeter = 0;// 指定目标设备的垂直分辨率，单位是每米的象素个数，关于分辨率的概念。 
	bmi.bmiHeader.biClrUsed = 0;//用到的颜色数，为0则为2 * biBitCount
	bmi.bmiHeader.biClrImportant = 0;//指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的。

	hBitmap = CreateDIBSection(
		NULL,
		&bmi,
		DIB_RGB_COLORS,
		reinterpret_cast<PVOID*>(&bmp_buf),
		NULL,
		0
	);

	if ((hBitmap == nullptr) || (bmp_buf == nullptr)) {
		if (pImageData != nullptr)*pImageData = nullptr;
		return nullptr;
	}
	if (pImageData != nullptr)*pImageData = bmp_buf;
	return hBitmap;
}

NGF_END
