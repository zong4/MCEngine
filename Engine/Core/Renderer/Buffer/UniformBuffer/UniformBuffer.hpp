#pragma once

#include "pch.hpp"

namespace MCEngine
{

class UniformBufferData
{
public:
    UniformBufferData(const void *data, size_t size, size_t offset) : m_Data(data), m_Size(size), m_Offset(offset) {}

    const void *GetData() const { return m_Data; }
    size_t GetSize() const { return m_Size; }
    size_t GetOffset() const { return m_Offset; }

private:
    const void *m_Data;
    size_t m_Size;
    size_t m_Offset;
};

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

    void SetData(const std::initializer_list<UniformBufferData> &dataList);

private:
    unsigned int m_RendererID = 0;
    unsigned int m_Binding = 0;
};

} // namespace MCEngine