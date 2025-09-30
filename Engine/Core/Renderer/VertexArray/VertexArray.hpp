#pragma once

#include "Renderer/Buffer/BasicBuffer/IndexBuffer.hpp"
#include "Renderer/Buffer/BasicBuffer/VertexBuffer.hpp"

namespace MCEngine
{

struct VertexAttribute
{
    unsigned int location;
    unsigned int count;
    unsigned int type;
    bool normalized;
    size_t stride;
    const void *offset;
};

class VertexArray
{
public:
    VertexArray(VertexBuffer &&vertexBuffer, const std::vector<VertexAttribute> &attributes,
                IndexBuffer &&indexBuffer = IndexBuffer(nullptr, 0), int count = 1);
    ~VertexArray();

    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray(VertexArray &&);
    VertexArray &operator=(VertexArray &&);

    unsigned int GetRendererID() const { return m_RendererID; }

    void SetVertexBuffer(VertexBuffer &&vertexBuffer, const std::vector<VertexAttribute> &attributes);
    void SetIndexBuffer(IndexBuffer &&indexBuffer);
    void SetCount(int count) { m_Count = count; }

public:
    void Render() const;

private:
    unsigned int m_RendererID = 0;
    VertexBuffer m_VertexBuffer;
    int m_AttributeCount = 0;
    IndexBuffer m_IndexBuffer;
    int m_Count = 1;

protected:
    void Bind() const;
    void Unbind() const;

    void SetVertexAttributes(const std::vector<VertexAttribute> &attributes);
};

} // namespace MCEngine