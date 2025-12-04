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

        void SetupWindow();
        void ReleaseWindow();

    public:
        HWND GetWindowHandle() const noexcept;
        int32 GetWidth() const noexcept;
        int32 GetHeight() const noexcept;

        void Init(HINSTANCE hInstance, wstring_view title, int32 width, int32 height);
    };
}

// Win32Manager 싱글톤 헬퍼 인라인 함수
export c2d::Win32Manager* Win32Inst() noexcept { return c2d::Win32Manager::GetInstance(); }