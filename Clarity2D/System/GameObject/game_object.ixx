export module c2d.system.game_object;

import c2d.engine.types;

export namespace c2d
{
    class SceneObject;

    class GameObject
    {
    private:
        SceneObject* _scene;
        c2wstring    _name;
        uint32       _id;
        int32        _layer;
        float32      _zOrder;
        bool         _bVisibility;
        bool         _bActivity;

    public:
        GameObject()          = default;
        virtual ~GameObject() = default;

        GameObject(const GameObject&)            = delete;
        GameObject& operator=(const GameObject&) = delete;

    public:
        virtual void Create()                       {}
        virtual void Destroy()                      {}
        virtual void ASyncUpdate(float32 deltatime) {}
        virtual void Update(float32 deltatime) = 0;
        virtual void Render()                  = 0;

    public:
        c2wstring_view       GetName()       const noexcept { return _name; }
        uint32               GetID()         const noexcept { return _id; }
        int32                GetLayer()      const noexcept { return _layer; }
        float32              GetZOrder()     const noexcept { return _zOrder; }
        bool                 GetVisibility() const noexcept { return _bVisibility; }
        bool                 GetActivity()   const noexcept { return _bActivity; }
        const SceneObject*   GetScene()      const noexcept { return _scene; }

        void SetName(c2wstring name)               noexcept { _name = std::move(name); }
        void SetID(const uint32 id)                noexcept { _id = id; }
        void SetLayer(const int32 layer)           noexcept { _layer = layer; }
        void SetZOrder(const float32 z)            noexcept { _zOrder = z; }
        void SetVisibility(const bool v)           noexcept { _bVisibility = v; }
        void SetActivity(const bool a)             noexcept { _bActivity = a; }
        void SetScene(SceneObject* scene)          noexcept { _scene = scene; }
    };
}