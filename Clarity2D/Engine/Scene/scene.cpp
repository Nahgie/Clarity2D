module;
    #include "c2d_dx.h"
module c2d.engine.scene;

import c2d.engine.game;
import c2d.engine.win32;

using namespace c2d;

void SceneManager::Init()
{
    _sceneIt = _scenes.end();
}

void SceneManager::LoadScene(const c2wstring& name)
{
    auto it = _scenes.find(name);

    if (it == _scenes.end())
    {
        ShowError(L"Failed to load scene");
        return;
    }

    if (_sceneIt != _scenes.end() && _sceneIt->second)
    {
        _sceneIt->second->Hide();
    }

    _sceneIt = it;

    if (_sceneIt->second)
    {
        _sceneIt->second->Show();
    }
}

void SceneManager::DeleteScene(const c2wstring& name)
{
    bool deleteFlag = _scenes.contains(name);

    if (!deleteFlag)
    {
        ShowError(L"Failed to delete scene");
        return;
    }

    if (_sceneIt != _scenes.end() && _sceneIt->first == name)
    {
        _sceneIt = _scenes.end();   // 현재 사용중인 씬이라면 무효화
    }

    _scenes.erase(name);
}

void SceneManager::Update()
{
    if (_sceneIt == _scenes.end() || !_sceneIt->second)
    {
        return;
    }

    _sceneIt->second->Update(Game()->GetDeltaTime());
}

void SceneManager::Draw()
{
    if (_sceneIt == _scenes.end() || !_sceneIt->second)
    {
        return;
    }

    _sceneIt->second->Draw();
}