/*
    Win32 API를 사용해 윈도우를 생성합니다.
*/
export module c2d.engine.win32;

import <Windows.h>;
import c2d.engine.singleton;
import c2d.engine.types;

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
            case WM_CLOSE:
            case WM_DESTROY:

                PostQuitMessage(0);
                break;

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
export inline c2d::Win32Manager* Win32Inst() noexcept { return c2d::Win32Manager::GetInstance(); }