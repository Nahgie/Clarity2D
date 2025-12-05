export module c2d.engine.game;

import c2d.engine.types;
import c2d.engine.singleton;
import c2d.launch.options;
import std;

using namespace c2d;
using namespace c2d::engine_start_options;

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
        c2thread _asyncUpdateThread;
        c2thread _gameUpdateThread;

        afloat64 _deltaTime   = 0.0;
        abool    _threadState = true;

    private:
        void ASyncProcess();
        void GameProcess();

    public:
        float32 GetDeltaTime()     const noexcept { return static_cast<float32>(_deltaTime); }
        float64 GetHighDeltaTime() const noexcept { return _deltaTime; }

        void Init();
        void GameQuit();
    };
}

// GameManager 싱글톤 헬퍼 인라인 함수
export inline c2d::GameManager* GameInst() noexcept { return c2d::GameManager::GetInstance(); }