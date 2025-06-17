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
    // TODO Better resizing algorithm
    buffer.resize(width * height, Air);
}

void SandBox::Update() {
    for (int y = height - 1; y >= 0; --y) {
        for (int x = width - 1; x >= 0; --x) {
            const auto& cell = buffer[Index(x, y)];

            // clang-format off
            switch (cell) {
            case Air:                       continue;
            case Sand: UpdateSand(x, y);    break;
            case Water: UpdateWater(x, y);  break;
            default:                        continue;
            }
            // clang-format on
        }
    }
}

void SandBox::Create(const int cx, const int cy, const CellType type, const int radius, const float chance) {
    for (int y = cy - radius; y < cy + radius; ++y) {
        for (int x = cx - radius; x < cx + radius; ++x) {
            if ((cx - x) * (cx - x) + (cy - y) * (cy - y) <= radius * radius) {
                if (InBounds(x, y) && (rand() / (RAND_MAX + 1.)) < chance) {
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

void SandBox::UpdateSand(const int x, const int y) {
    if (y == height - 1) return;
    const auto idx = Index(x, y);

    // Below
    if (buffer[Index(x, y + 1)] == Air) {
        std::swap(buffer[idx], buffer[Index(x, y + 1)]);
        return;
    }

    // Below-left
    if (x > 0 && buffer[Index(x - 1, y + 1)] == Air) {
        std::swap(buffer[idx], buffer[Index(x - 1, y + 1)]);
        return;
    }

    // Below-right
    if (x < width - 1 && buffer[Index(x + 1, y + 1)] == Air) {
        std::swap(buffer[idx], buffer[Index(x + 1, y + 1)]);
        return;
    }
}

void SandBox::UpdateWater(const int x, const int y) {
    const auto idx = Index(x, y);

    // Below
    if (y < height - 1 && buffer[Index(x, y + 1)] == Air) {
        std::swap(buffer[idx], buffer[Index(x, y + 1)]);
        return;
    }

    // Below-left
    if (x > 0 && y < height - 1 && buffer[Index(x - 1, y + 1)] == Air) {
        std::swap(buffer[idx], buffer[Index(x - 1, y + 1)]);
        return;
    }

    // Below-right
    if (x < width - 1 && y < height - 1 && buffer[Index(x + 1, y + 1)] == Air) {
        std::swap(buffer[idx], buffer[Index(x + 1, y + 1)]);
        return;
    }

    // Left
    if (x > 0 && buffer[Index(x - 1, y)] == Air) {
        std::swap(buffer[idx], buffer[Index(x - 1, y)]);
        return;
    }

    // Right
    if (x < width - 1 && buffer[Index(x + 1, y)] == Air) {
        std::swap(buffer[idx], buffer[Index(x + 1, y)]);
        return;
    }
}
