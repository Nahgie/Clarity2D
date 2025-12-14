module;
    #include "c2d_dx.h"
export module c2d.system.component.painter;

import c2d.core.types;
import c2d.system.game_object;
import c2d.engine.texture;
import c2d.engine.graphics;

using namespace c2d;
using namespace c2d::math;
using namespace c2d::rendering;

export namespace c2d
{
    class Painter final
    {
    private:
        c2texture_ptr _tex{};
        RECT          _srcRect{ 0, 0, 0, 0 };
        vec2          _origin{ 0.f, 0.f };

    public:
        vec2  position{ 0.f, 0.f };
        vec2  scale{ 1.f, 1.f };
        float32 rotation = 0.f;
        float32 depth = 0.f;
        DirectX::SpriteEffects flip = DirectX::SpriteEffects_None;

        color tint{ 1.f, 1.f, 1.f, 1.f };

        bool SetTexture(const c2wstring& path)
        {
            _tex = Texture2D()->Load(path);
            if (!_tex || !_tex->srv)
                return false;

            _srcRect.left = 0;
            _srcRect.top = 0;
            _srcRect.right = static_cast<uint32>(_tex->size.x);
            _srcRect.bottom = static_cast<uint32>(_tex->size.y);

            _origin = vec2{ _tex->size.x * 0.5f, _tex->size.y * 0.5f };
            return true;
        }

        void Render() const noexcept
        {
            if (!_tex || !_tex->srv)
            {
                return;
            }

            auto sb = Gfx()->GetSpriteBatch();
            if (!sb)
            {
                return;
            }

            sb->Draw(
                _tex->srv.Get(),
                position,
                &_srcRect,
                tint,
                rotation,
                _origin,
                scale,
                flip,
                depth
            );
        }
    };
}