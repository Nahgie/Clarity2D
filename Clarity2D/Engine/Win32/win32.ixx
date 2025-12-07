/*
* Win32 API를 사용해 윈도우를 생성합니다.
* 싱글톤 형태이며 소스(*.cpp) 파일에서 사용할 수 있습니다.
* 
* 작성일 : 25.12.07
* 
* [주의!] 순환 참조 문제가 발생할 수 있으니 모듈(*.ixx)에서 사용 금지
*/
module;
    #include "c2d_dx.h"
export module c2d.engine.win32;

import c2d.core.singleton;
import c2d.core.types;

using namespace DirectX;

export namespace c2d
{
    class Win32Manager final : public Singleton<Win32Manager>
    {
    private:
        HINSTANCE _hInstance = nullptr;
        HWND      _hWnd      = nullptr;

        c2wstring _title;
        int32     _width     = 0;
        int32     _height    = 0;

    private:
        static LRESULT WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
        {
            switch (message)
            {
            case WM_ACTIVATEAPP:
                Keyboard::ProcessMessage(message, wParam, lParam);
                Mouse::ProcessMessage(message, wParam, lParam);
                break;

            case WM_KEYDOWN:
            case WM_KEYUP:
            case WM_SYSKEYDOWN:
            case WM_SYSKEYUP:
                Keyboard::ProcessMessage(message, wParam, lParam);
                break;

            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_MBUTTONDOWN:
            case WM_MBUTTONUP:
            case WM_MOUSEWHEEL:
            case WM_MOUSEHWHEEL:
                Mouse::ProcessMessage(message, wParam, lParam);
                break;

            case WM_CLOSE:
                DestroyWindow(handle);
                return 0;

            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            default:
                break;
            }
            return DefWindowProc(handle, message, wParam, lParam);
        }

        void SetupWindow();
        void ReleaseWindow();

    public:
        HWND  GetWindowHandle() const noexcept { return _hWnd; }
        int32 GetWidth()        const noexcept { return _width; }
        int32 GetHeight()       const noexcept { return _height; }

        void Init(HINSTANCE hInstance, c2wstring_view title, int32 width, int32 height);
    };
}

// Win32Manager 싱글톤 헬퍼 인라인 함수
export inline c2d::Win32Manager* Win32() noexcept { return c2d::Win32Manager::GetInstance(); }