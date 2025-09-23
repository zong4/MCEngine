#pragma once

#include "Object.hpp"

namespace MCEngine
{

class Camera : public Object
{
public:
    Camera();
    virtual ~Camera() override = default;

    void Update() override;
    void Render() override;

private:
    void SetupCamera();
};

} // namespace MCEngine