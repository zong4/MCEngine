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
    Vector3 m_Position{0.0f, 0.0f, 0.0f};
    Vector3 m_Rotation{0.0f, 0.0f, 0.0f};
    Vector3 m_Scale{1.0f, 1.0f, 1.0f};

    std::shared_ptr<VertexArray> m_VertexArray = nullptr;
};

} // namespace MCEngine
