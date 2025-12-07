module;
    #include "c2d_dx.h"
export module c2d.engine.scene;

import c2d.core.singleton;
import c2d.core.types;

export namespace c2d
{
    class SceneManager final : public Singleton<SceneManager>
    {

    };
}

// SceneManager 싱글톤 헬퍼 인라인 함수
export inline c2d::SceneManager* Scene() noexcept { return c2d::SceneManager::GetInstance(); }