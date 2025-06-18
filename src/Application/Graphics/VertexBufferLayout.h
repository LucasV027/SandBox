#pragma once

#include <vector>

struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned int normalized;
    unsigned int typeSize;
};

class VertexBufferLayout {
public:
    VertexBufferLayout() : stride(0) {}

    ~VertexBufferLayout() = default;

    unsigned int GetStride() const { return stride; }
    const std::vector<VertexBufferElement>& GetElements() const { return elements; }

    template <typename T>
    void Push(unsigned int count);

private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
};

template <>
void VertexBufferLayout::Push<float>(unsigned int count);

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count);
