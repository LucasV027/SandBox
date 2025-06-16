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

    while (!window.ShouldClose()) {
        renderer.Clear(0.2f, 0.2f, 0.2f);
        renderer.Render(sandbox);

        window.SwapBuffers();

        glfwPollEvents();
    }

    window.Destroy();

    GLFW::Destroy();
}
