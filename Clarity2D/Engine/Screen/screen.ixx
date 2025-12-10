module;
    #include "c2d_dx.h"
export module c2d.engine.screen;

import c2d.core.singleton;
import c2d.core.types;

using namespace c2d::math;

export namespace c2d
{
    class ScreenManager final : public Singleton<ScreenManager>
    {
    private:
        vec2 _screenSize{ 1280.f, 720.f };

    public:
        const vec2& GetTargetSize()           const noexcept { return _screenSize; }
        void        SetTargetSize(const vec2& size) noexcept { _screenSize = size; }

        float32 GetTargetX()                  const noexcept { return _screenSize.x; }
        void    SetTargetX(const float32 x)         noexcept { _screenSize.x = x; }

        float32 GetTargetY()                  const noexcept { return _screenSize.y; }
        void    SetTargetY(const float32 y)         noexcept { _screenSize.y = y; }

        vec2    ToRelative(const vec2& xy)          noexcept;
        float32 ToRelativeX(const float32 x)        noexcept;
        float32 ToRelativeY(const float32 y)        noexcept;

        vec2    ToAbsolute(const vec2& xy)          noexcept;
        float32 ToAbsoluteX(const float32 x)        noexcept;
        float32 ToAbsoluteY(const float32 y)        noexcept;

        vec2    ToScreen(const vec2& xy)            noexcept;
        float32 ToScaleX(const float32 x)           noexcept;
        float32 ToScaleY(const float32 y)           noexcept;
    };
}

// ScreenManager 싱글톤 헬퍼 인라인 함수
export inline c2d::ScreenManager* Screen() noexcept { return c2d::ScreenManager::GetInstance(); }