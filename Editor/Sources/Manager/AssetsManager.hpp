#pragma once

#include "pch.hpp"

namespace MCEditor
{

class AssetsManager
{
public:
    static AssetsManager &GetInstance();

    void AddAsset(const std::filesystem::path &filepath);

private:
    AssetsManager();
    ~AssetsManager() = default;
};

} // namespace MCEditor