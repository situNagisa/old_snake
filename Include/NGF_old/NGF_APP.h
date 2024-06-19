//==========================================================================================================
// @file	:	NGF_APP
// @author	:	NAGISA
// @data	:	2022/12/28 10:19:39
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_NGF_APP
#define __HEAD_NGF_APP

#include "NGF/NGF_Defined.h"
#include "NGF/NGF_Rectangle.h"
#include "NGF/NGF_Windows.h"
#include <set>


NGF_BEGIN

class NGF_Application {
public:
	static NGF_Application* Instance() {
		static NGF_Application instance;
		return &instance;
	}
private:
	NGF_Application();
public:
	~NGF_Application();

	BOOL Run();

	NGF_PWindows OpenWindow(LPCTSTR title,const NGF_Rectangle& size);
	BOOL CloseWindow(NGF_PWindows window);
	NGF_PWindows GetCurrentWindow() { return _currentWindow; }
	
	VOID SetAnimationFPS(INT8 FPS);

	BOOL FrameHandler();
	BOOL ShutDown();

	LRESULT HandleMessage(HWND, UINT, WPARAM, LPARAM);
private:
	NGF_PWindows _GetWindowBy(const HWND hwnd);
protected:
	std::set<NGF_PWindows> _windows;
	NGF_PWindows _currentWindow;

	HINSTANCE _process;
	LARGE_INTEGER _animationInterval;
	INT8 _FPS;
};

NGF_END

#endif // !__HEAD_NGF_APP
