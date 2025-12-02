export module c2d.engine.game;

import c2d.engine.types;
import c2d.engine.singleton;
import c2d.launch_options;

import <chrono>;
import <thread>;

using namespace c2d;
using namespace c2d::options;

export namespace c2d
{
    class GameManager final : public Singleton<GameManager>
    {
    private:
        //chrono의 타이머를 using 문으로 축약
        using frameRate = std::chrono::duration<uint64, std::ratio<FPS_NUM, FRAME_RATE>>;
        using deltaTimer = std::chrono::duration<float64, std::milli>;
        using setTimer = std::chrono::high_resolution_clock;

    private:
        std::atomic_bool _threadState = true;

        std::jthread _aSyncUpdateThread;
        std::jthread _gameUpdateThread;

        afloat64 _deltaTime = 0.0;

    private:
        void ASyncProcess()
        {
            while (_threadState)
            {
                //InputMNGR->Update();
                //SceneMNGR->SceneASyncUpdate();
            }
        }

        void GameProcess()
        {
            auto timePoint = setTimer::now() + frameRate(SECONDS); //목표 시간
            auto prevTime = setTimer::now();                       //이전 시간
            auto currTime = setTimer::time_point();                //현재 시간

            while (_threadState)
            {
                currTime = setTimer::now();                                                       //현재 시간 측정
                _deltaTime = std::chrono::duration_cast<deltaTimer>(currTime - prevTime).count(); //델타 타임 계산
                prevTime = currTime;                                                              //이전 시간

                //GraphicsMNGR->RenderBegin();
                {
                    //SceneMNGR->SceneUpdate();
                    //SceneMNGR->SceneDraw();
                }
                //GraphicsMNGR->RenderEnd();

                while (timePoint >= setTimer::now())
                {
                    //BusyWait 프레임 제어
                }
                timePoint += frameRate(SECONDS);
            }
        }


    public:
        float32 GetDeltaTime() const noexcept { return static_cast<float32>(_deltaTime); }
        float64 GetHighDeltaTime() const noexcept { return _deltaTime; }

        void Init()
        {
            //GraphicsMNGR->Init();
            //SceneMNGR->Init();

            //주 쓰레드 실행
            _aSyncUpdateThread = std::jthread(&GameManager::ASyncProcess, this);
            _gameUpdateThread = std::jthread(&GameManager::GameProcess, this);
        }

        void GameQuit()
        {
            _threadState.store(false);

            _aSyncUpdateThread.request_stop();
            _gameUpdateThread.request_stop();

            if (_aSyncUpdateThread.joinable())
            {
                _aSyncUpdateThread.join();
            }

            if (_gameUpdateThread.joinable())
            {
                _gameUpdateThread.join();
            }
        }
    };
}

// GameManager 싱글톤 헬퍼 인라인 함수
export inline c2d::GameManager* Game() noexcept { return c2d::GameManager::GetInstance(); }