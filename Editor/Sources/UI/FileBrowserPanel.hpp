#pragma once

#include <Function.hpp>

namespace MCEditor
{

class FileBrowserPanel
{

public:
    FileBrowserPanel();
    ~FileBrowserPanel() = default;

public:
    void OnImGuiRender();

private:
    std::filesystem::path m_CurrentDirectory;
    std::shared_ptr<MCEngine::Texture2D> m_FileIcon;
    std::shared_ptr<MCEngine::Texture2D> m_DirectoryIcon;

private:
    void SetCurrentDirectory(const std::filesystem::path &path) { m_CurrentDirectory = path; }
};

} // namespace MCEditor