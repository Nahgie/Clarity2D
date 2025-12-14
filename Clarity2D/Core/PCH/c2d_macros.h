/*
* Clarity2D 엔진 매크로를 정의합니다.
* 
* 작성일 : 25.12.10
*/
#pragma once

#ifdef TEXT
    #undef TEXT
#endif

// 와이드 스트링 처리용 매크로
#define C2D_WIDE_IMPL(STR) \
    L##STR

#define C2D_WIDE(STR) \
    C2D_WIDE_IMPL(STR)

#define TEXT(STR) \
    C2D_WIDE(STR)

#define PATH(STR) \
    Path()->Abs(C2D_WIDE(STR))

#define ASSETS(STR) \
    Path()->Assets(C2D_WIDE(STR))

// 메시지(Win32 MessageBoxW) 단발성 처리용 매크로
#define ShowError(msg) \
    ErrorMsg(C2D_WIDE(msg))

#define ShowWarning(msg) \
    WarningMsg(C2D_WIDE(msg))

#define ShowInformation(msg) \
    InformationMsg(C2D_WIDE(msg))

// 씬(SceneObject) 등록 매크로
#define C2D_REGISTER_SCENE(T, NAME) \
    inline static ::c2d::SceneRegister<T> _sceneContext{ C2D_WIDE(NAME) };

// XY좌표 코디네이션용 매크로
#define XY(X, Y) \
    c2d::math::vec2{ static_cast<float32>(X), static_cast<float32>(Y) }