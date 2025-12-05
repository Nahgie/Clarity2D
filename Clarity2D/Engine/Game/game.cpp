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
    auto prevTime  = setTimer::now();                      //이전 시간
    auto currTime  = setTimer::time_point();               //현재 시간

    while (_threadState)
    {
        currTime   = setTimer::now();                                                     //현재 시간 측정
        _deltaTime = std::chrono::duration_cast<deltaTimer>(currTime - prevTime).count(); //델타 타임 계산
        prevTime   = currTime;                                                            //이전 시간

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

void GameManager::Init()
{
    GFXInst()->Init();
    //SceneMNGR->Init();

    //주 쓰레드 실행
    _asyncUpdateThread = std::jthread(&GameManager::ASyncProcess, this);
    _gameUpdateThread  = std::jthread(&GameManager::GameProcess, this);
}

void GameManager::GameQuit()
{
    _threadState = false;

    _asyncUpdateThread.request_stop();
    _gameUpdateThread.request_stop();

    if (_asyncUpdateThread.joinable())
    {
        _asyncUpdateThread.join();
    }

    if (_gameUpdateThread.joinable())
    {
        _gameUpdateThread.join();
    }
}