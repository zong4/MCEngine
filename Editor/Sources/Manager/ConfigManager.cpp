#include "ConfigManager.hpp"

#include <nlohmann/json.hpp>

// Set default window properties
MCEngine::WindowProperty MCEditor::ConfigManager::s_WindowProperty =
    MCEngine::WindowProperty("Minecraft Engine", 1280, 720, true, glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

// Set default paths
std::filesystem::path MCEditor::ConfigManager::s_ConfigsPath = "Editor/Configs/";
std::filesystem::path MCEditor::ConfigManager::s_AssetsPath = "Editor/Assets/";
std::filesystem::path MCEditor::ConfigManager::s_ScenesPath = "Editor/Assets/Scenes/";
std::filesystem::path MCEditor::ConfigManager::s_IconsPath = "Editor/Resources/Icons/";

// Set default extensions
std::string MCEditor::ConfigManager::s_SceneExtension = ".mcscene";
std::set<std::string> MCEditor::ConfigManager::s_TextureExtensions = {".png", ".jpg"};

MCEditor::ConfigManager &MCEditor::ConfigManager::GetInstance()
{
    static ConfigManager instance;
    return instance;
}

bool MCEditor::ConfigManager::IsScene(std::filesystem::path path) { return path.extension() == s_SceneExtension; }

bool MCEditor::ConfigManager::IsTexture(std::filesystem::path path)
{
    return IsExtensionInSet(path.extension().string(), s_TextureExtensions);
}

MCEditor::ConfigManager::ConfigManager()
{
    ENGINE_PROFILE_FUNCTION();

    // Load configuration from JSON file
    std::string configFilePath = std::string(PROJECT_ROOT) + "Editor/Configs/config.json";
    std::ifstream configFile(configFilePath);
    if (configFile.is_open())
    {
        nlohmann::json configJson;
        configFile >> configJson;

        if (configJson.contains("Window"))
        {
            auto windowConfig = configJson["Window"];
            std::string title = windowConfig.value("Title", s_WindowProperty.Title);
            int width = windowConfig.value("Width", s_WindowProperty.Width);
            int height = windowConfig.value("Height", s_WindowProperty.Height);
            bool vsync = windowConfig.value("VSync", s_WindowProperty.VSync);
            std::vector<float> clearColor = windowConfig.value(
                "ClearColor", std::vector<float>{s_WindowProperty.ClearColor.r, s_WindowProperty.ClearColor.g,
                                                 s_WindowProperty.ClearColor.b, s_WindowProperty.ClearColor.a});
            if (clearColor.size() != 4)
            {
                LOG_ENGINE_WARN("Invalid ClearColor in config file. Using default clear color.");
                clearColor = {s_WindowProperty.ClearColor.r, s_WindowProperty.ClearColor.g,
                              s_WindowProperty.ClearColor.b, s_WindowProperty.ClearColor.a};
            }
            s_WindowProperty = MCEngine::WindowProperty(
                title, width, height, vsync, glm::vec4(clearColor[0], clearColor[1], clearColor[2], clearColor[3]));
        }

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

        if (configJson.contains("Extensions"))
        {
            auto extensions = configJson["Extensions"];
            if (extensions.contains("Scene"))
                s_SceneExtension = extensions["Scene"].get<std::string>();
            if (extensions.contains("Texture"))
                s_TextureExtensions = std::set<std::string>(extensions["Texture"].begin(), extensions["Texture"].end());
        }
    }
    else
    {
        LOG_ENGINE_WARN("Could not open config file: " + configFilePath + ". Using default configurations.");
    }

    // Prepend PROJECT_ROOT to make paths absolute
    s_ConfigsPath = std::filesystem::path(PROJECT_ROOT) / s_ConfigsPath;
    s_AssetsPath = std::filesystem::path(PROJECT_ROOT) / s_AssetsPath;
    s_ScenesPath = std::filesystem::path(PROJECT_ROOT) / s_ScenesPath;
    s_IconsPath = std::filesystem::path(PROJECT_ROOT) / s_IconsPath;
}

bool MCEditor::ConfigManager::IsExtensionInSet(const std::string &extension, const std::set<std::string> &extensionSet)
{
    return extensionSet.find(extension) != extensionSet.end();
}