//==========================================================================================================
// @file	:	Windows
// @author	:	NAGISA
// @data	:	2023/1/28 11:45:58
// @brief	:	
//==========================================================================================================
#pragma once

#ifndef __HEAD_Windows
#define __HEAD_Windows

#include "N_WIN/N_WIN_Library.h"
#include "N_WIN/WinEvent.h"
#include "N_WIN/WinParam.h"
#include "N_WIN/WinBitmap.h"

NGS_BEGIN

NGS_CONSTEXPR const _TYP DWORD    g_windowstyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_VISIBLE;
NGS_CONSTEXPR const _TYP DWORD    g_windowexstyle = WS_EX_LEFT | WS_EX_LTRREADING;


class Window : public Object,DeleteCopy{
public:
    NDA_DEFAULT_TYPE;
    NGS_TYPE_DEFINE(Window, this);
    NGS_TYPE_DEFINE(Stage, stage);
    NGS_TYPE_DEFINE(HDC, dc);
    NGS_TYPE_DEFINE(HWND, wnd);
    NGS_TYPE_DEFINE(DisplayObjectContainer, container);
    NGS_TYPE_DEFINE(DisplayObject, display);
    NGS_TYPE_DEFINE(std::wstring, string);
    NGS_TYPE_DEFINE(std::wstring_view, view);
    NGS_TYPE_DEFINE(EventDispatcher, dispatcher);
    NGS_TYPE_DEFINE(_TYP INT32, id);

    NGS_TYPE_DEFINE(WM_Event, evt);
    NGS_TYPE_DEFINE(W_Param, param);

    NGS_TYPE_DEFINE(KeyboardEvent, keyEvt);
    NGS_TYPE_DEFINE(KeyboardParam, keyParam);

    NGS_TYPE_DEFINE(MouseEvent, mouseEvt);
    NGS_TYPE_DEFINE(MouseParam, mouseParam);
public:
    Window(__view title,__rect_ref_cst bounds,WNDPROC handler):
        _bounds(bounds),
        _title(title)
    {
        __string classname = _title + L"class";

        _InitWindow(classname,handler);
        _Initialize();

        SetTitle(_title);
        SetBounds(_bounds);
    }
    ~Window() {
        Delete(_stage_o);
        Delete(_bd_canvas_o);

        ::ReleaseDC(_wnd_o, _dc_o);

        ::SelectObject(_canvas_o, _gdiobj);
        ::DeleteObject(_mask_o);
        ::DeleteDC(_canvas_o);
    }
    _TYP BOOL operator==(HWND wnd) { return _wnd_o == wnd; }

    _TYP BOOL NeedUpdate() {
        _time.Update();
        return _time.DeltaCount() / 1000000.0 * FPS >= 1;
    }
    _TYP UINT32 SolveMessage() {
        if (!::PeekMessage(&_msg, _wnd_o, 0, 0, PM_REMOVE))return 0;
        ::TranslateMessage(&_msg);
        ::DispatchMessage(&_msg);
        return _msg.message;
    }
    _TYP VOID Update() {
        __param p(__evt::UPDATE, this, 0, 0, (_TYP PVOID)_time.DeltaCount());
        _Dispatch(__evt::UPDATE, &p);
        _time.Record();
    }

    _TYP VOID Show(_TYP FLAG showMode) {
        ::ShowWindow(_wnd_o,showMode);
        ::UpdateWindow(_wnd_o);
    }
    _TYP VOID Close() {
        ::DestroyWindow(_wnd_o);
        PostQuitMessage(0);
    }
    _TYP VOID TryToClose() {
        __param p(__evt::CLOSE,this, 0, 0, (_TYP PVOID)TRUE);
        _TYP BOOL isClose = (_TYP BOOL)_Dispatch(__evt::CLOSE,&p);
        if (isClose)Close();
    }

    _TYP VOID SetTitle(__view title) {
        _title = title;
        ::SetWindowTextW(_wnd_o, _title.c_str());
    }
    _TYP VOID SetSize(__num width, __num height) {
        _bounds.width = width;
        _bounds.height = height;
        _UpdateWindowRect();
    }
    _TYP VOID SetPosition(__num x, __num y) {
        _bounds.x = x;
        _bounds.y = y;
        _UpdateWindowRect();
    }
    _TYP VOID SetBounds(__rect_ref_cst bounds) {
        _bounds.Set(bounds);
        _UpdateWindowRect();
    }

    _TYP VOID Render() {
        //遍历显示列表，逐个绘制显示对象
        Stage::Render(*_stage_o, *_bd_canvas_o);
        ::BitBlt(_dc_o, 0, 0, _bounds.width, _bounds.height, _canvas_o, 0, 0, SRCCOPY);
    }
    __stage_ref GetStage() { return *_stage_o; }

