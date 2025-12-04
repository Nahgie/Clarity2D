/*
    프로그램의 런칭 옵션을 설정합니다.
*/
export module c2d.launch.options;

import c2d.engine.types;

using namespace c2d::engine_start_options;

export namespace c2d
{
    inline constexpr TEXT           TITLE        = L"Clarity2D [Dev By Nahgie]";
    inline constexpr SCREEN_WIDTH   WIDTH        = 1280;
    inline constexpr SCREEN_HEIGHT  HEIGHT       = 720;
    inline constexpr MAX_FRAME_RATE FRAME_RATE   = 120;

    //GameManager에서 사용하는 상수입니다.
    inline constexpr uint8 SECONDS { 0x01 };
    inline constexpr uint8 FPS_NUM { 0x01 };
}