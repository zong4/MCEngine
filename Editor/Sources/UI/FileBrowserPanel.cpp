#include "FileBrowserPanel.hpp"

#include "Editor/EditorConfig.hpp"
#include "Scene/SceneManager.hpp"
#include <imgui.h>

MCEditor::FileBrowserPanel::FileBrowserPanel() : m_CurrentDirectory(EditorConfig::GetInstance().GetAssetsPath())
{
    ENGINE_PROFILE_FUNCTION();

    // Load icons
    m_DirectoryIcon =
        std::make_shared<MCEngine::Texture2D>(EditorConfig::GetInstance().GetIconsPath() + "Directory.png");
    m_FileIcon = std::make_shared<MCEngine::Texture2D>(EditorConfig::GetInstance().GetIconsPath() + "File.png");
}

void MCEditor::FileBrowserPanel::OnImGuiRender()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui::Begin("File Browser");

    if (!std::filesystem::equivalent(m_CurrentDirectory, EditorConfig::GetInstance().GetAssetsPath()))
    {
        if (ImGui::Button("<-"))
        {
            m_CurrentDirectory = m_CurrentDirectory.parent_path();
        }
    }

    static float padding = 10.0f;
    static float thumbnailSize = 60.0f;
    float cellSize = thumbnailSize + padding;

    float panelWidth = ImGui::GetContentRegionAvail().x;
    int columnCount = (int)(panelWidth / cellSize);
    if (columnCount < 1)
        columnCount = 1;

    ImGui::Columns(columnCount, 0, false);
    for (auto &&directoryEntry : std::filesystem::directory_iterator(m_CurrentDirectory))
    {
        // ID
        const auto &path = directoryEntry.path();
        auto &&relativePath = std::filesystem::relative(path, EditorConfig::GetInstance().GetAssetsPath());
        std::string filenameString = relativePath.filename().string();
        ImGui::PushID(filenameString.c_str());

        // Icon
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        std::shared_ptr<MCEngine::Texture2D> icon = directoryEntry.is_directory() ? m_DirectoryIcon : m_FileIcon;
        ImGui::ImageButton(filenameString.c_str(), (ImTextureID)icon->GetRendererID(), {thumbnailSize, thumbnailSize},
                           {0, 1}, {1, 0});
        ImGui::PopStyleColor();

        // Drag and Drop Source
        if (ImGui::BeginDragDropSource())
        {
            ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", path.c_str(), (strlen(path.c_str()) + 1) * sizeof(char));
            ImGui::EndDragDropSource();
        }

        // Handle double-click to open directory or select file
        if (ImGui::IsItemHovered())
        {
            if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                if (directoryEntry.is_directory())
                {
                    m_CurrentDirectory /= path.filename();
                }
                else
                {
                    if (relativePath.extension() == ".mcsene")
                    {
                        SceneManager::GetInstance().OpenScene(path.string());
                    }
                }
            }
            else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                // Handle file selection (e.g., open the file or display its properties)
                LOG_EDITOR_TRACE("Selected file: " + path.string());
            }
        }

        // Filename
        ImGui::TextWrapped("%s", filenameString.c_str());

        ImGui::PopID();
        ImGui::NextColumn();
    }

    // Footer
    ImGui::Columns(1);
    ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
    ImGui::SliderFloat("Padding", &padding, 0, 32);

    // if (ImGui::BeginDragDropTarget())
    // {
    //     LOG_EDITOR_TRACE("Begin drag drop target");
    //     if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
    //     {
    //         LOG_EDITOR_TRACE("Accept payload: CONTENT_BROWSER_ITEM");
    //         if (payload->Data)
    //         {
    //             const char *path = static_cast<const char *>(payload->Data);
    //             std::filesystem::path filepath(path);
    //             if (std::filesystem::is_directory(filepath))
    //             {
    //                 SetCurrentDirectory(filepath);
    //                 LOG_EDITOR_TRACE("Open directory: " + filepath.string());
    //             }
    //             else
    //             {
    //                 if (filepath.extension() == ".mcsene")
    //                 {
    //                     SceneManager::GetInstance().OpenScene(path);
    //                 }
    //             }
    //         }
    //     }
    //     ImGui::EndDragDropTarget();
    // }

    ImGui::End();
}