    LRESULT CALLBACK ProcessHandler(UINT msg, WPARAM wParam, LPARAM lParam)
    {
        switch (msg){
        case __evt::CLOSE:
            TryToClose();
            break;
        case __keyEvt::KEY_DOWN:
        case __keyEvt::KEY_UP:
        {
            __keyParam p(msg, this, wParam, lParam);
            _Dispatch<__keyEvt>(msg, &p);
        }
            break;
        case __mouseEvt::LEFT_DOUBLE_CLICK:
        case __mouseEvt::LEFT_DOWN:
        case __mouseEvt::LEFT_UP:
        case __mouseEvt::RIGHT_DOUBLE_CLICK:
        case __mouseEvt::RIGHT_DOWN:
        case __mouseEvt::RIGHT_UP:
        case __mouseEvt::MIDDLE_DOUBLE_CLICK:
        case __mouseEvt::MIDDLE_DOWN:
        case __mouseEvt::MIDDLE_UP:
        case __mouseEvt::WHEEL:
        case __mouseEvt::HOVER:
        case __mouseEvt::MOVE:
        case __mouseEvt::LEAVE:
        {
            __mouseParam p(msg, this, wParam, lParam);
            _Dispatch<__mouseEvt>(msg, &p);
            break;
        }
        default:
        {
            __param p(msg,this, wParam, lParam);
            _Dispatch(msg, &p);
            return ::DefWindowProc(_wnd_o, msg, wParam, lParam);
        }
            break;
        }
        return 0;
    }
    _TYP VOID Listen(__id id,__dispatcher::__handler_ref_cst handler) {
        _dispatcher.AddEventListener(__evt::WM_EVENT_ID(id), { handler ,this});
    }
    _TYP VOID UnListen(__id id, __dispatcher::__handler_ref_cst listener) {
        return _dispatcher.RemoveEventListener(__evt::WM_EVENT_ID(id), listener);
    }
private:
    _TYP VOID _InitWindow(__view classname,WNDPROC handler) {
        //window类信息库
        WNDCLASSEXW wcex = {
                sizeof(WNDCLASSEX),                                 //cbSize    本身大小
                CS_HREDRAW | CS_VREDRAW,                            //style     窗口式样
                handler,                                        //lpfnWndProc   事件处理函数
                0,                                                  //cbClsExtra
                0,                                                  //cbWndExtra
                nullptr,                                            //hInstance 所属窗口
                LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),   //hIcon  程序图标 使用程序默认图标
                LoadCursor(NULL, IDC_ARROW),                        //hCursor    程序光标
                (HBRUSH)(COLOR_WINDOW + 1),                         //hbrBackground 背景画刷
                0,             //MAKEINTRESOURCEW(def.ID_mainClass),//lpszMenuName   菜单资源
                classname.data(),                          //lpszClassName 新建类名
                0//LoadIcon(_hInstance, MAKEINTRESOURCE(def.ID_iconSmall)),//hIconSm   程序小图标
        };

        RegisterClassExW(&wcex);

        _style = g_windowstyle;
        _exstyle = g_windowexstyle;
        //_menu = FALSE;
        //创建一个窗口（此函数会调用后续的WndProc）
        _wnd_o = CreateWindowExW(
            _exstyle,
            classname.data(),
            _title.c_str(),                  //窗口名称
            _style,                 //窗口样式
            0, 0,
            1, 1,
            nullptr,                //父窗口
            nullptr,                //菜单句柄
            nullptr,                //要与窗口关联的模块实例的句柄
            nullptr                 //
        );

        if (!_wnd_o) {

        }

        _dc_o = ::GetDC(_wnd_o);
        _canvas_o = ::CreateCompatibleDC(_dc_o);
    }
    _TYP VOID _Initialize() {
        _stage_o = New(new Stage());

        PBYTE buf;
        _mask_o = DIB::Create(_bounds.width, _bounds.height, &buf, BitsOf<BitmapData::__color>());
        Trace("Window._Initialize Allocate::_bd_canvas_o: ");
        _bd_canvas_o = New(new BitmapData(_bounds.width, _bounds.height, reinterpret_cast<BitmapData::__color_ptr>(buf)));
        _gdiobj = ::SelectObject(_canvas_o, _mask_o);
    }

    template<class E = __evt>
    __param_ptr _Dispatch(__id id,__param_ptr param) {
        E e(id);
        e.param = param;
        _dispatcher.Dispatch(e);
        return e.GetParam();
    }
    _TYP VOID _UpdateWindowRect() {
        RECT rect;
        rect.left = static_cast<LONG>(_bounds.Left());
        rect.top = static_cast<LONG>(_bounds.Top());
        rect.right = static_cast<LONG>(_bounds.Right());
        rect.bottom = static_cast<LONG>(_bounds.Bottom());

        ::AdjustWindowRectEx(&rect, _style, FALSE, _exstyle);
        ::MoveWindow(_wnd_o, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
    }
public:
    __size FPS = 30;
private:
    HBITMAP _mask_o;
    BitmapData* _bd_canvas_o;

    __stage_ptr _stage_o;

    _TYP DWORD _style, _exstyle;
    __rect _bounds;
    __string _title;

    __dc _dc_o;
    __dc _canvas_o;
    HGDIOBJ _gdiobj;

    __wnd _wnd_o;
    __dispatcher _dispatcher;

    Duration<std::chrono::microseconds> _time;
    MSG _msg;
};

NGS_END

#endif // !__HEAD_Windows
