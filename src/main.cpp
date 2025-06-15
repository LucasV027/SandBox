#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"

int main() {
    GLFW::Init();

    Window window(800, 600, "Sandbox", true);
    window.Bind();

    while (!window.ShouldClose()) {
        window.Clear(0.2f, 0.2f, 0.2f);
        window.SwapBuffers();

        glfwPollEvents();
    }

    window.Destroy();

    GLFW::Destroy();
}
