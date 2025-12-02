/*
    Win32 API를 사용해 윈도우를 생성합니다.
*/
export module c2d.engine.win32;

import c2d.engine.game;
import c2d.engine.singleton;
import c2d.engine.types;

import <Windows.h>;
import <cassert>;

export namespace c2d
{
    class Win32Manager final : public Singleton<Win32Manager>
    {
    private:
        HINSTANCE _hInstance = nullptr;
        HWND _hWnd = nullptr;

        wstring _title;
        int32 _width = 0;
        int32 _height = 0;

    private:
        static LRESULT WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_CLOSE:
            case WM_DESTROY:

                WIN32::PostQuitMessage(0);
                break;

            default:
                break;
            }
            return WIN32::DefWindowProc(handle, message, wParam, lParam);
        }

        void SetupWindow()
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

            HRESULT hr = WIN32::RegisterClassExW(&wc);
            assert(SUCCEEDED(hr));

            //윈도우 사이즈를 계산합니다.
            RECT contentSize{ 0, 0, _width, _height };
            WIN32::AdjustWindowRectEx(&contentSize, WS_OVERLAPPEDWINDOW, false, WS_EX_APPWINDOW);

            int32 clientWidth = (contentSize.right - contentSize.left);
            int32 clientHeight = (contentSize.bottom - contentSize.top);

            //윈도우 생성
            _hWnd = WIN32::CreateWindowExW
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
                WIN32::MessageBoxW(nullptr, L"Window Creation Failed!", L"FATAL ERROR", MB_ICONERROR);
                std::exit(-1);
            }

            WIN32::ShowWindow(_hWnd, SW_SHOWDEFAULT);
            WIN32::UpdateWindow(_hWnd);
        }

        void ReleaseWindow()
        {
            WIN32::DestroyWindow(_hWnd);
            WIN32::UnregisterClass(_title.c_str(), _hInstance);
        }

    public:

        HWND GetWindowHandle() const noexcept { return _hWnd; }
        int32 GetWidth() const noexcept { return _width; }
        int32 GetHeight() const noexcept { return _height; }

        void Init
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
            HRESULT hr = WIN32::CoInitializeEx(nullptr, COINITBASE_MULTITHREADED | COINIT_DISABLE_OLE1DDE);
            assert(SUCCEEDED(hr));

            SetupWindow();

            Game()->Init();

            MSG msg{};

            while (WIN32::GetMessageW(&msg, nullptr, 0, 0))
            {
                WIN32::TranslateMessage(&msg);
                WIN32::DispatchMessageW(&msg);
            }

            WIN32::CoUninitialize();
            ReleaseWindow();

            Game()->GameQuit();
        }
    };
}

// Win32Manager 싱글톤 헬퍼 인라인 함수
export inline c2d::Win32Manager* Win32() noexcept { return c2d::Win32Manager::GetInstance(); }