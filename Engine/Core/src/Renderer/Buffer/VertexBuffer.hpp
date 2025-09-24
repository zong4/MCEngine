#pragma once

#include "Buffer.hpp"

namespace MCEngine
{

class VertexBuffer : public Buffer
{
public:
    VertexBuffer(const void *data, size_t size);
    VertexBuffer(const std::vector<float> &vertices);
    virtual ~VertexBuffer() override;

    VertexBuffer(VertexBuffer &&other) noexcept;
    VertexBuffer &operator=(VertexBuffer &&other) noexcept;

public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetData(const void *data, size_t size) override;

protected:
    virtual void CreateBuffer(const void *data, size_t size) override;
};

} // namespace MCEngine