#pragma once

#include "Event/Event.hpp"

namespace MCEngine
{

class Layer
{
public:
    Layer(const std::string &name) : m_Name(name) {}
    virtual ~Layer() = default;

    inline const std::string &GetName() const { return m_Name; }

    virtual void OnAttach() = 0;
    virtual void OnDetach() = 0;

public:
    virtual void OnEvent(Event &event) = 0;
    virtual void OnUpdate() = 0;

private:
    std::string m_Name;
};

} // namespace MCEngine
