module;
    #include "c2d_dx.h"
module c2d.engine.path;

import c2d.core.types;

using namespace c2d;
using namespace c2d::path_access_level;

c2path PathManager::GetExeDir()
{
    std::array<wchar_t, MAX_PATH> buf{};
    GetModuleFileNameW(nullptr, buf.data(), MAX_PATH);
    return c2path(buf.data()).parent_path();
}

c2path PathManager::FindRootByAssets(const c2path& exeDir, c2wstring_view assetsName, uint8 maxUp)
{
    c2path cur = exeDir;

    for (uint8 i = 0; i <= maxUp; ++i)
    {
        const auto marker = (cur / assetsName);
        std::error_code ec{};
        if (std::filesystem::exists(marker, ec) && std::filesystem::is_directory(marker, ec))
        {
            return cur.lexically_normal();
        }

        if (!cur.has_parent_path())
        {
            break;
        }

        cur = cur.parent_path();
    }

    return exeDir.lexically_normal();
}

void PathManager::Init(c2wstring_view assetsFolderName, uint8 maxUp) noexcept
{
    _exeDir = GetExeDir().lexically_normal();
    _root = FindRootByAssets(_exeDir, assetsFolderName, maxUp);
    _inited = true;
}

c2path PathManager::Abs(const c2path& path) noexcept
{
    if (!_inited)
    {
        Init();
    }

    if (path.is_absolute())
    {
        return path.lexically_normal();
    }
    return (_root / path).lexically_normal();
}

c2path PathManager::Assets(const c2path& rel) noexcept
{
    if (!_inited)
    {
        Init();
    }

    if (!rel.empty() && (*rel.begin() == L"Assets"))
    {
        return (_root / rel).lexically_normal();
    }
    return (_root / L"Assets" / rel).lexically_normal();
}