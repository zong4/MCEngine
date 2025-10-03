#include "FileBrowserPanel.hpp"

#include <imgui.h>

void MCEditor::FileBrowserPanel::RenderFileBrowser(const std::filesystem::path &directory) const
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &&entry : std::filesystem::directory_iterator(directory))
    {
        auto &&filename = entry.path().filename().string();
        if (!filename.empty() && filename[0] == '.')
            continue;

        if (entry.is_directory())
        {
            if (ImGui::TreeNode(entry.path().filename().string().c_str()))
            {
                RenderFileBrowser(entry.path());
                ImGui::TreePop();
            }
        }
        else
        {
            ImGui::BulletText("%s", entry.path().filename().string().c_str());
        }
    }
}
