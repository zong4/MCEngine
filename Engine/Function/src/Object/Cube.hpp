#pragma once

#include "Object.hpp"

namespace MCEngine
{

class Cube : public Object
{
public:
    Cube(float size);
    virtual ~Cube() override = default;

    void Update() override;
    void Render() override;

private:
    float m_size;
    std::vector<float> m_vertices;
    unsigned int m_VAO, m_VBO;

private:
    void SetupCube();
};

} // namespace MCEngine