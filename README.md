# Sandbox Visualizer

A 2D grid-based visual simulation app using OpenGL. It lets you create and interact with different types of cells (like
sand, water, etc.) with zooming, camera movement, and mouse input support.

## ✨ Features

- Real-time OpenGL rendering.
- Add cells with mouse input.
- Zoom and move the view.
- UI to select elements.
- Interactive controls:
    - Left click: draw cells.
    - Scroll: zoom.
    - Z, Q, S, D: move the view.
    - R: reset the view.

## 🧱 Dependencies

- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [glm](https://github.com/g-truc/glm)
- [ImGui](https://github.com/ocornut/imgui)

## 🛠️ Build Instructions

This project uses `CMake` with `FetchContent`.

```bash
mkdir build
cd build
cmake ..
make
```

The executable will be located in the `build/` directory.

## ✅ TODOs

- Add more particle types.
- Post-processing.
- Optimize the simulation.


