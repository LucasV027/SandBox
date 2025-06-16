#include <iostream>

#include "Window.h"
#include "Renderer.h"
#include "Inputs.h"

int main() {
    GLFW::Init();

    Window window(800, 600, "Sandbox", true);
    window.Bind();

    Inputs inputs(window);

    Renderer renderer;
    renderer.Init(800, 600);

    SandBox sandbox(800, 600);

    while (!window.ShouldClose()) {
        renderer.Clear(0.2f, 0.2f, 0.2f);
        renderer.Render(sandbox);

        if (inputs.IsMouseButtonPressed(0)) {
            auto pos = window.GetMousePos();
            sandbox.Create(static_cast<int>(pos.x), static_cast<int>(pos.y), Sand);
        }

        sandbox.Update();

        window.SwapBuffers();

        inputs.Poll();
    }

    window.Destroy();

    GLFW::Destroy();
}
