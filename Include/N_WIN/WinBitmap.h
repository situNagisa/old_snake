//==========================================================================================================
// @file	:	WinBitmap
// @author	:	NAGISA
// @data	:	2023/2/14 21:41:11
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_WinBitmap
#define __HEAD_WinBitmap

#include "N_WIN/N_WIN_Library.h"

NGS_BEGIN

class _WinBitmap : public Object{

};

class DDB : public _WinBitmap {
public:
    static HBITMAP Load(_TYP PTR source) {
        return (HBITMAP)::LoadImageW(
            ::GetModuleHandle(NULL),
            MAKEINTRESOURCE(source),
            IMAGE_BITMAP,
            0, 0,
            0
        );
    }
    static HBITMAP Load(_TYP PCWCHAR file) {
        return (HBITMAP)::LoadImageW(
            ::GetModuleHandle(NULL),
            file,
            IMAGE_BITMAP,
            0, 0,
            LR_LOADFROMFILE
        );
    }
};

class DIB : public _WinBitmap {
public:
    static _TYP PBYTE Create(HBITMAP ddb, BITMAPINFO& info) {
        HDC tool = ::CreateCompatibleDC(NULL);

        info.bmiHeader.biSize = sizeof(info.bmiHeader);

        ::GetDIBits(tool, ddb, 0, 0, NULL, &info, DIB_RGB_COLORS);
        _TYP PBYTE pData = New(new _TYP BYTE[info.bmiHeader.biSizeImage](), info.bmiHeader.biSizeImage);
        info.bmiHeader.biHeight *= -1;//设置高度为-1，使位图读取从左上开始读取
        ::GetDIBits(tool, ddb, 0, info.bmiHeader.biHeight, pData, &info, DIB_RGB_COLORS);
        info.bmiHeader.biHeight *= -1;


        ::DeleteDC(tool);
        return pData;
    }

    static HBITMAP Create(_TYP INT32 width, _TYP INT32 height, _TYP PBYTE* pImageData, _TYP UINT8 bitCount = 32)
    {
        HBITMAP hBitmap = nullptr;
        BITMAPINFO bmi = {};
        PBYTE bmp_buf = nullptr;

        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = width;
        bmi.bmiHeader.biHeight = -height;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = bitCount;
        bmi.bmiHeader.biCompression = BI_RGB;//指定位图是否压缩，有效的值为BI_RGB(不压缩)，BI_RLE8，BI_RLE4，BI_BITFIELDS。要说明的是，Windows位图可以采用RLE4，和RLE8的压缩格式，但用的不多。
        bmi.bmiHeader.biSizeImage = 0;
        bmi.bmiHeader.biXPelsPerMeter = 0;// 指定目标设备的水平分辨率，单位是每米的象素个数，关于分辨率的概念。 
        bmi.bmiHeader.biYPelsPerMeter = 0;// 指定目标设备的垂直分辨率，单位是每米的象素个数，关于分辨率的概念。 
        bmi.bmiHeader.biClrUsed = 0;//用到的颜色数，为0则为2 * biBitCount
        bmi.bmiHeader.biClrImportant = 0;//指定本图象中重要的颜色数，如果该值为零，则认为所有的颜色都是重要的。

        bmi.bmiColors;

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

    static BitmapData* Create(HBITMAP ddb) {
        BitmapData::__color_ptr pData = nullptr;
        //调试模式下，当长度为1时,BITMAPINFO的第二个成员会栈溢出，没看出来是什么问题，目前怀疑是windows专门要设置些什么
        BITMAPINFO info[2] = {};
        if (!(pData = (BitmapData::__color_ptr)Create(ddb, info[0]))) return nullptr;
        auto bitmapData = New(new BitmapData(info[0].bmiHeader.biWidth, info[0].bmiHeader.biHeight, pData));

        return bitmapData;
    }
};

NGS_END

#endif // !__HEAD_WinBitmap
