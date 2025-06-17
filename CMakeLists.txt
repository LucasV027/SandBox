cmake_minimum_required(VERSION 3.15)
project(SandBox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug, Release)" FORCE)
endif ()

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Window.cpp
        src/Window.h
        src/Inputs.cpp
        src/Inputs.h
        src/SandBox.cpp
        src/SandBox.h
        src/Renderer.cpp
        src/Renderer.h
        src/DebugCallBack.cpp
        src/DebugCallBack.h
        src/Shader.h
        src/Shader.cpp
        src/Timer.h
        src/Application.cpp
        src/Application.h
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets")

include(Dependencies.cmake)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glad
        glfw
        glm
        imgui
)
