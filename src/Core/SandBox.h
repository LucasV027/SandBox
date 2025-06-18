#pragma once

#include <cstdint>
#include <vector>

#include "glm/vec3.hpp"

enum CellType : uint8_t {
    Air = 0,
    Sand = 1,
    Water = 2,
};

constexpr glm::vec3 PARTICLE_COLORS[256] = {
    {0.2f, 0.2f, 0.2f},    // Air
    {0.8f, 0.7f, 0.3f},    // Sand
    {0.13f, 0.53f, 0.85f}, // Water
};

class SandBox {
public:
    SandBox() = default;
    ~SandBox() = default;
    void Init(int width, int height);
    void Resize(int newWidth, int newHeight);

    void Update();
    void Create(int cx, int cy, CellType type, int radius = 1, float chance = 1.f);
    const CellType* Data() const;
    int Width() const;
    int Height() const;

private:
    bool InBounds(int x, int y) const;
    bool IsEmpty(int x, int y) const;
    int Index(int x, int y) const;

private:
    void UpdateSand(int x, int y);
    void UpdateWater(int x, int y);

private:
    int width, height;
    std::vector<CellType> buffer;
};
