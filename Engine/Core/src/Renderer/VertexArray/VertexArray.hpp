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
    VertexArray(VertexBuffer &&vertexBuffer, const std::vector<VertexAttribute> &attributes,
                IndexBuffer &&indexBuffer = IndexBuffer(nullptr, 0));
    ~VertexArray();

    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray(VertexArray &&);
    VertexArray &operator=(VertexArray &&);

    void SetVertexBuffer(VertexBuffer &&vertexBuffer, const std::vector<VertexAttribute> &attributes);
    void SetIndexBuffer(IndexBuffer &&indexBuffer);

public:
    void Render() const;

private:
    unsigned int m_RendererID = 0;
    VertexBuffer m_VertexBuffer;
    IndexBuffer m_IndexBuffer;
    int m_AttributeCount = 0;

protected:
    void Bind() const;
    void Unbind() const;

    void SetVertexAttributes(const std::vector<VertexAttribute> &attributes);
};

} // namespace MCEngine