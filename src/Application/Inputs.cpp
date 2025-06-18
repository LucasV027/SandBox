#include "Inputs.h"

#include "GLFW/glfw3.h"

#include "imgui.h"

void Inputs::Init(const Window& windowRef) {
    glfwSetWindowUserPointer(windowRef.Get(), this);

    resizeSize = windowRef.GetSize();

    glfwSetWindowSizeCallback(
        windowRef.Get(), [](GLFWwindow* window, const int width, const int height) {
            if (auto* _this = static_cast<Inputs*>(glfwGetWindowUserPointer(window))) {
                _this->resizeSize.x = width;
                _this->resizeSize.y = height;
                _this->resizeEvent = true;
            }
        });

    glfwSetKeyCallback(
        windowRef.Get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            if (auto* _this = static_cast<Inputs*>(glfwGetWindowUserPointer(window))) {
                if (action == GLFW_PRESS) {
                    _this->keyStates[key] = true;
                } else if (action == GLFW_RELEASE) {
                    _this->keyStates[key] = false;
                }
            }
        });

    glfwSetMouseButtonCallback(
        windowRef.Get(), [](GLFWwindow* window, int button, int action, int mods) {
            if (auto* _this = static_cast<Inputs*>(glfwGetWindowUserPointer(window))) {
                if (action == GLFW_PRESS) {
                    _this->mouseStates[button] = true;
                } else if (action == GLFW_RELEASE) {
                    _this->mouseStates[button] = false;
                }
            }
        });

    glfwSetScrollCallback(windowRef.Get(), [](GLFWwindow* window, double xOffset, double yOffset) {
        if (auto* _this = static_cast<Inputs*>(glfwGetWindowUserPointer(window))) {
            _this->scrollEvent = true;
            _this->mouseScrollOffset.x = xOffset;
            _this->mouseScrollOffset.y = yOffset;
        }
    });
}

void Inputs::Poll() {
    resizeEvent = false;
    scrollEvent = false;
    glfwPollEvents();
}

bool Inputs::IsKeyPressed(const int key) const {
    if (!keyStates.contains(key))
        return false;
    return keyStates.at(key);
}

bool Inputs::IsMouseButtonPressed(const int button) const {
    if (!mouseStates.contains(button))
        return false;
    return IsMouseFree() && mouseStates.at(button);
}

bool Inputs::IsMouseFree() const { return !ImGui::GetIO().WantCaptureMouse; }

bool Inputs::IsWindowResized() const { return resizeEvent; }

bool Inputs::IsMouseScrolled() const { return IsMouseFree() && scrollEvent; }

glm::dvec2 Inputs::GetScrollOffset() const { return mouseScrollOffset; }


