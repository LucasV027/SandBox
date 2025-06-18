#pragma once

class Texture {
public:
    Texture();
    ~Texture();

    void Create(int width, int height, unsigned int format, unsigned int internalFormat);
    void Submit(const void* data) const;
    void Resize(int newWidth, int newHeight);

    void Bind(unsigned int slot = 0) const;
    void UnBind() const;

private:
    int width, height;
    unsigned int id;
    unsigned int type;
    unsigned int format;
    unsigned int internalFormat;
    int bpp;
};


