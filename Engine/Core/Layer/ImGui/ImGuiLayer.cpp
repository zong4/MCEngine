#include "ImGuiLayer.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/Key/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// After import imgui
#include <ImGuizmo.h>

MCEngine::ImGuiLayer::ImGuiLayer(const std::shared_ptr<Window> &windowPtr, const std::string &filePath,
                                 const std::string &name)
    : Layer(name), m_WindowPtr(windowPtr), m_ImGuiFilePath(filePath)
{
}

void MCEngine::ImGuiLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiIO &io = ImGui::GetIO();
    io.WantCaptureMouse = false;

    if (!event.IsHandled())
    {
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
}

void MCEngine::ImGuiLayer::OnImGuiRender()
{
    BeginRenderImGui();
    RenderImGui();
    EndRenderImGui();
}

void MCEngine::ImGuiLayer::BeginRenderImGui() const
{
    ENGINE_PROFILE_FUNCTION();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
}

void MCEngine::ImGuiLayer::EndRenderImGui() const
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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

    // Fonts
    ImFont *fontChild = io.Fonts->AddFontFromFileTTF(
        (std::string(PROJECT_ROOT) + "Engine/Assets/Fonts/Shadows_Into_Light/ShadowsIntoLight-Regular.ttf").c_str(),
        18.0f);
    ImFont *fontCute = io.Fonts->AddFontFromFileTTF(
        (std::string(PROJECT_ROOT) + "Engine/Assets/Fonts/Delius/Delius-Regular.ttf").c_str(), 18.0f);
    ImFont *fontActive = io.Fonts->AddFontFromFileTTF(
        (std::string(PROJECT_ROOT) + "Engine/Assets/Fonts/Allan/Allan-Regular.ttf").c_str(), 18.0f);
    ImFont *fontActiveBold = io.Fonts->AddFontFromFileTTF(
        (std::string(PROJECT_ROOT) + "Engine/Assets/Fonts/Allan/Allan-Bold.ttf").c_str(), 18.0f);

    // Set default font
    ImFont *customFont = fontCute;
    if (!customFont)
    {
        LOG_EDITOR_INFO("Failed to load custom font! Using default font instead.");
        customFont = io.FontDefault;
    }
    io.FontDefault = customFont;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
    // ones.
    ImGuiStyle &style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Custom theme
    SetDarkThemeColors();

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

static ImVec4 ReverseGammaCorrection(ImVec4 &&color)
{
    color.x = pow(color.x, 2.2f);
    color.y = pow(color.y, 2.2f);
    color.z = pow(color.z, 2.2f);
    return color;
}

void MCEngine::ImGuiLayer::SetDarkThemeColors()
{
    auto &colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ReverseGammaCorrection(ImVec4{0.1f, 0.105f, 0.11f, 1.0f});

    // Headers
    colors[ImGuiCol_Header] = ReverseGammaCorrection(ImVec4{0.2f, 0.205f, 0.21f, 1.0f});
    colors[ImGuiCol_HeaderHovered] = ReverseGammaCorrection(ImVec4{0.3f, 0.305f, 0.31f, 1.0f});
    colors[ImGuiCol_HeaderActive] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});

    // Buttons
    colors[ImGuiCol_Button] = ReverseGammaCorrection(ImVec4{0.2f, 0.205f, 0.21f, 1.0f});
    colors[ImGuiCol_ButtonHovered] = ReverseGammaCorrection(ImVec4{0.3f, 0.305f, 0.31f, 1.0f});
    colors[ImGuiCol_ButtonActive] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});

    // Frame BG
    colors[ImGuiCol_FrameBg] = ReverseGammaCorrection(ImVec4{0.2f, 0.205f, 0.21f, 1.0f});
    colors[ImGuiCol_FrameBgHovered] = ReverseGammaCorrection(ImVec4{0.3f, 0.305f, 0.31f, 1.0f});
    colors[ImGuiCol_FrameBgActive] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});

    // Tabs
    colors[ImGuiCol_Tab] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});
    colors[ImGuiCol_TabHovered] = ReverseGammaCorrection(ImVec4{0.38f, 0.3805f, 0.381f, 1.0f});
    colors[ImGuiCol_TabActive] = ReverseGammaCorrection(ImVec4{0.28f, 0.2805f, 0.281f, 1.0f});
    colors[ImGuiCol_TabUnfocused] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});
    colors[ImGuiCol_TabUnfocusedActive] = ReverseGammaCorrection(ImVec4{0.2f, 0.205f, 0.21f, 1.0f});

    // Title
    colors[ImGuiCol_TitleBg] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});
    colors[ImGuiCol_TitleBgActive] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});
    colors[ImGuiCol_TitleBgCollapsed] = ReverseGammaCorrection(ImVec4{0.15f, 0.1505f, 0.151f, 1.0f});
}