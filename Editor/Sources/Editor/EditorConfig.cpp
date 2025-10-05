#include "EditorConfig.hpp"

#include <nlohmann/json.hpp>

MCEditor::EditorConfig &MCEditor::EditorConfig::GetInstance()
{
    static EditorConfig instance;
    return instance;
}

MCEditor::EditorConfig::EditorConfig()
{
    ENGINE_PROFILE_FUNCTION();

    // Load configuration from JSON file
    std::string configFilePath = std::string(PROJECT_ROOT) + "/Editor/Configs/config.json";
    std::ifstream configFile(configFilePath);
    if (configFile.is_open())
    {
        nlohmann::json configJson;
        configFile >> configJson;

        if (configJson.contains("RelativePath"))
        {
            auto relativePaths = configJson["RelativePath"];
            if (relativePaths.contains("Configs"))
                m_ConfigsPath = relativePaths["Configs"].get<std::string>();
            if (relativePaths.contains("Assets"))
                m_AssetsPath = relativePaths["Assets"].get<std::string>();
            if (relativePaths.contains("Scenes"))
                m_ScenesPath = relativePaths["Scenes"].get<std::string>();
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

    LOG_ENGINE_INFO("EditorConfig initialized with ConfigsPath: " + m_ConfigsPath + ", AssetsPath: " + m_AssetsPath +
                    ", ScenesPath: " + m_ScenesPath);
}