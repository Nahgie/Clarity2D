module;
    #include "c2d_dx.h"
module c2d.engine.path;

import c2d.core.types;

using namespace c2d;
using namespace c2d::path_access_level;

void PathManager::ApplyAccessLevel()
{
    auto base = std::filesystem::current_path();
    const auto level = static_cast<uint8>(_accessLevel);

    for (uint8 access = 0; access < level && base.has_parent_path(); ++access)
    {
        base = base.parent_path();
    }
    _basePath = base.lexically_normal();
}

void PathManager::SetAccessLevel(ePathAccessLevel lv)
{
    _accessLevel = lv;
    ApplyAccessLevel();
}

ePathAccessLevel PathManager::GetAccessLevel() const noexcept
{
    return _accessLevel;
}

void PathManager::ResetBasePath(const c2path& newpath)
{
    _basePath = newpath.lexically_normal();
}

const c2path& PathManager::GetBasePath() const noexcept
{
    return _basePath;
}

c2path PathManager::MakePath(const c2path& relative) const
{
    if (relative.is_absolute())
    {
        return relative.lexically_normal();
    }

    return (_basePath / relative).lexically_normal();
}