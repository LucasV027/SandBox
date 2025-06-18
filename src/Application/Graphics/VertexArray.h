#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Init();
    void AddBuffer(const VertexBuffer& vbo, const VertexBufferLayout& layout) const;

    void Bind() const;
    void UnBind() const;

private:
    unsigned int vao;
};
