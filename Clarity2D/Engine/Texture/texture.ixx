module;
    #include "c2d_dx.h"
export module c2d.engine.texture;

import c2d.core.singleton;
import c2d.core.types;
import c2d.engine.graphics;

using namespace c2d::rendering;

export namespace c2d
{
    class TextureManager final : public Singleton<TextureManager>
    {
    private:
        std::unordered_map <c2wstring, c2texture_ptr> _cache;

    public:
        bool IsInitialized() const noexcept
        {
            return Gfx()->GetDevice().Get() != nullptr && Gfx()->GetDeviceContext().Get() != nullptr;
        }

        c2texture_ptr Load(const c2wstring& path)
        {
            if (!IsInitialized())
            {
                return nullptr;
            }

            if (auto it = _cache.find(path); it != _cache.end())
            {
                return it->second;
            }

            com_ptr<ID3D11ShaderResourceView> srv;
            HRESULT hr = DirectX::CreateWICTextureFromFile(
                Gfx()->GetDevice().Get(),
                Gfx()->GetDeviceContext().Get(),
                path.c_str(),
                nullptr,
                srv.GetAddressOf()
            );

            if (FAILED(hr))
            {
                return nullptr;
            }

            com_ptr<ID3D11Resource> res;
            srv->GetResource(res.GetAddressOf());

            com_ptr<ID3D11Texture2D> tex2D;
            D3D11_TEXTURE2D_DESC desc{};

            if (SUCCEEDED(res.As(&tex2D)))
            {
                tex2D->GetDesc(&desc);
            }

            auto tex = std::make_shared<Texture>();
            tex->srv = std::move(srv);
            tex->size = vec2{ static_cast<float32>(desc.Width), static_cast<float32>(desc.Height) };

            _cache.emplace(path, tex);
            return tex;
        }

        c2texture_ptr Get(const c2wstring& path) const
        {
            if (auto it = _cache.find(path); it != _cache.end())
            {
                return it->second;
            }
            return nullptr;
        }

        void Clear() noexcept
        {
            _cache.clear();
        }
    };
}

// TextureManager 싱글톤 헬퍼 인라인 함수
export inline c2d::TextureManager* Texture2D() noexcept { return c2d::TextureManager::GetInstance(); }