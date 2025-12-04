export module c2d.engine.graphics;

import <d3d11.h>;
import <d3dcompiler.h>;
import <dxgi.h>;
import <mfmediaengine.h>;
import <mfapi.h>;
import <mfidl.h>;
import <mferror.h>;
import <cassert>;
import <Windows.h>;

import c2d.engine.singleton;
import c2d.engine.types;

using namespace c2d;
using namespace c2d::rendering;

export namespace c2d
{
    class GraphicsManager final : public Singleton<GraphicsManager>
    {
    private:

        com_ptr<ID3D11Device> _dev = nullptr;
        com_ptr<ID3D11DeviceContext> _devContext = nullptr;
        com_ptr<IDXGISwapChain> _swChain = nullptr;
        com_ptr<ID3D11RenderTargetView> _rtv = nullptr;
        com_ptr<IMFDXGIDeviceManager> _dxgiManager = nullptr;

        //렌더링 싱크
        eRenderLimitMode _renderState = eRenderLimitMode::UNLIMIT;

        //뷰포트 정의
        uint32 _dxgiResetToken = 0;
        D3D11_VIEWPORT _viewport;
        float32 _defColor[4]{};

    private:
        void CreateDevSC();
        void CreateRTV();
        void SetViewport();

    public:
        void Init();
        void SetRenderLimitMode(const eRenderLimitMode state) noexcept;
        void RenderBegin();
        void RenderEnd();

        const com_ptr<ID3D11Device>& GetDevice() const noexcept;
        const com_ptr<ID3D11DeviceContext>& GetDeviceContext() const noexcept;
        const com_ptr<IDXGISwapChain>& GetSWChain() const noexcept;
        const com_ptr<IMFDXGIDeviceManager>& GetDXGI() const noexcept;
    };
}

// GraphicsManager 싱글톤 헬퍼 인라인 함수
export c2d::GraphicsManager* GFXInst() noexcept { return c2d::GraphicsManager::GetInstance(); }