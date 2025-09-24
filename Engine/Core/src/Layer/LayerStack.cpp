#include "LayerStack.hpp"

MCEngine::LayerStack::~LayerStack()
{
    for (auto &layer : m_Layers)
    {
        layer->OnDetach();
    }
    m_Layers.clear();
}

void MCEngine::LayerStack::OnEvent(Event &e)
{
    for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); ++it)
    {
        (*it)->OnEvent(e);
        if (e.IsHandled())
        {
            break;
        }
    }
}

void MCEngine::LayerStack::Update()
{
    for (auto &layer : m_Layers)
    {
        layer->OnUpdate();
    }
}

void MCEngine::LayerStack::PushLayer(const std::shared_ptr<Layer> &layer)
{
    m_Layers.emplace_back(layer);
    layer->OnAttach();
}

void MCEngine::LayerStack::PopLayer(const std::shared_ptr<Layer> &layer)
{
    auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
    if (it != m_Layers.end())
    {
        (*it)->OnDetach();
        m_Layers.erase(it);
    }
}