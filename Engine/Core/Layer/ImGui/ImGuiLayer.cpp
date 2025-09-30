#include "ImGuiLayer.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/Key/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

MCEngine::ImGuiLayer::ImGuiLayer(const std::shared_ptr<Window> &windowPtr, const std::string &filePath,
                                 const std::string &name)
    : Layer(name), m_WindowPtr(windowPtr), m_ImGuiFilePath(filePath)
{
}

void MCEngine::ImGuiLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<MouseButtonEvent>([](MouseButtonEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseButtonEvent(event.GetButton(), event.GetAction() == 1 || event.GetAction() == 2);
        return io.WantCaptureMouse;
    });

    dispatcher.Dispatch<MouseMoveEvent>([](MouseMoveEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMousePosEvent((float)event.GetX(), (float)event.GetY());
        return io.WantCaptureMouse;
    });

    dispatcher.Dispatch<KeyEvent>([](KeyEvent &event) {
        ImGuiIO &io = ImGui::GetIO();
        io.AddKeyEvent(static_cast<ImGuiKey>(event.GetKeyCode()), event.GetAction() == 1 || event.GetAction() == 2);
        return io.WantCaptureKeyboard;
    });
}

void MCEngine::ImGuiLayer::OnImGuiRender()
{
    Begin();
    End();
}

void MCEngine::ImGuiLayer::Begin()
{
    ENGINE_PROFILE_FUNCTION();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MCEngine::ImGuiLayer::End()
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiIO &io = ImGui::GetIO();
    io.DisplaySize =
        ImVec2((float)m_WindowPtr->GetProperty().GetWidth(), (float)m_WindowPtr->GetProperty().GetHeight());

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void MCEngine::ImGuiLayer::OnAttach()
{
    ENGINE_PROFILE_FUNCTION();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    // ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    // Read ini file
    ImGui::GetIO().IniFilename = m_ImGuiFilePath.c_str();
    ImGui::LoadIniSettingsFromDisk(m_ImGuiFilePath.c_str());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(m_WindowPtr->GetNativeWindowPtr()), true);
    std::string glsl_version = "#version " + std::to_string(m_WindowPtr->GetRendererAPIProperty().GetMajorVersion()) +
                               std::to_string(m_WindowPtr->GetRendererAPIProperty().GetMinorVersion()) + "0";
    ImGui_ImplOpenGL3_Init(glsl_version.c_str());
}

void MCEngine::ImGuiLayer::OnDetach()
{
    ENGINE_PROFILE_FUNCTION();

    // Save ini file
    ImGui::SaveIniSettingsToDisk(m_ImGuiFilePath.c_str());

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
