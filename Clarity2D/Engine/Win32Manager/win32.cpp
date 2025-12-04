module c2d.engine.win32;

import <Windows.h>;
import <cassert>;

import c2d.engine.game;

using namespace c2d;

void Win32Manager::SetupWindow()
{
    WNDCLASSEXW wc{};
    {
        wc.cbSize = sizeof(WNDCLASSEXW);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.lpfnWndProc = WndProc;
        wc.hInstance = _hInstance;
        wc.lpszClassName = _title.c_str();
    }

    HRESULT hr = RegisterClassExW(&wc);
    assert(SUCCEEDED(hr));

    //윈도우 사이즈를 계산합니다.
    RECT contentSize{ 0, 0, _width, _height };
    AdjustWindowRectEx(&contentSize, WS_OVERLAPPEDWINDOW, false, WS_EX_APPWINDOW);

    int32 clientWidth = (contentSize.right - contentSize.left);
    int32 clientHeight = (contentSize.bottom - contentSize.top);

    //윈도우 생성
    _hWnd = CreateWindowExW
    (
        WS_EX_APPWINDOW,
        _title.c_str(),
        _title.c_str(),
        WS_OVERLAPPEDWINDOW,
        (GetSystemMetrics(SM_CXSCREEN) / 2) - (clientWidth / 2),
        (GetSystemMetrics(SM_CYSCREEN) / 2) - (clientHeight / 2),
        clientWidth,
        clientHeight,
        nullptr,
        nullptr,
        _hInstance,
        nullptr
    );

    if (_hWnd == nullptr) //윈도우 생성 실패시 메시지 박스를 출력
    {
        MessageBoxW(nullptr, L"Window Creation Failed!", L"FATAL ERROR", MB_ICONERROR);
        std::exit(-1);
    }

    ShowWindow(_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(_hWnd);
}

void Win32Manager::ReleaseWindow()
{
    DestroyWindow(_hWnd);
    UnregisterClass(_title.c_str(), _hInstance);
}

void Win32Manager::Init
(
    HINSTANCE hInstance,
    wstring_view title,
    int32 width,
    int32 height
)
{
    _hInstance = hInstance;
    _title = title;
    _width = width;
    _height = height;

    //COM객체를 멀티 쓰레드 환경으로 초기화 합니다.
    HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
    assert(SUCCEEDED(hr));

    SetupWindow();

    GameInst()->Init();

    MSG msg{};

    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    CoUninitialize();
    ReleaseWindow();

    GameInst()->GameQuit();
}

HWND Win32Manager::GetWindowHandle() const noexcept
{
    return _hWnd;
}

int32 Win32Manager::GetWidth() const noexcept
{
    return _width;
}

int32 Win32Manager::GetHeight() const noexcept
{
    return _height;
}