#pragma once

#include <Function.hpp>

namespace MCEditor
{

class FileBrowserPanel
{

public:
    FileBrowserPanel() = default;
    ~FileBrowserPanel() = default;

public:
    void OnImGuiRender(const std::filesystem::path &directory) const { RenderFileBrowser(directory); }

private:
    void RenderFileBrowser(const std::filesystem::path &directory) const;
};

} // namespace MCEditor