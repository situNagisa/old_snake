//==========================================================================================================
// @file	:	APP
// @author	:	NAGISA
// @data	:	2023/2/13 22:39:20
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_APP
#define __HEAD_APP

#include "N_WIN/N_WIN_Library.h"
#include "N_WIN/Windows.h"
#include "N_WIN/WinEvent.h"

NGS_BEGIN

class App : public Object,public Singleton<App> , DeleteCopy{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(Window, window);
    NGS_TYPE_DEFINE(std::vector<__window_ptr>, windows);
    NGS_TYPE_DEFINE(std::wstring_view, string);

    enum class Flag : _TYP BYTE {
        IS_EXIT = bit(1),
        WND_IS_DESTORYED = bit(2)
    };
public:
    _TYP VOID Update() {
        while (!Bits(_flag, Flag::IS_EXIT)) {
            _SolveMessage();
            for (auto window : _windows_o) {
                window->SolveMessage();
                if (Bits(_flag, Flag::WND_IS_DESTORYED)) {
                    Bits<FALSE>(_flag, Flag::WND_IS_DESTORYED);
                    continue;
                }
                if (!window->NeedUpdate())continue;
                window->Update();
            }
        }
    }

#undef CreateWindow
    __window_ref CreateWindow(
        __string title,
        __rect_ref_cst windowBounds,
        _TYP FLAG flag = 0
    ) {
        Trace("App.CreateWindow Allocate::window: ");
        auto& window = *New(new Window(title,windowBounds,WindowProcess));
        

        window.SetTitle(title);

        _currentWindow = &window;
        _windows_o.push_back(&window);

        return window;
    }
    _TYP VOID DestoryWindow(__window_ref window) {
        auto n = erase(_windows_o, &window);
        if (!n) {
            //error
        }
        Trace("App.DestoryWindow Free::window: ");
        Delete(&window);
        
    }

    _TYP VOID Exit() {
        Bits<TRUE>(_flag, Flag::IS_EXIT);
    }

    static LRESULT CALLBACK WindowProcess(HWND hwindow, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        for (auto window : App::I()._windows_o) {
            if (*window != hwindow)continue;
            LRESULT result = 0;
            switch (msg){
            case WM_Event::DESTORY:
                result = window->ProcessHandler(msg, wParam, lParam);
                App::I().DestoryWindow(*window);
                Bits<TRUE>(App::I()._flag, Flag::WND_IS_DESTORYED);
                break;
            default:
                result = window->ProcessHandler(msg, wParam, lParam);
                break;
            }
            return result;
        }
        //error
        return ::DefWindowProc(hwindow, msg, wParam, lParam);
    }
    
    __window_ref CurrentWindow() { return *_currentWindow; }
    __window_ref_cst CurrentWindow()const { return *_currentWindow; }

private:
    _TYP UINT32 _SolveMessage() {
        MSG msg;
        if (!::PeekMessage(&msg, (HWND) - 1, 0, 0, PM_REMOVE))return 0;
        ::TranslateMessage(&msg);
        
        return msg.message;
    }
private:
    _TYP FLAG _flag = 0;
    __window_ptr _currentWindow = nullptr;
    __windows _windows_o;
};

NGS_END

#endif // !__HEAD_APP
