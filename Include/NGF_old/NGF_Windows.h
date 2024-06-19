//==========================================================================================================
// @file	:	NGF_Windows
// @author	:	NAGISA
// @data	:	2022/12/27 16:21:05
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_Windows
#define __HEAD_NGF_Windows

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Rectangle.h"
#include "NGF/NGF_Stage.h"
#include "NGF/NGF_GDI.h"



NGF_BEGIN

typedef class NGF_Windows {
public:
	NGF_Windows(LPCTSTR title,const NGF_Rectangle& rect);

	NGF_Windows(const NGF_Windows&) = delete;
	NGF_Windows& operator=(const NGF_Windows&) = delete;

	BOOL operator==(const HWND hwnd)const { return _wnd == hwnd; }

	VOID Show(INT showMode);
	VOID SetWindowPositionAndSize(FLOAT x, FLOAT y, FLOAT width, FLOAT height);
	VOID SetWindowPositionAndSize(const NGF_Rectangle& rect);
	VOID SetSize(FLOAT width, FLOAT height);
	VOID SetPosition(FLOAT x, FLOAT y);
	VOID SetTitle(LPCTSTR title);

	NGF_PStage GetStage()const {return _stage;}

	NGF_PDC GetDC() const { return _dc; }
	NGF_PCanvasDC GetCanvasDC() const { return _canvas; }

	VOID Close();
	
	BOOL FrameHandler();
	VOID Render();
private:
	VOID _UpdateWindowRect();
private:
	HWND _wnd;
	DWORD _style;
	DWORD _exstyle;
	BOOL _menu;

	NGF_PDC _dc;
	NGF_PCanvasDC _canvas;
	
	NGF_Rectangle _rect;

	NGF_PStage _stage;

	friend LRESULT CALLBACK NGF_WinProc(HWND, UINT, WPARAM, LPARAM);

} *NGF_PWindows;

LRESULT CALLBACK NGF_WinProc(HWND, UINT, WPARAM, LPARAM);

NGF_END


#endif // !__HEAD_NGF_Windows
