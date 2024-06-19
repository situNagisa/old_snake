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
        info.bmiHeader.biHeight *= -1;//���ø߶�Ϊ-1��ʹλͼ��ȡ�����Ͽ�ʼ��ȡ
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
        bmi.bmiHeader.biCompression = BI_RGB;//ָ��λͼ�Ƿ�ѹ������Ч��ֵΪBI_RGB(��ѹ��)��BI_RLE8��BI_RLE4��BI_BITFIELDS��Ҫ˵�����ǣ�Windowsλͼ���Բ���RLE4����RLE8��ѹ����ʽ�����õĲ��ࡣ
        bmi.bmiHeader.biSizeImage = 0;
        bmi.bmiHeader.biXPelsPerMeter = 0;// ָ��Ŀ���豸��ˮƽ�ֱ��ʣ���λ��ÿ�׵����ظ��������ڷֱ��ʵĸ�� 
        bmi.bmiHeader.biYPelsPerMeter = 0;// ָ��Ŀ���豸�Ĵ�ֱ�ֱ��ʣ���λ��ÿ�׵����ظ��������ڷֱ��ʵĸ�� 
        bmi.bmiHeader.biClrUsed = 0;//�õ�����ɫ����Ϊ0��Ϊ2 * biBitCount
        bmi.bmiHeader.biClrImportant = 0;//ָ����ͼ������Ҫ����ɫ���������ֵΪ�㣬����Ϊ���е���ɫ������Ҫ�ġ�

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
        //����ģʽ�£�������Ϊ1ʱ,BITMAPINFO�ĵڶ�����Ա��ջ�����û��������ʲô���⣬Ŀǰ������windowsר��Ҫ����Щʲô
        BITMAPINFO info[2] = {};
        if (!(pData = (BitmapData::__color_ptr)Create(ddb, info[0]))) return nullptr;
        auto bitmapData = New(new BitmapData(info[0].bmiHeader.biWidth, info[0].bmiHeader.biHeight, pData));

        return bitmapData;
    }
};

NGS_END

#endif // !__HEAD_WinBitmap
