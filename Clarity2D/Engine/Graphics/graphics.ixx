/*
* DirectX API를 사용해 그래픽 처리를 담당합니다.
* 싱글톤 형태이며 소스(*.cpp) 파일에서 사용할 수 있습니다.
* 
* 작성일 : 25.12.07
* [주의!] 순환 참조 문제가 발생할 수 있으니 모듈(*.ixx)에서 사용 금지
*/
module;
    #include "c2d_dx.h"
export module c2d.engine.graphics;

import c2d.core.singleton;
import c2d.core.types;

using namespace c2d;
using namespace c2d::rendering;

export namespace c2d
{
    class GraphicsManager final : public Singleton<GraphicsManager>
    {
    private:
        com_ptr<ID3D11Device5>           _dev            = nullptr;
        com_ptr<ID3D11DeviceContext4>    _devContext     = nullptr;
        com_ptr<IDXGISwapChain4>         _swChain        = nullptr;
        com_ptr<ID3D11RenderTargetView1> _rtv            = nullptr;
        com_ptr<IMFDXGIDeviceManager>   _dxgiManager     = nullptr;
        com_ptr<ID3D11Multithread>      _multithread     = nullptr;

        //뷰포트 정의
        uint32                          _dxgiResetToken = 0;
        D3D11_VIEWPORT                  _viewport;
        float32                         _defColor[4]{};

        //렌더링 싱크
        eRenderLimitMode                _renderState;

    private:
        void CreateDevSC();
        void CreateRTV();
        void SetViewport();

    public:
        void Init();
        void SetRenderLimitMode(const eRenderLimitMode state) noexcept { _renderState = state; }
        void RenderBegin();
        void RenderEnd();

        const com_ptr<ID3D11Device5>&         GetDevice()        const noexcept { return _dev; }
        const com_ptr<ID3D11DeviceContext4>&  GetDeviceContext() const noexcept { return _devContext; }
        const com_ptr<IDXGISwapChain4>&       GetSWChain()       const noexcept { return _swChain; }
        const com_ptr<IMFDXGIDeviceManager>&  GetDXGI()          const noexcept { return _dxgiManager; }
        const com_ptr<ID3D11Multithread>&     GetDXMultithread() const noexcept { return _multithread; }
    };
}

// GraphicsManager 싱글톤 헬퍼 인라인 함수
export inline c2d::GraphicsManager* Gfx() noexcept { return c2d::GraphicsManager::GetInstance(); }