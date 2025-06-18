#pragma once

class VertexBuffer {
public:
    VertexBuffer();
    ~VertexBuffer();

    void Load(const void* data, unsigned int size);

    void Bind() const;
    void Unbind() const;

private:
    unsigned int id;
};
