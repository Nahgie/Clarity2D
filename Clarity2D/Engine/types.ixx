/*
    Clarity2D에서 사용하는 자료형들을 정리합니다.
*/
export module c2d.engine.types;

import <wrl/client.h>;
import <SimpleMath.h>;
import <cassert>;
import std;

export namespace c2d
{
    template<typename T>
    using com_ptr = Microsoft::WRL::ComPtr<T>;

    // atomic bool
    using abool = std::atomic<bool>;

    // unsigned integer type
    using uint8   = std::uint_fast8_t;
    using uint16  = std::uint_fast16_t;
    using uint32  = std::uint_fast32_t;
    using uint64  = std::uint_fast64_t;
    using uint128 = uint64;         // std::uint_fast128_t 미구현 [uint64와 동일]

    // atomic unsigned integer type
    using auint8  = std::atomic<uint8>;
    using auint16 = std::atomic<uint16>;
    using auint32 = std::atomic<uint32>;
    using auint64 = std::atomic<uint64>;

    // signed integer type
    using int8   = std::int_fast8_t;
    using int16  = std::int_fast16_t;
    using int32  = std::int_fast32_t;
    using int64  = std::int_fast64_t;
    using int128 = int64;           // std::int_fast128_t 미구현 [int64와 동일]

    // atomic signed integer type
    using aint8  = std::atomic<int8>;
    using aint16 = std::atomic<int16>;
    using aint32 = std::atomic<int32>;
    using aint64 = std::atomic<int64>;

    // floating point type
    using float32  = float;
    using float64  = double;
    using float128 = long double;   // std::float128_t 미구현 [double과 동일한 64비트]

    // atomic floating point type
    using afloat32  = std::atomic<float32>;
    using afloat64  = std::atomic<float64>;
    using afloat128 = std::atomic<float128>;

    // 엔진 내부 텍스트 전용 UTF-8
    using c2string      = std::string;
    using c2string_view = std::string_view;

    // Win32 & DX 전용 UTF-16
    using c2wstring      = std::wstring;
    using c2wstring_view = std::wstring_view;

    // C++20 joining thread [ C++11 thread는 사용하지 말 것 ]
    using c2thread = std::jthread;

    export namespace engine_start_options
    {
        using TEXT           = LPCWSTR;
        using SCREEN_WIDTH   = uint16;
        using SCREEN_HEIGHT  = uint16;
        using MAX_FRAME_RATE = uint16;
    }

    export namespace math
    {
        using vec2  = DirectX::SimpleMath::Vector2;
        using vec3  = DirectX::SimpleMath::Vector3;
        using vec4  = DirectX::SimpleMath::Vector4;
        using color = DirectX::SimpleMath::Vector4;

        using matrix     = DirectX::SimpleMath::Matrix;
        using quaternion = DirectX::SimpleMath::Quaternion;

        inline constexpr double pi      = 3.141592653589793;
        inline constexpr double epsilon = 0.000001;
        inline constexpr double deg2rad = (pi / 180.0);
        inline constexpr double rad2deg = (180.0 / pi);
    }

    export namespace rendering
    {
        enum class eRenderLimitMode : UINT8     //렌더링 싱크 조절법을 정의
        {
            UNLIMIT       = (0x00),
            V_SYNC        = (0x01),
            SINGLE_BUFFER = (0x02),
            DOUBLE_BUFFER = (0x03),
            TRIPLE_BUFFER = (0x04)
        };
    }

/*    export namespace windows
    {
        using AppHandle = HINSTANCE;
        using WinHandle = HWND;
        using MsgID     = UINT;
        using MsgWParam = WPARAM;
        using MsgLParam = LPARAM;
    }
*/
}