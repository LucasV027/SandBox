#pragma once

#include "glm/vec2.hpp"

#include "Window.h"
#include "Renderer.h"
#include "Inputs.h"
#include "Timer.h"

class Application {
public:
    Application();
    void Run();
    ~Application() = default;

private:
    void Events();
    void UI();

private:
    GLFWContext context;

    Renderer renderer;
    Window window;
    Inputs inputs;
    SandBox sandbox;

    int radius = 1;
    float chance = 1.f;
    int currentType = Sand;
    static constexpr const char* cellTypeNames[] = {"Air", "Sand", "Water"};

    Timer timer;
    Cooldown<TimeUnit::milliseconds> cd{TimeUnit::milliseconds(35)};
    float lastUpdateTime = 0.f;
    float lastRenderTime = 0.f;

    float zoom = 1.0f;
    glm::vec2 offset = {0.f, 0.f};
};
