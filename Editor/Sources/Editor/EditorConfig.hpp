#pragma once

#include <Function.hpp>

namespace MCEditor
{

class EditorConfig
{
public:
    static EditorConfig &GetInstance();

    // Getters
    std::string GetConfigsPath() const { return std::string(PROJECT_ROOT) + m_ConfigsPath; }
    std::string GetAssetsPath() const { return std::string(PROJECT_ROOT) + m_AssetsPath; }
    std::string GetScenesPath() const { return std::string(PROJECT_ROOT) + m_ScenesPath; }

private:
    std::string m_ConfigsPath = "/Editor/Configs/";
    std::string m_AssetsPath = "/Editor/Assets/";
    std::string m_ScenesPath = "/Editor/Assets/Scenes/";

private:
    EditorConfig();
};

} // namespace MCEditor