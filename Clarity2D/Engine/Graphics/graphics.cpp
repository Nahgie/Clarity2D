module c2d.engine.graphics;

import <d3d11_4.h>;
import <d3dcompiler.h>;
import <dxgi1_6.h>;
import <mfmediaengine.h>;
import <mfapi.h>;
import <mfidl.h>;
import <mferror.h>;
import <cassert>;
import <Windows.h>;
import c2d.engine.win32;

using namespace c2d;

void GraphicsManager::CreateDevSC()
{
    //WinGDI를 사용해 사용자의 모니터 정보를 불러옵니다.
    DEVMODEW deviceMode{};
    {
        deviceMode.dmSize = sizeof(DEVMODEW);
        EnumDisplaySettingsW(nullptr, ENUM_CURRENT_SETTINGS, &deviceMode);
    }

    DXGI_SWAP_CHAIN_DESC desc{};
    {
        desc.BufferDesc.Width                   = Win32Inst()->GetWidth();
        desc.BufferDesc.Height                  = Win32Inst()->GetHeight();
        desc.BufferDesc.RefreshRate.Numerator   = deviceMode.dmDisplayFrequency;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.SampleDesc.Count                   = 1;
        desc.SampleDesc.Quality                 = 0;
        desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount                        = 1;
        desc.OutputWindow                       = Win32Inst()->GetWindowHandle();
        desc.Windowed                           = true;
        desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
    }

    // 기본 인터페이스 생성
    com_ptr<ID3D11Device>        baseDev;
    com_ptr<ID3D11DeviceContext> baseCtx;
    com_ptr<IDXGISwapChain>      baseSwap;

    HRESULT hr = D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        &desc,
        baseSwap.GetAddressOf(),
        baseDev.GetAddressOf(),
        nullptr,
        baseCtx.GetAddressOf()
    );
    assert(SUCCEEDED(hr));

    // 최신 인터페이스로 업캐스트
    hr = baseDev.As(&_dev);         // ID3D11Device5
    assert(SUCCEEDED(hr));

    hr = baseCtx.As(&_devContext);  // ID3D11DeviceContext4
    assert(SUCCEEDED(hr));

    hr = baseSwap.As(&_swChain);    // IDXGISwapChain4
    assert(SUCCEEDED(hr));

    // 멀티쓰레드 보호
    hr = _dev.As(&_multithread);
    assert(SUCCEEDED(hr));
    _multithread->SetMultithreadProtected(true);

    hr = MFCreateDXGIDeviceManager(&_dxgiResetToken, _dxgiManager.GetAddressOf());
    assert(SUCCEEDED(hr));

    hr = _dxgiManager->ResetDevice(_dev.Get(), _dxgiResetToken);
    assert(SUCCEEDED(hr));
}

void GraphicsManager::CreateRTV()
{
    com_ptr<ID3D11Texture2D> backBuff = nullptr;

    HRESULT hr = _swChain->GetBuffer
    (
        0,
        __uuidof(ID3D11Texture2D),
        reinterpret_cast<void**>(backBuff.GetAddressOf())
    );
    assert(SUCCEEDED(hr));

    hr = _dev->CreateRenderTargetView1
    (
        backBuff.Get(),
        nullptr,
        _rtv.GetAddressOf()
    );
    assert(SUCCEEDED(hr));
}

void GraphicsManager::SetViewport()
{
    _viewport.TopLeftX = 0.f;
    _viewport.TopLeftY = 0.f;
    _viewport.Width    = static_cast<float32>(Win32Inst()->GetWidth());
    _viewport.Height   = static_cast<float32>(Win32Inst()->GetHeight());
    _viewport.MinDepth = 0.f;
    _viewport.MaxDepth = 1.f;
}

void GraphicsManager::Init()
{
    CreateDevSC();
    CreateRTV();
    SetViewport();
    SetRenderLimitMode(eRenderLimitMode::UNLIMIT);
}

void GraphicsManager::RenderBegin()
{
    ID3D11RenderTargetView* const rtv = _rtv.Get(); // ID3D11RenderTargetView1 업캐스트

    _devContext->OMSetRenderTargets(1, &rtv, nullptr);
    _devContext->ClearRenderTargetView(rtv, _defColor);
    _devContext->RSSetViewports(1, &_viewport);
}

void GraphicsManager::RenderEnd()
{
    HRESULT hr = _swChain->Present(static_cast<uint8>(_renderState), 0);
    assert(SUCCEEDED(hr));
}