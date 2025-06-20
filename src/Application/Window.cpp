#include "Window.h"

#include <stdexcept>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

GLFWContext::GLFWContext() {
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

GLFWContext::~GLFWContext() {
    glfwTerminate();
}

void Window::Init(const int width, const int height, const char* title, const bool vsync) {
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

    glfwSwapInterval(vsync ? 1 : 0);

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

float Window::AspectRatio() const {
    const auto size = Size();
    return static_cast<float>(size.x) / static_cast<float>(size.y);
}

glm::ivec2 Window::Size() const {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return {width, height};
}

glm::dvec2 Window::MousePos() const {
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return {x, y};
}

glm::vec2 Window::MousePosRelative() const {
    const auto size = Size();
    const auto pos = MousePos();
    return {pos.x / size.x, pos.y / size.y};
}


