//==========================================================================================================
// @file	:	NGF_Windows
// @author	:	NAGISA
// @data	:	2022/12/29 23:08:27
// @brief	:	
//==========================================================================================================

#include "NGF/NGF_APP.h"
#include "NGF/NGF_Windows.h"
#include "NGF/NGF_BitmapData.h"
#include <vector>
#include "NGF/NGF_Vector.h"

NGF_BEGIN

static const DWORD    g_windowstyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_VISIBLE;
static const DWORD    g_windowexstyle = WS_EX_LEFT | WS_EX_LTRREADING;

LRESULT CALLBACK NGF_WinProc(HWND hwindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    return NGF_Application::Instance()->HandleMessage(hwindow, msg, wParam, lParam);
}

//window类信息库
WNDCLASSEXW wcex = {
        sizeof(WNDCLASSEX),                                 //cbSize    本身大小
        CS_HREDRAW | CS_VREDRAW,                            //style     窗口式样
        NGF_WinProc,                                        //lpfnWndProc   事件处理函数
        0,                                                  //cbClsExtra
        0,                                                  //cbWndExtra
        nullptr,                                            //hInstance 所属窗口
        LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION)),   //hIcon  程序图标 使用程序默认图标
        LoadCursor(NULL, IDC_ARROW),                        //hCursor    程序光标
        (HBRUSH)(COLOR_WINDOW + 1),                         //hbrBackground 背景画刷
        0,             //MAKEINTRESOURCEW(def.ID_mainClass),//lpszMenuName   菜单资源
        NGF_REGISTE_WINDOWS_CLASS,                          //lpszClassName 新建类名
        0//LoadIcon(_hInstance, MAKEINTRESOURCE(def.ID_iconSmall)),//hIconSm   程序小图标

};

NGF_Windows::NGF_Windows(LPCTSTR title,const NGF_Rectangle& rect):
    _stage(nullptr)
{
    /*
    * 向指定窗口中读取字符串资源
    * LoadStringW(
    *   HINSTANCE hInstance,    //指定窗口
    *   UINT      uID,          //要加载的字符串的标识符
    *   LPWSTR    lpBuffer,     //被赋值的字符串
    *   int       cchBufferMax  //被赋值的长度
    * )
    */
    
    //LoadStringW(_hInstance, def.ID_APP_TITLE, _title, MAX_LOADSTRING);//保存窗口标题
    //LoadStringW(_hInstance, def.ID_mainClass, _mainClass, MAX_LOADSTRING);//保存窗口主类名

    //注册一个窗口类，供后续用于对 CreateWindow 或 CreateWindowEx 函数的调用
    RegisterClassExW(&wcex);
    
    _style = g_windowstyle;
    _exstyle = g_windowexstyle;
    _menu = FALSE;
    //创建一个窗口（此函数会调用后续的WndProc）
    _wnd = CreateWindowExW(
        _exstyle,
        NGF_REGISTE_WINDOWS_CLASS,
        title,                  //窗口名称
        _style,                 //窗口样式
        0,
        0,
        1,
        1,
        nullptr,                //父窗口
        nullptr,                //菜单句柄
        nullptr,                //要与窗口关联的模块实例的句柄
        nullptr                 //
    );

    if (!_wnd) {

    }
    SetWindowPositionAndSize(rect);

    _dc = NGF_CAllocate<NGF_DC>(1, _wnd);
    _canvas = NGF_CAllocate<NGF_CanvasDC>(1, _dc->GetDC());

    _stage = NGF_CAllocate<NGF_Stage>(1,this);
}

VOID NGF_Windows::Show(INT showMode)
{
    ShowWindow(_wnd, showMode);
    UpdateWindow(_wnd);
}

VOID NGF_Windows::SetWindowPositionAndSize(FLOAT x, FLOAT y, FLOAT width, FLOAT height)
{
    _rect.Set(x, y, width, height);
    _UpdateWindowRect();
}

VOID NGF_Windows::SetWindowPositionAndSize(const NGF_Rectangle& rect)
{
    _rect.Set(rect);
    _UpdateWindowRect();
}

VOID NGF_Windows::SetSize(FLOAT width, FLOAT height)
{
    _rect.width = width;
    _rect.height = height;
    _UpdateWindowRect();
}

VOID NGF_Windows::SetPosition(FLOAT x, FLOAT y)
{
    _rect.x = x;
    _rect.y = y;
    _UpdateWindowRect();
}

VOID NGF_Windows::SetTitle(LPCTSTR title)
{
    return VOID();
}

VOID NGF_Windows::Close()
{
    NGF_Free<NGF_DC>(_dc);
    NGF_Free<NGF_CanvasDC>(_canvas);
    NGF_Free<NGF_Stage>(_stage);
}

BOOL NGF_Windows::FrameHandler()
{
    
    

    return TRUE;
}

VOID NGF_Windows::Render()
{
    NGF_Vector2D<LONG> size(_rect.width, _rect.height);

    _canvas->CreateCanvas(0, 0, static_cast<LONG>(size.x), static_cast<LONG>(size.y));

    _stage->AccessChildren(
        [this](NGF_DisplayObject& child)->BOOL {
            if (!child.GetVisible())return FALSE;
            auto msg = NGF_INTERNAL::DisplayObject_GetTreeMessage(child);
            auto stage_bounds = child.GetBounds(*_stage);
            auto bounds = child.GetBounds(child);
            auto& canvas = *child.Draw();

            bounds.x = bounds.y = 0;
            if (!msg.radian) {
                _canvas->StretchBlt(stage_bounds, canvas, bounds);
                return FALSE;
            }

            return FALSE;
        },
        [](const NGF_DisplayObject& child)->BOOL {
            return !child.GetVisible();
        }
    );

    _dc->BitBlt(NGF_Vector2D_Zero<LONG>, size, *_canvas, NGF_Vector2D_Zero<LONG>);
    _canvas->Release();
}

VOID NGF_Windows::_UpdateWindowRect()
{
    RECT rect;
    rect.left = static_cast<LONG>(_rect.GetLeft());
    rect.top = static_cast<LONG>(_rect.GetTop());
    rect.right = static_cast<LONG>(_rect.GetRight());
    rect.bottom = static_cast<LONG>(_rect.GetBottom());

    ::AdjustWindowRectEx(&rect, _style, _menu, _exstyle);
    ::MoveWindow(_wnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

NGF_END


