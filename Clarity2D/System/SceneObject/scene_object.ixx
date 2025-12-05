export module c2d.system.scene_object;

import c2d.engine.types;
import c2d.system.game_object;
import std;

export namespace c2d
{
    class SceneObject
    {
    private:
        std::vector<std::shared_ptr<GameObject>> _objects;

    protected:
        void AddObject(const std::shared_ptr<GameObject>& obj) { _objects.emplace_back(obj); }
        //void RemoveObject(const uint32 idx) noexcept { _objects.remove(idx); }
        void ClearObjects() noexcept { _objects.clear(); }

    public:
        SceneObject()          = default;
        virtual ~SceneObject() = default;

        SceneObject(const SceneObject&)            = default;
        SceneObject& operator=(const SceneObject&) = delete;

    public:
        virtual void Create()      {}
        virtual void Show()        {}
        virtual void Update()      {}
        virtual void ASyncUpdate() {}
        virtual void Hide()        {}
        virtual void Destroy()     {}

        virtual void Draw(const float32 deltatime)
        {
            for (auto& obj : _objects)
            {
                if (!obj)
                {
                    continue;
                }
                obj->Update(deltatime);
                obj->Render();
            }
        }
    };
}