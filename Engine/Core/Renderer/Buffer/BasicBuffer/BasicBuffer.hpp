#pragma once

#include "pch.hpp"

namespace MCEngine
{

class BasicBuffer
{
public:
    BasicBuffer() = default;
    virtual ~BasicBuffer() = default;
    BasicBuffer(const BasicBuffer &) = delete;
    BasicBuffer &operator=(const BasicBuffer &) = delete;

    unsigned int GetRendererID() const { return m_RendererID; }
    int GetCount() const { return m_Count; }

public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetData(const void *data, size_t size) = 0;

protected:
    unsigned int m_RendererID = 0;
    int m_Count = 0;

protected:
    virtual void CreateBuffer(const void *data, size_t size) = 0;
};

} // namespace MCEngine