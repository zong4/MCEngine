#pragma once

#include "pch.hpp"

namespace MCEngine
{

class UniformBuffer
{
public:
    UniformBuffer(size_t size, unsigned int binding);
    ~UniformBuffer();

    UniformBuffer(const UniformBuffer &) = delete;
    UniformBuffer &operator=(const UniformBuffer &) = delete;
    UniformBuffer(UniformBuffer &&) = delete;
    UniformBuffer &operator=(UniformBuffer &&) = delete;

    unsigned int GetRendererID() const { return m_RendererID; }

public:
    void Bind() const;
    void Unbind() const;

    void SetData(const void *data, size_t size, size_t offset = 0);

private:
    unsigned int m_RendererID = 0;
    unsigned int m_Binding = 0;
};

} // namespace MCEngine