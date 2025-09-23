#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Object
{
public:
    Object() = default;
    virtual ~Object() = default;

    virtual void Update() = 0;
    virtual void Render() = 0;

protected:
    std::shared_ptr<VertexArray> m_VertexArray = nullptr;
};

} // namespace MCEngine
