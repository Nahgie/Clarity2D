module;
    #include "c2d_dx.h"
export module c2d.system.scene_object;

import c2d.core.types;
import c2d.system.game_object;

export namespace c2d
{
    class SceneObject
    {
    private:
        std::vector<std::shared_ptr<GameObject>> _objects;

    protected:
        void AddObject(const std::shared_ptr<GameObject>& obj) { obj->Create(); _objects.emplace_back(obj); }
        void ClearObjects() noexcept                           { _objects.clear(); }

    public:
        SceneObject()                              = default;
        virtual ~SceneObject()                     = default;
        SceneObject(const SceneObject&)            = default;
        SceneObject& operator=(const SceneObject&) = delete;

    public:
        virtual void Create()      {}
        virtual void Show()        {}
        virtual void Hide()        {}
        virtual void Destroy()     {}

        virtual void Update(const float32 deltatime)
        {
            for (const auto& obj : _objects)
            {
                if (!obj)
                {
                    continue;
                }
                obj->Update(deltatime);
            }
        }

        virtual void Draw()
        {
            for (const auto& obj : _objects)
            {
                if (!obj)
                {
                    continue;
                }
                obj->Render();
            }
        }
    };
}