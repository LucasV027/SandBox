#include "VertexBufferLayout.h"

#include "glad/glad.h"

template <>
void VertexBufferLayout::Push<float>(unsigned int count) {
    elements.emplace_back(GL_FLOAT, count, GL_FALSE, sizeof(float));
    stride += count * sizeof(float);
}

template <>
void VertexBufferLayout::Push<unsigned int>(unsigned int count) {
    elements.emplace_back(GL_UNSIGNED_INT, count, GL_FALSE, sizeof(unsigned int));
    stride += count * sizeof(unsigned int);
}
