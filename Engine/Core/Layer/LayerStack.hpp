#pragma once

#include "Layer.hpp"

namespace MCEngine
{

class LayerStack
{
public:
    LayerStack() = default;
    ~LayerStack();

public:
    // Main loop
    void OnEvent(Event &event);
    void Update(float deltaTime);
    void Render();

    // Layer management
    void PushLayer(const std::shared_ptr<Layer> &layer);
    void PopLayer(const std::shared_ptr<Layer> &layer);

private:
    std::vector<std::shared_ptr<Layer>> m_Layers;
};

} // namespace MCEngine