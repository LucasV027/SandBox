#include "imgui.h"

#include "Window.h"
#include "Renderer.h"
#include "Inputs.h"

int main() {
    GLFWContext context;

    Renderer renderer;
    Window window;
    Inputs inputs;
    SandBox sandbox;

    window.Init(800, 600, "Sandbox", true);
    window.Bind();
    inputs.Init(window);
    renderer.Init(window, 800, 600);
    sandbox.Init(800, 600);

    int radius = 1;
    float chance = 1.f;
    int currentType = Sand;
    const char* cellTypeNames[] = {"Air", "Sand", "Water"};

    auto HandleInputs = [&] {
        static int frame = 0;
        if (inputs.IsMouseButtonPressed(0)) {
            if (frame < 0) {
                const auto pos = window.GetMousePos();
                sandbox.Create(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<CellType>(currentType),
                               radius,
                               chance);
                frame = 10;
            }
            frame--;
        }

        if (inputs.IsWindowResized()) {
            const auto newSize = window.GetSize();
            renderer.Resize(newSize.x, newSize.y);
            sandbox.Resize(newSize.x, newSize.y);
        }
    };

    while (!window.ShouldClose()) {
        renderer.Clear(0.2f, 0.2f, 0.2f);

        renderer.BeginFrame();
        renderer.Render(sandbox);
        ImGui::Begin("[INFO]");
        ImGui::Text("Sandbox");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::SliderInt("Radius", &radius, 1, 100);
        ImGui::SliderFloat("Chance", &chance, 0.01f, 1.0f);
        ImGui::Combo("Element", &currentType, cellTypeNames, IM_ARRAYSIZE(cellTypeNames));
        ImGui::End();
        renderer.EndFrame();

        HandleInputs();

        sandbox.Update();

        window.SwapBuffers();
        inputs.Poll();
    }
}
