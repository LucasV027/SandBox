#include "SandBox.h"

#include <stdexcept>

SandBox::SandBox(const int width, const int height) : width(width), height(height) {
    if (width > 0 && height > 0) {
        buffers[0].resize(width * height, Air);
        buffers[1].resize(width * height, Air);
    } else {
        throw std::invalid_argument("SandBox::Constructor : width and height must be greater than 0");
    }
}

void SandBox::Update() {
    const auto& src = buffers[current];
    auto& dst = buffers[1 - current];
    // Clear destination buffer (Air everywhere)
    std::fill(dst.begin(), dst.end(), Air);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const int idx = Index(x, y);
            CellType cell = src[idx];

            if (cell == Sand) {
                int below = Index(x, y + 1);
                if (y + 1 < height && src[below] == Air && dst[below] == Air) {
                    dst[below] = Sand;
                } else {
                    dst[idx] = Sand;
                }
            }
        }
    }

    SwapBuffers();
}

void SandBox::Create(const int x, const int y, const CellType type) {
    if (x < 0 || x >= width || y < 0 || y >= height) return;
    buffers[current][Index(x, y)] = type;
}

const CellType* SandBox::Data() const { return buffers[current].data(); }
int SandBox::Width() const { return width; }
int SandBox::Height() const { return height; }
void SandBox::SwapBuffers() { current = 1 - current; }
int SandBox::Index(const int x, const int y) const { return y * width + x; }
