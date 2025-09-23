#pragma once

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"

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
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray(VertexArray &&);
    VertexArray &operator=(VertexArray &&);

    void Bind() const;
    void Render() const;
    void Unbind() const;

    void SetIndexBuffer(IndexBuffer &&indexBuffer);
    void AddVertexBuffer(VertexBuffer &&vertexBuffer, const VertexAttribute &attribute);

private:
    unsigned int m_RendererID = 0;
    IndexBuffer m_IndexBuffer;
    std::vector<VertexBuffer> m_VertexBuffers;
    std::vector<VertexAttribute> m_VertexAttributes;
};

} // namespace MCEngine