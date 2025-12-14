/*
* Clarity2D의 Scene 템플릿입니다.
* 모듈(*.ixx)내에서 구현체 작성은 비추천하며
* 별도의 소스(*.cpp)에서 구현체를 작성하는게 안전합니다.
* 
* 작성일 : 25.12.11
*/
module; 
    #include "c2d_dx.h"
export module DefaultScene;

import c2d.core.types;
import c2d.engine.scene;
import c2d.system.scene_object;
import c2d.engine.path;
import TestSprite;

using namespace TC2D;
using namespace c2d::math;

export namespace c2d
{
    class DefaultScene final : public SceneObject
    {
        C2D_REGISTER_SCENE(DefaultScene, "DefaultScene") // Scene을 등록합니다.
    private:
        std::unique_ptr<TestSprite> sprite = nullptr;
    public:
        DefaultScene()  { Create(); }                     // Scene의 생성자입니다. [Create()  포함 필수]
        ~DefaultScene() { Destroy(); }                    // Scene의 소멸자입니다. [Destroy() 포함 필수]

        void Create() override                            // Scene이 등록될 때 처리할 명령을 작성합니다.
        {
            sprite = std::make_unique<TestSprite>(ASSETS("Assets/icon_01.png"), XY(0, 0));
        }

        void Show() override                              // Scene이 로딩되면 처리할 명령을 작성합니다.
        {
            AddObject(std::move(sprite));
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