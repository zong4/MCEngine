#include "Editor.hpp"

std::unique_ptr<MCEngine::Application> MCEngine::CreateApplication() { return std::make_unique<MCEditor::Editor>(); }