#include "EditorConfig.hpp"

#include <nlohmann/json.hpp>

// Set default paths
std::string MCEditor::EditorConfig::s_ConfigsPath = "Editor/Configs/";
std::string MCEditor::EditorConfig::s_AssetsPath = "Editor/Assets/";
std::string MCEditor::EditorConfig::s_ScenesPath = "Editor/Assets/Scenes/";
std::string MCEditor::EditorConfig::s_IconsPath = "Editor/Resources/Icons/";

MCEditor::EditorConfig &MCEditor::EditorConfig::GetInstance()
{
    static EditorConfig instance;
    return instance;
}

MCEditor::EditorConfig::EditorConfig()
{
    ENGINE_PROFILE_FUNCTION();

    // Load configuration from JSON file
    std::string configFilePath = std::string(PROJECT_ROOT) + "Editor/Configs/config.json";
    std::ifstream configFile(configFilePath);
    if (configFile.is_open())
    {
        nlohmann::json configJson;
        configFile >> configJson;

        if (configJson.contains("RelativePath"))
        {
            auto relativePaths = configJson["RelativePath"];
            if (relativePaths.contains("Configs"))
                s_ConfigsPath = relativePaths["Configs"].get<std::string>();
            if (relativePaths.contains("Assets"))
                s_AssetsPath = relativePaths["Assets"].get<std::string>();
            if (relativePaths.contains("Scenes"))
                s_ScenesPath = relativePaths["Scenes"].get<std::string>();
            if (relativePaths.contains("Icons"))
                s_IconsPath = relativePaths["Icons"].get<std::string>();
        }
        else
        {
            LOG_ENGINE_WARN("No 'RelativePath' section found in config.json. Using default paths.");
        }
    }
    else
    {
        LOG_ENGINE_WARN("Could not open config file: " + configFilePath + ". Using default paths.");
    }

    // Prepend PROJECT_ROOT to make paths absolute
    s_ConfigsPath = std::string(PROJECT_ROOT) + s_ConfigsPath;
    s_AssetsPath = std::string(PROJECT_ROOT) + s_AssetsPath;
    s_ScenesPath = std::string(PROJECT_ROOT) + s_ScenesPath;
    s_IconsPath = std::string(PROJECT_ROOT) + s_IconsPath;
}