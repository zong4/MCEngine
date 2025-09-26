#include "ImGuiLayer.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

MCEngine::ImGuiLayer::ImGuiLayer(std::shared_ptr<Window> window) : Layer("ImGuiLayer"), m_Window(window)
{
    ENGINE_PROFILE_FUNCTION();

    m_GuiFilePath = std::string(PROJECT_ROOT) + "/Editor/configs/imgui.ini";
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
    ImGui::GetIO().IniFilename = m_GuiFilePath.c_str();
    ImGui::LoadIniSettingsFromDisk(m_GuiFilePath.c_str());

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(m_Window->GetNativeWindow()), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void MCEngine::ImGuiLayer::OnDetach()
{
    ENGINE_PROFILE_FUNCTION();

    // Save ini file
    ImGui::SaveIniSettingsToDisk(m_GuiFilePath.c_str());

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MCEngine::ImGuiLayer::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    EventDispatcher dispatcher(event);

    dispatcher.Dispatch<MouseButtonEvent>([](MouseButtonEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMouseButtonEvent(e.GetButton(), e.GetAction() == 1);
        return io.WantCaptureMouse;
    });

    dispatcher.Dispatch<MouseMoveEvent>([](MouseMoveEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.AddMousePosEvent((float)e.GetX(), (float)e.GetY());
        return io.WantCaptureMouse;
    });

    dispatcher.Dispatch<KeyEvent>([](KeyEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.AddKeyEvent(static_cast<ImGuiKey>(e.GetKeyCode()), e.GetAction() == 1 || e.GetAction() == 2);
        return io.WantCaptureKeyboard;
    });
}

void MCEngine::ImGuiLayer::OnImGuiRender(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    Begin();

    RenderDockSpace();

    ImGui::Begin("Event Info");
    ImGui::Text("Delta Time: %.3f ms/frame (%.1f FPS)", deltaTime * 1000.0f, 1.0f / deltaTime);
    ImGui::Text("Mouse Position: (%.1f, %.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
    ImGui::Text("Mouse Buttons: Left(%d), Right(%d), Middle(%d)", ImGui::GetIO().MouseDown[0],
                ImGui::GetIO().MouseDown[1], ImGui::GetIO().MouseDown[2]);
    ImGui::End();

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
    io.DisplaySize = ImVec2((float)m_Window->GetProps().Width, (float)m_Window->GetProps().Height);

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

void MCEngine::ImGuiLayer::RenderDockSpace()
{
    ENGINE_PROFILE_FUNCTION();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                                    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                    ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                                    ImGuiWindowFlags_MenuBar;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
    ImGui::Begin("DockSpace", nullptr, window_flags);
    ImGui::PopStyleColor();

    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
    ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    // Menu Bar
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                m_Window->SetRunning(false);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::End();
}