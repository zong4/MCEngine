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
    void OnEvent(Event &event);
    void Update(float deltaTime);
    void Render(float deltaTime);

    void PushLayer(const std::shared_ptr<Layer> &layerPtr);
    void PopLayer(const std::shared_ptr<Layer> &layerPtr);

private:
    std::vector<std::shared_ptr<Layer>> m_Layers;

private:
    std::vector<std::shared_ptr<Layer>>::iterator begin() { return m_Layers.begin(); }
    std::vector<std::shared_ptr<Layer>>::iterator end() { return m_Layers.end(); }
    std::vector<std::shared_ptr<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
    std::vector<std::shared_ptr<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }
};

} // namespace MCEngine