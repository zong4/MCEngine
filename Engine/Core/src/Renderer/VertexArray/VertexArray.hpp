#pragma once

#include "Renderer/Buffer/IndexBuffer.hpp"
#include "Renderer/Buffer/VertexBuffer.hpp"

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
    VertexArray(IndexBuffer &&indexBuffer, VertexBuffer &&vertexBuffer, const VertexAttribute &attribute);
    ~VertexArray();

    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray(VertexArray &&);
    VertexArray &operator=(VertexArray &&);

    void SetIndexBuffer(IndexBuffer &&indexBuffer);
    void SetVertexBuffer(VertexBuffer &&vertexBuffer, const VertexAttribute &attribute);

public:
    void Render() const;

private:
    unsigned int m_RendererID = 0;

    IndexBuffer m_IndexBuffer;
    VertexBuffer m_VertexBuffer;

protected:
    void Bind() const;
    void Unbind() const;
};

} // namespace MCEngine