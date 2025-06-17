#include "Application.h"

#include <iostream>

#include "imgui.h"

Application::Application() {
    window.Init(800, 600, "Sandbox", true);
    window.Bind();
    inputs.Init(window);
    renderer.Init(window, 800, 600);
    sandbox.Init(800, 600);
}

void Application::Run() {
    while (!window.ShouldClose()) {
        renderer.Clear(0.2f, 0.2f, 0.2f);

        renderer.BeginFrame();
        timer.Reset();
        renderer.Render(sandbox);
        lastRenderTime = timer.Elapsed();
        UI();
        renderer.EndFrame();

        Events();

        timer.Reset();
        sandbox.Update();
        lastUpdateTime = timer.Elapsed();

        window.SwapBuffers();
        inputs.Poll();
    }
}

void Application::Events() {
    if (cd.Ok() && inputs.IsMouseButtonPressed(0)) {
        const auto pos = window.GetMousePos();
        sandbox.Create(static_cast<int>(pos.x),
                       static_cast<int>(pos.y),
                       static_cast<CellType>(currentType),
                       radius, chance);

        std::cout << pos.x << ", " << pos.y << std::endl;
        cd.Reset();
    }


    if (inputs.IsWindowResized()) {
        const auto newSize = window.GetSize();
        renderer.Resize(newSize.x, newSize.y);
        sandbox.Resize(newSize.x, newSize.y);
    }
}

void Application::UI() {
    ImGui::Begin("[INFO]");
    ImGui::Text("Sandbox");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Render: %.1f ns", lastRenderTime);
    ImGui::Text("Update: %.1f ms", lastUpdateTime);
    ImGui::SliderInt("Radius", &radius, 1, 100);
    ImGui::SliderFloat("Chance", &chance, 0.01f, 1.0f);
    ImGui::Combo("Element", &currentType, cellTypeNames, IM_ARRAYSIZE(cellTypeNames));
    ImGui::End();
}
