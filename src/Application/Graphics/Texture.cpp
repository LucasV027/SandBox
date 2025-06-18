#include "Texture.h"

#include <stdexcept>

#include "glad/glad.h"

Texture::Texture() : width(0), height(0), id(0), type(0), format(0), internalFormat(0), bpp(0) {}

Texture::~Texture() {
    glDeleteTextures(1, &id);
}

void Texture::Create(const int width, const int height, const unsigned int format, const unsigned int internalFormat) {
    this->width = width;
    this->height = height;
    this->format = format;
    this->internalFormat = internalFormat;
    type = GL_TEXTURE_2D;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

    int channels = 0;
    switch (format) {
    case GL_RED:
    case GL_RED_INTEGER: channels = 1;
        break;
    case GL_RG: channels = 2;
        break;
    case GL_RGB: channels = 3;
        break;
    case GL_RGBA: channels = 4;
        break;
    default:
        throw std::runtime_error("Unsupported format");
    }

    // Only supported format
    constexpr int glUnsignedByte = 1;
    bpp = channels * glUnsignedByte;


    UnBind();
}

void Texture::Resize(const int newWidth, const int newHeight) {
    if (newWidth != this->width || newHeight != this->height) {
        glDeleteTextures(1, &id);
        Create(newWidth, newHeight, format, internalFormat);
    }
}

void Texture::Submit(const void* data) const {
    Bind();

    GLint prevAlignment;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &prevAlignment);

    int alignment = 1;
    if (bpp % 8 == 0) alignment = 8;
    else if (bpp % 4 == 0) alignment = 4;
    else if (bpp % 2 == 0) alignment = 2;

    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, format, GL_UNSIGNED_BYTE, data);

    glPixelStorei(GL_UNPACK_ALIGNMENT, prevAlignment);
}

void Texture::Bind(const unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(type, id);
}

void Texture::UnBind() const {
    glBindTexture(type, 0);
}
