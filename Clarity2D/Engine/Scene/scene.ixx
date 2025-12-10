module;
    #include "c2d_dx.h"
export module c2d.engine.scene;

import c2d.core.singleton;
import c2d.core.types;
import c2d.system.scene_object;
import c2d.core.messenger;

export namespace c2d
{
    class SceneManager final : public Singleton<SceneManager>
    {
    private:
        std::unordered_map<c2wstring, std::unique_ptr<SceneObject>>           _scenes;
        std::unordered_map<c2wstring, std::unique_ptr<SceneObject>>::iterator _sceneIt;

    public:
        template<typename T, typename... Args>
        T* AddScene(const c2wstring& name, Args&&... args);

        void LoadScene(const c2wstring& name);
        void DeleteScene(const c2wstring& name);

        void Init();
        void Update();
        void Draw();
    };
}

// SceneManager 싱글톤 헬퍼 인라인 함수
export inline c2d::SceneManager* Scene() noexcept { return c2d::SceneManager::GetInstance(); }

// 템플릿 함수 모음
export namespace c2d
{
    template <typename T, typename... Args>
    T* SceneManager::AddScene(const c2wstring& name, Args&&... args)
    {
        static_assert(std::is_base_of_v<SceneObject, T>, "T must be derived from SceneObject");

        auto [it, inserted] =
            _scenes.emplace(
                name,
                std::make_unique<T>(std::forward<Args>(args)...));

        if (!inserted)
        {
            ShowError("Failed to add scene");
        }
        return static_cast<T*>(it->second.get());
    }

    template <typename T>
    struct SceneRegister            // 씬 등록 헬퍼
    {
        explicit SceneRegister(const c2wstring& name)
        {
            static_assert(std::is_base_of_v<SceneObject, T>, "T must be derived from SceneObject");
            Scene()->AddScene<T>(name);
        }

        // 복사 / 이동 금지
        SceneRegister()                                = delete;
        SceneRegister(const SceneRegister&)            = delete;
        SceneRegister& operator=(const SceneRegister&) = delete;
        SceneRegister(SceneRegister&&)                 = delete;
        SceneRegister& operator=(SceneRegister&&)      = delete;

        // 동적 할당 금지
        static void* operator new(std::size_t)         = delete;
        static void* operator new[](std::size_t)       = delete;
        static void operator delete(void*)             = delete;
        static void operator delete[](void*)           = delete;

        ~SceneRegister()                               = default;
    };
}