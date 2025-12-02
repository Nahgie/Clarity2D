import c2d.engine.win32;
import c2d.launch_options;

import <Windows.h>;

using namespace c2d;

int WINAPI wWinMain
(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    Win32()->Init(nullptr, TITLE, WIDTH, HEIGHT);
    return 0;
}