module; 
    #include "c2d_dx.h"
export module DefaultScene;

import c2d.engine.scene;
import c2d.system.scene_object;

export namespace c2d
{
    class DefaultScene final : public SceneObject
    {
        C2D_REGISTER_SCENE(DefaultScene, L"DefaultScene") // Scene을 등록합니다.
    private:

    public:
        DefaultScene() { Create(); }                      // Scene의 생성자입니다. [Create()  포함 필수]
        ~DefaultScene() { Destroy(); }                    // Scene의 소멸자입니다. [Destroy() 포함 필수]

        void Create() override                            // Scene이 등록될 때 처리할 명령을 작성합니다.
        {

        }

        void Show() override                              // Scene이 로딩되면 처리할 명령을 작성합니다.
        {

        }

        void Hide() override                              // Scene이 언로드되면 처리할 명령을 작성합니다.
        {

        }

        void Update(const float32 dt) override            // Scene이 매 프레임마다 처리할 명령을 작성합니다.
        {
            SceneObject::Update(dt);

        }
    };
}