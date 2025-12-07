#pragma once
/*
* 레거시 형태의 라이브러리(헤더)를 관리합니다.
* 라이브러리의 종속성을 띠는 매크로는 작성할 수 있지만
* 관련 없는 임의의 매크로 작성은 금지합니다.
* 
* 작성일 : 25.12.07
*/
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

// Windows
#include <Windows.h>
#include <windowsx.h>
#include <Shlwapi.h>
#include <wrl.h>

// Windows Media Foundation
#include <mfmediaengine.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>

// DirectX
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <dxgi1_6.h>

// DirectX Input
#include "Keyboard.h"
#include "Mouse.h"
#include "GamePad.h"

// DirectX Audio
#include "Audio.h"

// DirectX Graphics
#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Model.h"
#include "PostProcess.h"
#include "VertexTypes.h"

// DirectX Graphic Utility
#include "PrimitiveBatch.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"

// DirectX Texture Loader
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"

// DirectX Misc Utility
#include "ScreenGrab.h"
#include "SimpleMath.h"