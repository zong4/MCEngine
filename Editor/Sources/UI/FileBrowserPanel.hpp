#pragma once

#include <Function.hpp>

namespace MCEditor
{

class FileBrowserPanel
{

public:
    FileBrowserPanel();
    ~FileBrowserPanel() = default;

    void SetCurrentDirectory(const std::filesystem::path &path) { m_CurrentDirectory = path; }

public:
    void OnImGuiRender();

private:
    std::filesystem::path m_CurrentDirectory;

    // Icons
    std::shared_ptr<MCEngine::Texture2D> m_DirectoryIcon;
    std::shared_ptr<MCEngine::Texture2D> m_FileIcon;
};

} // namespace MCEditor