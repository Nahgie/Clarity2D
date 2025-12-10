module;
    #include "c2d_dx.h"
export module c2d.core.messenger;

import c2d.core.types;
import c2d.engine.win32;

export namespace c2d
{
    void ErrorMsg
    (
        const c2wstring& msg,
        const c2wstring& title = L"Clarity2D Fatal Error",
        UINT msgFlag = MB_OK | MB_ICONERROR
    )
    {
        MessageBoxW
        (
            Win32()->GetWindowHandle(),
            msg.c_str(),
            title.c_str(),
            msgFlag
        );
    }

    void WarningMsg
    (
        const c2wstring& msg,
        const c2wstring& title = L"Clarity2D Warning",
        UINT msgFlag = MB_OK | MB_ICONEXCLAMATION
    )
    {
        MessageBoxW
        (
            Win32()->GetWindowHandle(),
            msg.c_str(),
            title.c_str(),
            msgFlag
        );
    }

    void InformationMsg
    (
        const c2wstring& msg,
        const c2wstring& title = L"Clarity2D Information",
        UINT msgFlag = MB_OK | MB_ICONINFORMATION
    )
    {
        MessageBoxW
        (
            Win32()->GetWindowHandle(),
            msg.c_str(),
            title.c_str(),
            msgFlag
        );
    }
}