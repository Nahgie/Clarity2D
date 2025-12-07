module;
    #include "c2d_dx.h"
module c2d.engine.game;

import c2d.engine.graphics;
import c2d.engine.input;
import c2d.engine.win32;

using namespace c2d;

void GameManager::GameUpdate()
{
    auto timePoint = setTimer::now() + frameRate(SECONDS); //목표 시간
    auto prevTime  = setTimer::now();                      //이전 시간
    auto currTime  = setTimer::time_point();               //현재 시간

    while (_isRunning)
    {
        Input()->Update();     // 인풋 매니저 업데이트

        currTime   = setTimer::now();                                             //현재 시간 측정
        _deltaTime = std::chrono::duration<float64>(currTime - prevTime).count(); //델타 타임 계산
        prevTime   = currTime;                                                    //이전 시간

        Gfx()->RenderBegin();
        {
            //SceneMNGR->SceneUpdate();
            //SceneMNGR->SceneDraw();
        }
        Gfx()->RenderEnd();

        std::println("deltatime : {}", GetHighDeltaTime());
        while (timePoint >= setTimer::now())
        {
            //BusyWait 프레임 제어
        }
        timePoint += frameRate(SECONDS);
    }
}

void GameManager::Init()
{
    Gfx()->Init();
    Input()->Init(Win32()->GetWindowHandle());
    //SceneMNGR->Init();

    // 게임스레드 실행
    _gameUpdateThread  = c2thread(&GameManager::GameUpdate, this);
}

void GameManager::GameQuit()
{
    _isRunning = false;

    if (_gameUpdateThread.joinable())
    {
        _gameUpdateThread.join();
    }
}