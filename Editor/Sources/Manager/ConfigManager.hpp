#pragma once

#include <Function.hpp>

namespace MCEditor
{

class ConfigManager
{
public:
    static ConfigManager &GetInstance();

    static bool IsScene(std::filesystem::path path) { return path.extension() == ".mcscene"; }

    static std::string GetConfigsPath() { return s_ConfigsPath; }
    static std::string GetAssetsPath() { return s_AssetsPath; }
    static std::string GetScenesPath() { return s_ScenesPath; }
    static std::string GetIconsPath() { return s_IconsPath; }

private:
    static std::string s_ConfigsPath;
    static std::string s_AssetsPath;
    static std::string s_ScenesPath;
    static std::string s_IconsPath;

private:
    ConfigManager();
};

} // namespace MCEditor