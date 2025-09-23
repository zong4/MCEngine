#pragma once

#include "Buffer/VertexArray.hpp"
#include "Shader/ShaderLibrary.hpp"

namespace MCEngine
{

class Window
{
public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    void Update();
    bool ShouldClose() const;

protected:
    void Init(int width, int height, std::string title);
    void Shutdown();

private:
    void *m_Window = nullptr;

    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<ShaderLibrary> m_ShaderLibrary;
};

} // namespace MCEngine
