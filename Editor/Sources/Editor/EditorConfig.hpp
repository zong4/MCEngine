#pragma once

#include <Function.hpp>

namespace MCEditor
{

class EditorConfig
{
public:
    static EditorConfig &GetInstance();

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
    EditorConfig();
};

} // namespace MCEditor