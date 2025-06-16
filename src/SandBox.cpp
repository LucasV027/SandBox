#include "SandBox.h"

#include <stdexcept>

void SandBox::Init(const int width, const int height) {
    this->width = width;
    this->height = height;

    if (width > 0 && height > 0) {
        buffer.resize(width * height, Air);
    } else {
        throw std::invalid_argument("SandBox::Constructor : width and height must be greater than 0");
    }
}

void SandBox::Resize(const int newWidth, const int newHeight) {
    width = newWidth;
    height = newHeight;
    buffer.resize(width * height, Air);
}

void SandBox::Update() {
    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            const int idx = Index(x, y);
            auto& cell = buffer[idx];

            if (cell == Sand) {
                const int below = Index(x, y + 1);
                if (y + 1 < height) {
                    if (buffer[below] == Air) {
                        std::swap(cell, buffer[below]);
                    } else if (buffer[below - 1] == Air) {
                        std::swap(cell, buffer[below - 1]);
                    } else if (buffer[below + 1] == Air) {
                        std::swap(cell, buffer[below + 1]);
                    }
                }
            }
        }
    }
}

void SandBox::Create(const int cx, const int cy, const CellType type, const int radius) {
    for (int y = cy - radius; y < cy + radius; ++y) {
        for (int x = cx - radius; x < cx + radius; ++x) {
            if ((cx - x) * (cx - x) + (cy - y) * (cy - y) <= radius * radius) {
                if (InBounds(x, y)) {
                    buffer[Index(x, y)] = type;
                }
            }
        }
    }
}

const CellType* SandBox::Data() const { return buffer.data(); }
int SandBox::Width() const { return width; }
int SandBox::Height() const { return height; }
bool SandBox::InBounds(const int x, const int y) const { return x >= 0 && y >= 0 && x < width && y < height; }
bool SandBox::IsEmpty(const int x, const int y) const { return buffer[Index(x, y)] == Air; }
int SandBox::Index(const int x, const int y) const { return y * width + x; }
