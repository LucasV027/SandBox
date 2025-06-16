#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Window.h"
#include "Renderer.h"

int main() {
    GLFW::Init();

    Window window(800, 600, "Sandbox", true);
    window.Bind();

    Renderer renderer;
    renderer.Init(800, 600);

    SandBox sandbox(800, 600);
    sandbox.Create(40, 40, Sand);

    while (!window.ShouldClose()) {
        window.Clear(0.2f, 0.2f, 0.2f);

        renderer.Render(sandbox);

        window.SwapBuffers();

        glfwPollEvents();
    }

    window.Destroy();

    GLFW::Destroy();
}
