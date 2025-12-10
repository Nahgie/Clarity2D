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
        c2path _basePath;
        ePathAccessLevel _accessLevel;

    private:
        void ApplyAccessLevel();

    public:
        PathManager(ePathAccessLevel lv = ePathAccessLevel::UP2) { _accessLevel = lv; }

        void SetAccessLevel(ePathAccessLevel lv);
        ePathAccessLevel GetAccessLevel() const noexcept;

        void ResetBasePath(const c2path& newpath);
        const c2path& GetBasePath() const noexcept;

        c2path MakePath(const c2path& relative) const;
    };
}

// PathManager 싱글톤 헬퍼 인라인 함수
export inline c2d::PathManager* Path() noexcept { return c2d::PathManager::GetInstance(); }