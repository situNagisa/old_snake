//==========================================================================================================
// @file	:	NGF_APP
// @author	:	NAGISA
// @data	:	2022/12/29 22:45:27
// @brief	:	
//==========================================================================================================


#include "NGF/NGF_APP.h"
#include "NGF/NGF_Memory.h"
#include "NGF/NGF_Math.h"

extern BOOL NGF_MAIN();

NGF_BEGIN

NGF_Application::NGF_Application() :
    _process(GetModuleHandle(NULL)),
    _FPS(60)
{
    SetAnimationFPS(60);
    _animationInterval.QuadPart = 0;
}

NGF_Application::~NGF_Application() {
	//析构代码有待商榷
	
	_process = nullptr;
}

BOOL NGF_Application::Run()
{
	NGF_PWindows firstWindow = OpenWindow(NGF_WINDOWS_TITLE, { NGF_WINDOW_POS_X, NGF_WINDOW_POS_Y, NGF_WINDOWS_WIDTH, NGF_WINDOWS_HEIGHT });//创建窗口

    if (!NGF_MAIN())return FALSE;//用户接口

    // Main message loop:
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    QueryPerformanceCounter(&nLast);

    LONGLONG interval = 0LL;
    LONG waitMS = 0L;

    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    //游戏主循环
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        QueryPerformanceCounter(&nNow);
        interval = nNow.QuadPart - nLast.QuadPart;
        if (interval >= _animationInterval.QuadPart)
        {
            nLast.QuadPart = nNow.QuadPart;
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else {
                if (!FrameHandler())break;
            }
        }
        else
        {
            //时间片
            waitMS = static_cast<LONG>((_animationInterval.QuadPart - interval) * 1000LL / freq.QuadPart - 1L);
            if (waitMS > 1L)
                Sleep(waitMS);
        }
    }

    //管理窗口关闭
    ShutDown();

#ifdef _DEBUG
    NGF_MemoryAllocator::Instance()->Show();
    //std::cout << "此类占用内存：" << NGF_MemoryAllocator::Instance()->SizeOf(this) << " bytes" << std::endl;
#endif // _DEBUG

	return TRUE;
}

VOID NGF_Application::SetAnimationFPS(INT8 FPS)
{
    _FPS = FPS;
    FLOAT interval = static_cast<FLOAT>(1 / _FPS);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    _animationInterval.QuadPart = (LONGLONG)(interval * freq.QuadPart);
}

BOOL NGF_Application::FrameHandler()
{
    for (auto& i : _windows) {
        if (!i->FrameHandler())return FALSE;
        i->Render();
    }


    return TRUE;
}

BOOL NGF_Application::ShutDown()
{
    auto CopyWindows = _windows;
    for (auto& i : CopyWindows) {
        CloseWindow(i);
    }
    return TRUE;
}

LRESULT NGF_Application::HandleMessage(HWND hwindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        /*auto pnwnd = _GetWindowBy(hwindow);
        pnwnd->Show();*/
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }
    return DefWindowProc(hwindow, msg, wParam, lParam);

}

NGF_PWindows NGF_Application::_GetWindowBy(const HWND hwnd)
{
    for (auto& i : _windows) {
        if (*i == hwnd)return i;
    }
    return nullptr;
}

NGF_PWindows NGF_Application::OpenWindow(LPCTSTR title,const NGF_Rectangle& size)
{
	NGF_PWindows pw = NGF_CAllocate<NGF_Windows>(1, title, size);

	_windows.insert(pw);

    _currentWindow = pw;

	pw->Show(SW_NORMAL);


	return pw;
}

BOOL NGF_Application::CloseWindow(NGF_PWindows window) {

	window->Close();
	NGF_Free<NGF_Windows>(window);

	_windows.erase(window);
	return TRUE;
}


NGF_END