#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Window
{
public:
    Window(int width, int height, std::string title);
    virtual ~Window();

    bool IsVSync() const { return m_VSync; }
    void SetVSync(bool enabled);

    void PreUpdate();
    void Update();
    void PostUpdate();

    void OnEvent(Event &e);

    bool ShouldClose() const;

private:
    void *m_Window = nullptr;
    bool m_VSync = true;

protected:
    void Init(int width, int height, std::string title);
    void Shutdown();

    void SetCallbacks();
};

} // namespace MCEngine
