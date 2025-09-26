#include "LayerStack.hpp"

MCEngine::LayerStack::~LayerStack()
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &layer : m_Layers)
    {
        layer->OnDetach();
    }
    m_Layers.clear();
}

void MCEngine::LayerStack::OnEvent(Event &e)
{
    ENGINE_PROFILE_FUNCTION();

    for (auto it = rbegin(); it != rend(); ++it)
    {
        if (e.IsHandled())
        {
            break;
        }
        (*it)->OnEvent(e);
    }
}

void MCEngine::LayerStack::Update(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &layer : m_Layers)
    {
        layer->OnUpdate(deltaTime);
    }
}

void MCEngine::LayerStack::PushLayer(const std::shared_ptr<Layer> &layer)
{
    ENGINE_PROFILE_FUNCTION();

    m_Layers.emplace_back(layer);
    layer->OnAttach();

    LOG_ENGINE_INFO("Layer pushed: " + layer->GetName());
}

void MCEngine::LayerStack::PopLayer(const std::shared_ptr<Layer> &layer)
{
    ENGINE_PROFILE_FUNCTION();

    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        (*it)->OnDetach();
        m_Layers.erase(it);

        LOG_ENGINE_INFO("Layer popped: " + layer->GetName());
    }
    else
    {
        LOG_ENGINE_WARN("Layer not found: " + layer->GetName());
    }
}