#pragma once

#include <filesystem>

#include "SandBox.h"
#include "Window.h"

class Renderer {
public:
    void Init(const Window& window, int width, int height);
    ~Renderer();

    void Resize(int newWidth, int newHeight);

    void BeginFrame() const;
    void Render(const SandBox& sandbox) const;
    void EndFrame() const;

    void Clear(float r, float g, float b, float a = 1.0f) const;

private:
    static constexpr float QUAD[] = {
        // x, y, u, v
        -1.f, -1.f, 0.f, 1.f,
        1.f, -1.f, 1.f, 1.f,
        1.f, 1.f, 1.f, 0.f,

        -1.f, -1.f, 0.f, 1.f,
        1.f, 1.f, 1.f, 0.f,
        -1.f, 1.f, 0.f, 0.f
    };

    int width, height;
    unsigned int vao;
    unsigned int vbo;
    unsigned int tex;
    unsigned int program;

    const std::filesystem::path mainFsPath = ASSETS_DIR "/shaders/main.frag";
    const std::filesystem::path mainVsPath = ASSETS_DIR "/shaders/main.vert";
};
