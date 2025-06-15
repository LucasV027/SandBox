#include "Window.h"

#include <stdexcept>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void GLFW::Init() {
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");
}

void GLFW::Destroy() {
    glfwTerminate();
}

Window::Window(const int width, const int height, const char* title, const bool vsync) {
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
        throw std::runtime_error("Failed to create GLFW window");

    Bind();

    static bool gladInitialized = false;
    if (!gladInitialized) {
        gladInitialized = true;
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to load GLAD");
    }

    if (vsync) glfwSwapInterval(1);

    count++;
}

Window::~Window() {
    Destroy();
}

void Window::Destroy() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
        count--;
    }
}

bool Window::IsValid() const { return window != nullptr; }
int Window::Count() { return count; }
int Window::count = 0;

bool Window::ShouldClose() const { return window && glfwWindowShouldClose(window); }
void Window::Bind() const { glfwMakeContextCurrent(window); }
void Window::SwapBuffers() const { glfwSwapBuffers(window); }

void Window::Clear(const float r, const float g, const float b, const float a) const {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}
