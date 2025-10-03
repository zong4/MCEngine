#include "LayerStack.hpp"

#include "Renderer/RendererCommand.hpp"

MCEngine::LayerStack::~LayerStack()
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &&layer : m_Layers)
    {
        layer->OnDetach();
    }
    m_Layers.clear();
}

void MCEngine::LayerStack::PushLayer(const std::shared_ptr<Layer> &layerPtr)
{
    ENGINE_PROFILE_FUNCTION();

    m_Layers.emplace_back(layerPtr);
    layerPtr->OnAttach();
    LOG_ENGINE_INFO("Layer pushed: " + layerPtr->GetName());
}

void MCEngine::LayerStack::PopLayer(const std::shared_ptr<Layer> &layerPtr)
{
    ENGINE_PROFILE_FUNCTION();

    auto &&it = std::find(m_Layers.begin(), m_Layers.end(), layerPtr);
    if (it != m_Layers.end())
    {
        (*it)->OnDetach();
        m_Layers.erase(it);

        LOG_ENGINE_INFO("Layer popped: " + layerPtr->GetName());
        return;
    }
    LOG_ENGINE_WARN("Layer not found: " + layerPtr->GetName());
}

void MCEngine::LayerStack::OnEvent(Event &event)
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &&it = m_Layers.rbegin(); it != m_Layers.rend(); it++)
    {
        if (event.IsHandled())
            break;

        (*it)->OnEvent(event);
    }
}

void MCEngine::LayerStack::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &&layer : m_Layers)
    {
        layer->OnUpdate(deltaTime);
    }
}

void MCEngine::LayerStack::Render()
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &&layer : m_Layers)
    {
        layer->OnRender();

        RendererCommand::DisableGammaCorrection();
        layer->OnImGuiRender();
        RendererCommand::EnableGammaCorrection();
    }
}