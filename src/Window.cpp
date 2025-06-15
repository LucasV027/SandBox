#include "Window.h"

#include <stdexcept>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void GLFW::Init() {
    if (!glfwInit())
        throw std::runtime_error("Failed to initialize GLFW");

    glfwSetErrorCallback([](const int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    });

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
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

GLFWwindow* Window::Get() const { return window; }

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
