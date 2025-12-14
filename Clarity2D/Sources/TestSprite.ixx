module;
#include "c2d_dx.h"
export module TestSprite;

import c2d.core.types;
import c2d.system.game_object;
import c2d.system.component.painter;

using namespace c2d;
using namespace c2d::math;

export namespace TC2D
{
    class TestSprite final : public GameObject
    {
    private:
        Painter   _painter{};
        c2wstring _path{};

    public:
        TestSprite(const c2wstring& texturePath, vec2 pos = { 0.f, 0.f })
            : _path(texturePath)
        {
            _painter.position = pos;
        }

        void Create() override
        {
            const bool ok = _painter.SetTexture(_path);
            if (!ok)
            {
                std::wcout << L"[TestSprite] Failed to load texture: " << _path << L"\n";
            }
        }

        void Update(float32 deltatime) override
        {

        }

        void Render() override
        {
            _painter.Render();
        }
    };
}