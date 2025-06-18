#pragma once

class IndexBuffer {
public:
    IndexBuffer();
    ~IndexBuffer();

    void Load(const unsigned int* data, unsigned int count);

    void Bind() const;
    void UnBind() const;

    unsigned int GetCount() const;

private:
    unsigned int id;
    unsigned int count;
};
