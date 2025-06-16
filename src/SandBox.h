#pragma once

#include <cstdint>
#include <vector>

enum CellType : uint8_t {
    Air = 0,
    Sand = 1,
};

class SandBox {
public:
    SandBox(int width, int height);
    ~SandBox() = default;

    void Update();
    void Create(int x, int y, CellType type);
    const CellType* Data() const;
    int Width() const;
    int Height() const;

private:
    void SwapBuffers();
    int Index(int x, int y) const;

private:
    int width, height;
    std::vector<CellType> buffers[2];
    int current = 0;
};
