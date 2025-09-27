#pragma once

#include "Buffer.hpp"

namespace MCEngine
{

class IndexBuffer : public Buffer
{
public:
    // IndexBuffer() = default;
    IndexBuffer(const void *data, size_t size);
    IndexBuffer(const std::vector<uint32_t> &indices);
    virtual ~IndexBuffer() override;

    IndexBuffer(IndexBuffer &&other);
    IndexBuffer &operator=(IndexBuffer &&other);

public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetData(const void *data, size_t size) override;

protected:
    virtual void CreateBuffer(const void *data, size_t size) override;
};

} // namespace MCEngine
