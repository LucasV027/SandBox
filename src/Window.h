#pragma once

namespace GLFW {
    void Init();
    void Destroy();
}

class GLFWwindow;

class Window {
public:
    Window(int width, int height, const char* title, bool vsync = false);
    ~Window();

    GLFWwindow* Get() const;

    void Destroy();

    bool IsValid() const;
    static int Count();

    bool ShouldClose() const;
    void Bind() const;
    void SwapBuffers() const;

private:
    static int count;
    GLFWwindow* window = nullptr;
};
