#include "Layer.hpp"

#include "Logger/Logger.hpp"

MCEngine::Layer::Layer(const std::string &name) : m_Name(name) {}

void MCEngine::Layer::OnAttach() { LOG_ENGINE_INFO("Layer " + m_Name + " attached."); }
void MCEngine::Layer::OnDetach() { LOG_ENGINE_INFO("Layer " + m_Name + " detached."); }