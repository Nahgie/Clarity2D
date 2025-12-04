module c2d.engine.game;

import c2d.engine.graphics;

using namespace c2d;

void GameManager::ASyncProcess()
{
    while (_threadState)
    {
        //InputMNGR->Update();
        //SceneMNGR->SceneASyncUpdate();
    }
}

void GameManager::GameProcess()
{
    auto timePoint = setTimer::now() + frameRate(SECONDS); //목표 시간
    auto prevTime = setTimer::now();                       //이전 시간
    auto currTime = setTimer::time_point();                //현재 시간

    while (_threadState)
    {
        currTime = setTimer::now();                                                       //현재 시간 측정
        _deltaTime = std::chrono::duration_cast<deltaTimer>(currTime - prevTime).count(); //델타 타임 계산
        prevTime = currTime;                                                              //이전 시간

        GFXInst()->RenderBegin();
        {
            //SceneMNGR->SceneUpdate();
            //SceneMNGR->SceneDraw();
        }
        GFXInst()->RenderEnd();

        while (timePoint >= setTimer::now())
        {
            //BusyWait 프레임 제어
        }
        timePoint += frameRate(SECONDS);
    }
}

float32 GameManager::GetDeltaTime() const noexcept
{
    return static_cast<float32>(_deltaTime);
}

float64 GameManager::GetHighDeltaTime() const noexcept
{
    return _deltaTime;
}

void GameManager::Init()
{
    GFXInst()->Init();
    //SceneMNGR->Init();

    //주 쓰레드 실행
    _aSyncUpdateThread = std::jthread(&GameManager::ASyncProcess, this);
    _gameUpdateThread = std::jthread(&GameManager::GameProcess, this);
}

void GameManager::GameQuit()
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