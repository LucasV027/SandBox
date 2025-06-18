#pragma once

#include <filesystem>

#include "Core/SandBox.h"
#include "Application/Window.h"
#include "Graphics/Program.h"
#include "Graphics/Texture.h"
#include "Graphics/VertexArray.h"

class Renderer {
public:
    void Init(const Window& window);
    ~Renderer();

    void Resize(int newWidth, int newHeight);

    void BeginFrame() const;
    void Render(const SandBox& sandbox) const;
    void EndFrame() const;

    void SetZoom(float zoom) const;
    void SetOffset(const glm::vec2& offset) const;

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

    const std::filesystem::path mainFsPath = ASSETS_DIR "/shaders/main.frag";
    const std::filesystem::path mainVsPath = ASSETS_DIR "/shaders/main.vert";

    VertexArray vao;
    VertexBuffer vbo;
    Texture tex;
    Program program;
};
