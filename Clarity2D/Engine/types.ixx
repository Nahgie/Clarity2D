/*
    Clarity2D에서 사용하는 자료형들을 정리합니다.
*/
export module c2d.engine.types;

import <wrl/client.h>;
import <SimpleMath.h>;
import <cstdint>;
import <stdfloat>;
import <string>;
import <atomic>;

export namespace c2d
{
    template<typename T>
    using com_ptr = Microsoft::WRL::ComPtr<T>;

    using uint8 = std::uint_fast8_t;
    using uint16 = std::uint_fast16_t;
    using uint32 = std::uint_fast32_t;
    using uint64 = std::uint_fast64_t;
    using uint128 = uint64;         // std::uint_fast128_t 미구현 [uint64와 동일]

    // atomic unsigned integer type
    using auint8 = std::atomic<uint8>;
    using auint16 = std::atomic<uint16>;
    using auint32 = std::atomic<uint32>;
    using auint64 = std::atomic<uint64>;

    using int8 = std::int_fast8_t;
    using int16 = std::int_fast16_t;
    using int32 = std::int_fast32_t;
    using int64 = std::int_fast64_t;
    using int128 = int64;           // std::int_fast128_t 미구현 [int64와 동일]

    // atomic signed integer type
    using aint8 = std::atomic<int8>;
    using aint16 = std::atomic<int16>;
    using aint32 = std::atomic<int32>;
    using aint64 = std::atomic<int64>;

    using float32 = float;
    using float64 = double;
    using float128 = long double;   // std::float128_t 미구현 [double과 동일한 64비트]

    // atomic float type
    using afloat32 = std::atomic<float32>;
    using afloat64 = std::atomic<float64>;
    using afloat128 = std::atomic<float128>;

    // 엔진 내부 텍스트 전용 UTF-8
    using string = std::string;
    using string_view = std::string_view;

    // Win32 & DX 전용 UTF-16
    using wstring = std::wstring;
    using wstring_view = std::wstring_view;

    export namespace options
    {
        using TEXT = LPCWSTR;
        using SCREEN_WIDTH = uint16;
        using SCREEN_HEIGHT = uint16;
        using MAX_FRAME_RATE = uint16;
    }

    export namespace math
    {
        using vec2 = DirectX::SimpleMath::Vector2;
        using vec3 = DirectX::SimpleMath::Vector3;
        using vec4 = DirectX::SimpleMath::Vector4;
        using color = DirectX::SimpleMath::Vector4;

        using matrix = DirectX::SimpleMath::Matrix;
        using quaternion = DirectX::SimpleMath::Quaternion;

        inline constexpr double pi = 3.141592653589793;
        inline constexpr double epsilon = 0.000001;
        inline constexpr double deg2rad = (pi / 180.0);
        inline constexpr double rad2deg = (180.0 / pi);
    }
}