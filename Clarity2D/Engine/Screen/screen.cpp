module;
    #include "c2d_dx.h"
module c2d.engine.screen;

import c2d.engine.win32;

using namespace c2d;

vec2 ScreenManager::ToRelative(const vec2& xy) noexcept
{
    return { ToRelativeX(xy.x), ToRelativeY(xy.y) };
}

float32 ScreenManager::ToRelativeX(const float32 x) noexcept
{
    return (x / _screenSize.x);
}

float32 ScreenManager::ToRelativeY(const float32 y) noexcept
{
    return (y / _screenSize.y);
}

vec2 ScreenManager::ToAbsolute(const vec2& xy) noexcept
{
    return { ToAbsoluteX(xy.x), ToAbsoluteY(xy.y) };
}

float32 ScreenManager::ToAbsoluteX(const float32 x) noexcept
{
    return static_cast<float32>(x * Win32()->GetWidth());
}

float32 ScreenManager::ToAbsoluteY(const float32 y) noexcept
{
    return static_cast<float32>(y * Win32()->GetHeight());
}

vec2 ScreenManager::ToScreen(const vec2& xy) noexcept
{
    return ToRelative(ToAbsolute(xy));
}

float32 ScreenManager::ToScaleX(const float32 x) noexcept
{
    return ToAbsoluteX(ToRelativeX(x));
}

float32 ScreenManager::ToScaleY(const float32 y) noexcept
{
    return ToAbsoluteY(ToRelativeY(y));
}