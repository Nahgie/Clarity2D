module c2d.engine.graphics;

import <d3d11.h>;
import <d3dcompiler.h>;
import <dxgi.h>;
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
        desc.BufferDesc.Width = Win32Inst()->GetWidth();
        desc.BufferDesc.Height = Win32Inst()->GetHeight();
        desc.BufferDesc.RefreshRate.Numerator = deviceMode.dmDisplayFrequency;
        desc.BufferDesc.RefreshRate.Denominator = 1;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        desc.SampleDesc.Count = 1;
        desc.SampleDesc.Quality = 0;

        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.BufferCount = 1;

        desc.OutputWindow = Win32Inst()->GetWindowHandle();
        desc.Windowed = true;
        desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    }

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
        _swChain.GetAddressOf(),
        _dev.GetAddressOf(),
        nullptr,
        _devContext.GetAddressOf()
    );
    assert(SUCCEEDED(hr));

    com_ptr<ID3D10Multithread> mt = nullptr;    //다이렉트X 멀티 쓰레드 동기화 작업 (DX10)
    _dev->QueryInterface<ID3D10Multithread>(mt.GetAddressOf());
    mt->SetMultithreadProtected(true);

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

    hr = _dev->CreateRenderTargetView(backBuff.Get(), nullptr, _rtv.GetAddressOf());
    assert(SUCCEEDED(hr));
}

void GraphicsManager::SetViewport()
{
    _viewport.TopLeftX = 0.f;
    _viewport.TopLeftY = 0.f;
    _viewport.Width = static_cast<float32>(Win32Inst()->GetWidth());
    _viewport.Height = static_cast<float32>(Win32Inst()->GetHeight());
    _viewport.MinDepth = 0.f;
    _viewport.MaxDepth = 1.f;
}

void GraphicsManager::Init()
{
    CreateDevSC();
    CreateRTV();
    SetViewport();
}

void GraphicsManager::SetRenderLimitMode(const eRenderLimitMode state) noexcept
{
    switch (state)
    {
    case eRenderLimitMode::UNLIMIT:
        _renderState = eRenderLimitMode::UNLIMIT;
        break;

    case eRenderLimitMode::V_SYNC:
        _renderState = eRenderLimitMode::V_SYNC;
        break;

    case eRenderLimitMode::SINGLE_BUFFER:
        _renderState = eRenderLimitMode::SINGLE_BUFFER;
        break;

    case eRenderLimitMode::DOUBLE_BUFFER:
        _renderState = eRenderLimitMode::DOUBLE_BUFFER;
        break;

    case eRenderLimitMode::TRIPLE_BUFFER:
        _renderState = eRenderLimitMode::TRIPLE_BUFFER;
        break;

    default:
        break;
    }
}

void GraphicsManager::RenderBegin()
{
    _devContext->OMSetRenderTargets(1, _rtv.GetAddressOf(), nullptr);
    _devContext->ClearRenderTargetView(_rtv.Get(), _defColor);
    _devContext->RSSetViewports(1, &_viewport);
}

void GraphicsManager::RenderEnd()
{
    HRESULT hr = _swChain->Present(static_cast<uint8>(_renderState), 0);
    assert(SUCCEEDED(hr));
}

const com_ptr<ID3D11Device>& GraphicsManager::GetDevice() const noexcept
{
    return _dev;
}

const com_ptr<ID3D11DeviceContext>& GraphicsManager::GetDeviceContext() const noexcept
{
    return _devContext;
}

const com_ptr<IDXGISwapChain>& GraphicsManager::GetSWChain() const noexcept
{
    return _swChain;
}

const com_ptr<IMFDXGIDeviceManager>& GraphicsManager::GetDXGI() const noexcept
{
    return _dxgiManager;
}