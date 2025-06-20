#pragma once

#include "glm/vec2.hpp"

class GLFWContext {
public:
    GLFWContext();
    ~GLFWContext();
};

class GLFWwindow;

class Window {
public:
    Window() = default;
    ~Window();

    void Init(int width, int height, const char* title, bool vsync = false);

    GLFWwindow* Get() const;
    void Destroy();

    bool IsValid() const;
    static int Count();

    bool ShouldClose() const;
    void Bind() const;
    void SwapBuffers() const;

    float AspectRatio() const;
    glm::ivec2 Size() const;
    glm::dvec2 MousePos() const;
    glm::vec2 MousePosRelative() const;

private:
    static int count;
    GLFWwindow* window = nullptr;
};
