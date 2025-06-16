#pragma once

#include <cstdint>
#include <vector>

enum CellType : uint8_t {
    Air = 0,
    Sand = 1,
};

class SandBox {
public:
    SandBox() = default;
    ~SandBox() = default;
    void Init(int width, int height);
    void Resize(int newWidth, int newHeight);

    void Update();
    void Create(int cx, int cy, CellType type, int radius = 1);
    const CellType* Data() const;
    int Width() const;
    int Height() const;

private:
    bool InBounds(int x, int y) const;
    bool IsEmpty(int x, int y) const;
    int Index(int x, int y) const;

private:
    int width, height;
    std::vector<CellType> buffer;
};
