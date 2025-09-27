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

void MCEngine::LayerStack::OnEvent(Event &eventRef)
{
    ENGINE_PROFILE_FUNCTION();

    for (auto it = rbegin(); it != rend(); ++it)
    {
        if (eventRef.IsHandled())
        {
            break;
        }
        (*it)->OnEvent(eventRef);
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

void MCEngine::LayerStack::Render(float deltaTime)
{
    ENGINE_PROFILE_FUNCTION();

    for (auto &layer : m_Layers)
    {
        layer->OnRender();
        layer->OnImGuiRender(deltaTime);
    }
}

void MCEngine::LayerStack::PushLayer(const std::shared_ptr<Layer> &layerPtrRef)
{
    ENGINE_PROFILE_FUNCTION();

    m_Layers.emplace_back(layerPtrRef);
    layerPtrRef->OnAttach();

    LOG_ENGINE_INFO("Layer pushed: " + layerPtrRef->GetNameRef());
}

void MCEngine::LayerStack::PopLayer(const std::shared_ptr<Layer> &layerPtrRef)
{
    ENGINE_PROFILE_FUNCTION();

    auto it = std::find(m_Layers.begin(), m_Layers.end(), layerPtrRef);
    if (it != m_Layers.end())
    {
        (*it)->OnDetach();
        m_Layers.erase(it);

        LOG_ENGINE_INFO("Layer popped: " + layerPtrRef->GetNameRef());
    }
    else
    {
        LOG_ENGINE_WARN("Layer not found: " + layerPtrRef->GetNameRef());
    }
}