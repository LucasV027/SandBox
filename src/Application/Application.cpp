#include "Application.h"

#include <iostream>

#include "imgui.h"

Application::Application() {
    constexpr int width = 800;
    constexpr int height = 600;
    window.Init(width, height, "Sandbox", true);
    window.Bind();
    inputs.Init(window);
    renderer.Init(window);
    renderer.SetZoom(zoom);
    renderer.SetOffset(offset);
    sandbox.Init(width, height);
}

void Application::Run() {
    while (!window.ShouldClose()) {
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
    // LEFT CLICK
    if (cd.Ok() && inputs.IsMouseButtonPressed(0)) {
        const auto pos = window.MousePosRelative();

        // [ -1 ; 1 ]
        const float ndcX = pos.x * 2.0f - 1.0f;
        const float ndcY = 1.0f - pos.y * 2.0f;

        const float worldX = (ndcX - offset.x) / zoom;
        const float worldY = (ndcY - offset.y) / zoom;

        const int simX = static_cast<int>((worldX + 1.0f) * 0.5f * sandbox.Width());
        const int simY = static_cast<int>((1.0f - worldY) * 0.5f * sandbox.Height());

        sandbox.Create(simX, simY, static_cast<CellType>(currentType), radius, chance);

        cd.Reset();
    }

    if (inputs.IsMouseScrolled()) {
        const glm::vec2 fixedWorldPoint = (-offset) / zoom;

        const auto scrollOffset = inputs.GetScrollOffset();
        zoom *= scrollOffset.y > 0 ? 1.1f : 0.9f;
        zoom = std::clamp(zoom, 0.1f, 10.0f);
        renderer.SetZoom(zoom);

        offset = -fixedWorldPoint * zoom;
        renderer.SetOffset(offset);
    }

    // S
    if (inputs.IsKeyPressed(83)) {
        offset.y += 0.01;
        renderer.SetOffset(offset);
    }
    // Z
    if (inputs.IsKeyPressed(87)) {
        offset.y -= 0.01;
        renderer.SetOffset(offset);
    }
    // Q
    if (inputs.IsKeyPressed(65)) {
        offset.x += 0.01;
        renderer.SetOffset(offset);
    }
    // D
    if (inputs.IsKeyPressed(68)) {
        offset.x -= 0.01;
        renderer.SetOffset(offset);
    }

    // R -> Reset
    if (inputs.IsKeyPressed(82)) {
        offset = {0, 0};
        zoom = 1.f;
        renderer.SetZoom(zoom);
        renderer.SetOffset(offset);
    }

    if (inputs.IsWindowResized()) {
        const auto newSize = window.Size();
        renderer.Resize(newSize.x, newSize.y);
        sandbox.Resize(newSize.x, newSize.y);
    }
}

void Application::UI() {
    ImGui::Begin("[INFO]");
    ImGui::Text("Window %d * %d", window.Size().x, window.Size().y);
    ImGui::Text("Sandbox %d * %d", sandbox.Width(), sandbox.Height());
    ImGui::NewLine();
    ImGui::Text("Zoom: %.1f", zoom);
    ImGui::Text("Offset: (%.1f ; %.1f)", offset.x, offset.y);
    ImGui::NewLine();
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Render: %.1f ns", lastRenderTime);
    ImGui::Text("Update: %.1f ms", lastUpdateTime);
    ImGui::NewLine();
    ImGui::SliderInt("Radius", &radius, 1, 100);
    ImGui::SliderFloat("Chance", &chance, 0.01f, 1.0f);
    ImGui::Combo("Element", &currentType, cellTypeNames, IM_ARRAYSIZE(cellTypeNames));
    ImGui::End();
}
