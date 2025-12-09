/*
* Clarity2D 엔진 매크로를 정의합니다.
* 
* 작성일 : 25.12.10
*/
#pragma once

// SceneObject 등록 매크로
#define C2D_REGISTER_SCENE(T, NAME) \
    inline static ::c2d::SceneRegister<T> _sceneContext{ NAME };