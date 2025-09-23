#pragma once

#include "pch.hpp"

namespace MCEngine
{

class Buffer
{
public:
    Buffer() = default;
    virtual ~Buffer() = default;
    Buffer(const Buffer &) = delete;
    Buffer &operator=(const Buffer &) = delete;

    unsigned int GetRendererID() const;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetData(const void *data, size_t size) = 0;

protected:
    unsigned int m_RendererID = 0;

protected:
    virtual void CreateBuffer(const void *data, size_t size) = 0;
};

} // namespace MCEngine