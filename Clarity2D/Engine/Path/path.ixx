module;
    #include "c2d_dx.h"
export module c2d.engine.path;

import c2d.core.types;
import c2d.core.singleton;

using namespace c2d::path_access_level;

export namespace c2d
{
    class PathManager final : public Singleton<PathManager>
    {
    private:
        c2path _exeDir{};
        c2path _root  {};
        bool   _inited{ false };

    private:
        c2path GetExeDir();
        c2path FindRootByAssets(const c2path& exeDir, std::wstring_view assetsName, uint8 maxUp);

    public:
        // 한 번만 호출해도 되고, 안 불러도 Abs()에서 lazy init 되게 할 수 있음(아래 구현 참고)
        void Init(std::wstring_view assetsFolderName = L"Assets", uint8 maxUp = 8) noexcept;

        // 핵심: 상대경로를 절대경로로
        c2path Abs(const c2path& path) noexcept;

        // 편의: Assets 기준
        c2path Assets(const c2path& rel) noexcept;

        const c2path& ExeDir() const noexcept { return _exeDir; }
        const c2path& Root()   const noexcept { return _root; }
    };
}

// PathManager 싱글톤 헬퍼 인라인 함수
export inline c2d::PathManager* Path() noexcept { return c2d::PathManager::GetInstance(); }