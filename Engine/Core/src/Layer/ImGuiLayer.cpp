#include "ImGuiLayer.hpp"

#include "Event/EventDispatcher.hpp"
#include "Event/KeyEvent.hpp"
#include "Event/MouseEvent.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

MCEngine::ImGuiLayer::ImGuiLayer(Window *window) : Layer("ImGuiLayer"), m_Window(window) {}

void MCEngine::ImGuiLayer::OnAttach()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

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

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow *>(m_Window->GetNativeWindow()), true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void MCEngine::ImGuiLayer::OnDetach()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void MCEngine::ImGuiLayer::OnEvent(Event &event)
{
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

void MCEngine::ImGuiLayer::OnUpdate()
{
    Begin();

    ImGui::ShowDemoWindow();

    End();
}

void MCEngine::ImGuiLayer::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MCEngine::ImGuiLayer::End()
{
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