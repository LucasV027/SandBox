#pragma once

#include <filesystem>

#include "SandBox.h"

class Renderer {
public:
    void Init(int width, int height);
    void Render(const SandBox& sandbox) const;
    ~Renderer();

private:
    static constexpr float QUAD[] = {
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,

        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    int width, height;
    unsigned int vao;
    unsigned int vbo;
    unsigned int tex;
    unsigned int program;

    const std::filesystem::path mainFsPath = ASSETS_DIR "/shaders/main.frag";
    const std::filesystem::path mainVsPath = ASSETS_DIR "/shaders/main.vert";
};
