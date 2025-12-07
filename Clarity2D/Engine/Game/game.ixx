/*
* 게임 루프를 담당합니다.
* 싱글톤 형태이며 소스(*.cpp) 파일에서 사용할 수 있습니다.
* 
* 작성일 : 25.12.07
* [주의!] 순환 참조 문제가 발생할 수 있으니 모듈(*.ixx)에서 사용 금지
*/
module;
    #include "c2d_dx.h"
export module c2d.engine.game;

import c2d.core.types;
import c2d.core.singleton;
import c2d.launch.options;
import c2d.engine.input;

using namespace c2d;
using namespace c2d::engine_start_options;
using namespace DirectX;

export namespace c2d
{
    class GameManager final : public Singleton<GameManager>
    {
    private:
        //chrono의 타이머를 using 문으로 축약
        using frameRate  = std::chrono::duration<uint64, std::ratio<FPS_NUM, FRAME_RATE>>;
        using deltaTimer = std::chrono::duration<float64, std::milli>;
        using setTimer   = std::chrono::high_resolution_clock;

    private:
        c2thread _gameUpdateThread;

        float64 _deltaTime   = 0.0;
        bool    _isRunning = true;

    private:
        void GameUpdate();

    public:
        float32 GetDeltaTime()     const noexcept { return static_cast<float32>(_deltaTime); }
        float64 GetHighDeltaTime() const noexcept { return _deltaTime; }

        void Init();
        void GameQuit();
    };
}

// GameManager 싱글톤 헬퍼 인라인 함수
export inline c2d::GameManager* Game() noexcept { return c2d::GameManager::GetInstance(); }