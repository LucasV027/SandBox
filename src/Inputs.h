#pragma once

#include <unordered_map>

#include "glm/glm.hpp"

#include "Window.h"

class Inputs {
public:
    Inputs() = default;
    ~Inputs() = default;

    void Init(const Window& windowRef);
    void Poll();

    // Input
    bool IsKeyPressed(int key) const;
    bool IsMouseButtonPressed(int button) const;
    bool IsMouseFree() const;
    bool IsWindowResized() const;
    bool IsMouseScrolled() const;

    glm::dvec2 GetScrollOffset() const;

private:
    // Window resize
    bool resizeEvent = false;
    glm::ivec2 resizeSize;

    // Keyboard
    std::unordered_map<int, bool> keyStates;

    // Mouse
    std::unordered_map<int, bool> mouseStates;
    glm::dvec2 mouseScrollOffset;
    bool scrollEvent = false;
};
