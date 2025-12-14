module;
    #include "c2d_dx.h"
export module c2d.system.game_object;

import c2d.core.types;

using namespace c2d::math;

export namespace c2d
{
    class GameObject
    {
    private:
        Transform2D  _transform{};
        c2wstring    _name;
        uint32       _id;
        int32        _layer;
        float32      _zOrder;
        bool         _bVisibility;
        bool         _bActivity;

    public:
        GameObject() {};
        virtual ~GameObject() = default;

        GameObject(const GameObject&)            = delete;
        GameObject& operator=(const GameObject&) = delete;

    public:
        virtual void Create()                       {}
        virtual void Destroy()                      {}
        virtual void Update(float32 deltatime)    = 0;
        virtual void Render()                     = 0;

    public:
        c2wstring_view       GetName()       const noexcept { return _name; }
        uint32               GetID()         const noexcept { return _id; }
        int32                GetLayer()      const noexcept { return _layer; }
        float32              GetZOrder()     const noexcept { return _zOrder; }
        bool                 GetVisibility() const noexcept { return _bVisibility; }
        bool                 GetActivity()   const noexcept { return _bActivity; }
        Transform2D&         GetTransform()        noexcept { return _transform; }
        const Transform2D&   GetTransform()  const noexcept { return _transform; }
        vec2                 GetPosition()   const noexcept { return _transform.position; }
        vec2                 GetScale()      const noexcept { return _transform.scale; }
        float32              GetRotation()   const noexcept { return _transform.rotation; } // rad
        float32              GetDepth()      const noexcept { return _transform.depth; }

        void SetName(c2wstring name)               noexcept { _name = std::move(name); }
        void SetID(const uint32 id)                noexcept { _id = id; }
        void SetLayer(const int32 layer)           noexcept { _layer = layer; }
        void SetZOrder(const float32 z)            noexcept { _zOrder = z; }
        void SetVisibility(const bool v)           noexcept { _bVisibility = v; }
        void SetActivity(const bool a)             noexcept { _bActivity = a; }
        void SetPosition(const vec2& pos)          noexcept { _transform.position = pos; }
        void SetPosition(float32 x, float32 y)     noexcept { _transform.position.x = x; _transform.position.y = y; }
        void SetScale(const vec2& scale)           noexcept { _transform.scale = scale; }
        void SetScale(float32 x, float32 y)        noexcept { _transform.scale.x = x; _transform.scale.y; }
        void SetRotation(float32 rad)              noexcept { _transform.rotation = rad; }
        void SetDepth(float32 depth)               noexcept { _transform.depth = depth; }
    };
}