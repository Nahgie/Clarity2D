import std.compat;
#include <Windows.h>

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        FillRect(hdc, &ps.rcPaint,
            static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));

        EndPaint(hWnd, &ps);
        return 0;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

// 엔트리 포인트 (유니코드 기준)
int WINAPI wWinMain(HINSTANCE hInstance,
    HINSTANCE /*hPrevInstance*/,
    PWSTR     /*lpCmdLine*/,
    int       nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Clarity2D Test";

    // 윈도우 클래스 등록
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClassExW(&wc))
        return -1;

    // 윈도우 생성
    HWND hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Pure Win32 Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    );

    if (!hWnd)
        return -1;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return static_cast<INT32>(msg.wParam);
}