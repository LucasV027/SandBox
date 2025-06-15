#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

int main() {
    GLFW::Init();

    Window window(800, 600, "Sandbox1", true);
    window.Bind();

    while (!window.ShouldClose()) {
        glClearColor(1.0f, 0.0f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        window.SwapBuffers();

        glfwPollEvents();
    }

    window.Destroy();

    GLFW::Destroy();
}
