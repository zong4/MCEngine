#pragma once

#include "Event/Event.hpp"

namespace MCEngine
{

class Layer
{
public:
    Layer(const std::string &name);
    virtual ~Layer() = default;

    inline const std::string &GetName() const { return m_Name; }

public:
    virtual void OnEvent(Event &event) = 0;

    virtual void OnAttach();
    virtual void OnUpdate() = 0;
    virtual void OnDetach();

private:
    std::string m_Name;
};

} // namespace MCEngine
