#include "imgui.h"

#include "Window.h"
#include "Renderer.h"
#include "Inputs.h"
#include "Timer.h"

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

    Timer timer;
    Cooldown cd(TimeUnit::milliseconds(35));
    float lastUpdateTime = 0.f;

    auto HandleInputs = [&] {
        if (cd.Ok() && inputs.IsMouseButtonPressed(0)) {
            const auto pos = window.GetMousePos();
            sandbox.Create(static_cast<int>(pos.x),
                           static_cast<int>(pos.y),
                           static_cast<CellType>(currentType),
                           radius, chance);
            cd.Reset();
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
        timer.Reset();
        renderer.Render(sandbox);
        ImGui::Begin("[INFO]");
        ImGui::Text("Sandbox");
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        ImGui::Text("Render: %.1f ms", timer.Elapsed());
        ImGui::Text("Update: %.1f ms", lastUpdateTime);
        ImGui::SliderInt("Radius", &radius, 1, 100);
        ImGui::SliderFloat("Chance", &chance, 0.01f, 1.0f);
        ImGui::Combo("Element", &currentType, cellTypeNames, IM_ARRAYSIZE(cellTypeNames));
        ImGui::End();
        renderer.EndFrame();

        HandleInputs();

        timer.Reset();
        sandbox.Update();
        lastUpdateTime = timer.Elapsed().count();

        window.SwapBuffers();
        inputs.Poll();
    }
}
