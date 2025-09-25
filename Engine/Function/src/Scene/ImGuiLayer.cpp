// #include "ImGuiLayer.hpp"

// #include "Application/Application.hpp"
// #include <imgui.h>
// #include <imgui_impl_glfw.h>
// #include <imgui_impl_opengl3.h>

// MCEngine::ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}

// void MCEngine::ImGuiLayer::OnAttach()
// {
//     IMGUI_CHECKVERSION();
//     ImGui::CreateContext();
//     ImGuiIO &io = ImGui::GetIO();

//     (void)io;
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
//     io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
//     io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
//     io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows

//     // Setup Dear ImGui style
//     ImGui::StyleColorsDark();
//     // ImGui::StyleColorsClassic();

//     // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular
//     // ones.
//     ImGuiStyle &style = ImGui::GetStyle();
//     if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//     {
//         style.WindowRounding = 0.0f;
//         style.Colors[ImGuiCol_WindowBg].w = 1.0f;
//     }

//     Application &app = Application::Get();
//     GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

//     // Setup Platform/Renderer bindings
//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 410");
// }

// void MCEngine::ImGuiLayer::OnDetach()
// {
//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();
// }

// void MCEngine::ImGuiLayer::OnEvent(Event &event)
// {
//     EventDispatcher dispatcher(event);

//     dispatcher.Dispatch<MouseButtonEvent>([](MouseButtonEvent &e) {
//         ImGuiIO &io = ImGui::GetIO();
//         io.AddMouseButtonEvent(e.GetMouseButton(), e.GetAction() == 1);
//         return io.WantCaptureMouse;
//     });

//     dispatcher.Dispatch<MouseMoveEvent>([](MouseMoveEvent &e) {
//         ImGuiIO &io = ImGui::GetIO();
//         io.AddMousePosEvent((float)e.GetX(), (float)e.GetY());
//         return io.WantCaptureMouse;
//     });

//     dispatcher.Dispatch<KeyEvent>([](KeyEvent &e) {
//         ImGuiIO &io = ImGui::GetIO();
//         io.AddKeyEvent(e.GetKeyCode(), e.GetAction() == 1 || e.GetAction() == 2);
//         return io.WantCaptureKeyboard;
//     });
// }

// void MCEngine::ImGuiLayer::OnUpdate()
// {
//     Begin();

//     ImGui::ShowDemoWindow();

//     End();
// }

// void MCEngine::ImGuiLayer::Begin()
// {
//     ImGui_ImplOpenGL3_NewFrame();
//     ImGui_ImplGlfw_NewFrame();
//     ImGui::NewFrame();
// }

// void MCEngine::ImGuiLayer::End()
// {
//     ImGuiIO &io = ImGui::GetIO();
//     Application &app = Application::Get();
//     io.DisplaySize = ImVec2((float)app.GetWindow().GetProps().Width, (float)app.GetWindow().GetProps().Height);

//     // Rendering
//     ImGui::Render();
//     ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//     if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
//     {
//         GLFWwindow *backup_current_context = glfwGetCurrentContext();
//         ImGui::UpdatePlatformWindows();
//         ImGui::RenderPlatformWindowsDefault();
//         glfwMakeContextCurrent(backup_current_context);
//     }
// }