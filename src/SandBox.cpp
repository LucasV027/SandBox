#include "SandBox.h"

#include <stdexcept>

SandBox::SandBox(const int width, const int height) : width(width), height(height) {
    if (width > 0 && height > 0) {
        cells.resize(width * height, Air);
    } else {
        throw std::invalid_argument("SandBox::Constructor : width and height must be greater than 0");
    }
}

void SandBox::Update() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            const auto idx = Index(x, y);
            const auto& cell = cells[idx];

            switch (cell) {
            case Air: { continue; }
            case Sand: {
                // TODO
                break;
            }
            default:
                break;
            }
        }
    }
}

void SandBox::Create(const int x, const int y, const CellType type) {
    cells[Index(x, y)] = type;
}

int SandBox::Index(const int x, const int y) const {
    return y * width + x;
}
