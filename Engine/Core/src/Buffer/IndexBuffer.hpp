#pragma once

#include "Buffer.hpp"

class IndexBuffer : public Buffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(const void *data, size_t size);
    IndexBuffer(const std::vector<uint32_t> &indices);
    virtual ~IndexBuffer() override;

    IndexBuffer(IndexBuffer &&other) noexcept;
    IndexBuffer &operator=(IndexBuffer &&other) noexcept;

    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetData(const void *data, size_t size) override;

protected:
    virtual void CreateBuffer(const void *data, size_t size) override;
};
