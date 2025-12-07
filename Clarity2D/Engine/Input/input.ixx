module;
    #include "c2d_dx.h"
export module c2d.engine.input;

import c2d.core.singleton;

using namespace DirectX;

export namespace c2d
{
    class InputManager final : public Singleton<InputManager>
    {
    private:
        std::unique_ptr<Keyboard>      _keyboard;
        std::unique_ptr<Mouse>         _mouse;

        Keyboard::State                _kbState  {};
        Keyboard::KeyboardStateTracker _kbTracker{};

        Mouse::State                   _msState  {};
        Mouse::ButtonStateTracker      _msTracker{};

    public:
        void Init(HWND hWnd)
        {
            _keyboard = std::make_unique<Keyboard>();
            _mouse    = std::make_unique<Mouse>();

            _mouse->SetWindow(hWnd);
            _mouse->SetMode(Mouse::MODE_ABSOLUTE);
        }

        void Update()
        {
            _kbState = _keyboard->GetState();
            _msState = _mouse->GetState();

            _kbTracker.Update(_kbState);
            _msTracker.Update(_msState);
        }

    public:
        const Keyboard::State&                GetKeyboardState()   const noexcept { return _kbState; }
        const Keyboard::KeyboardStateTracker& GetKeyboardTracker() const noexcept { return _kbTracker; }

        const Mouse::State&                   GetMouseState()      const noexcept { return _msState; }
        const Mouse::ButtonStateTracker&      GetMouseTracker()    const noexcept { return _msTracker; }

        bool IsKeyUp(Keyboard::Keys key)       const noexcept { return _kbState.IsKeyUp(key); }
        bool IsKeyDown(Keyboard::Keys key)     const noexcept { return _kbState.IsKeyDown(key); }
        bool IsKeyPressed(Keyboard::Keys key)  const noexcept { return _kbTracker.IsKeyPressed(key); }
        bool IsKeyReleased(Keyboard::Keys key) const noexcept { return _kbTracker.IsKeyReleased(key); }
    };
}

// InputManager 싱글톤 헬퍼 인라인 함수
export inline c2d::InputManager* Input() noexcept { return c2d::InputManager::GetInstance(); }