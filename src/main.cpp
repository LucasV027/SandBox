#include "imgui.h"

#include "Window.h"
#include "Renderer.h"
#include "Inputs.h"

int main() {
    GLFWContext context{};

    Renderer renderer;
    Window window;
    Inputs inputs;
    SandBox sandbox;

    window.Init(800, 600, "Sandbox", false);
    window.Bind();
    inputs.Init(window);
    renderer.Init(window, 800, 600);
    sandbox.Init(800, 600);

    auto HandleInputs = [&]() {
        if (inputs.IsMouseButtonPressed(0)) {
            auto pos = window.GetMousePos();
            sandbox.Create(static_cast<int>(pos.x), static_cast<int>(pos.y), Sand);
        }
    };

    while (!window.ShouldClose()) {
        renderer.Clear(0.2f, 0.2f, 0.2f);

        renderer.BeginFrame();
        renderer.Render(sandbox);
        ImGui::Begin("[INFO]");
        ImGui::Text("Sandbox");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::End();
        renderer.EndFrame();

        HandleInputs();

        sandbox.Update();

        window.SwapBuffers();
        inputs.Poll();
    }
}
