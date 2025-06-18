cmake_minimum_required(VERSION 3.15)
project(SandBox)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build (Debug, Release)" FORCE)
endif ()

add_executable(${PROJECT_NAME}
        src/main.cpp

        src/Application/Window.cpp
        src/Application/Window.h
        src/Application/Inputs.cpp
        src/Application/Inputs.h
        src/Application/Application.cpp
        src/Application/Application.h
        src/Application/Renderer.cpp
        src/Application/Renderer.h
        src/Application/Graphics/DebugCallBack.cpp
        src/Application/Graphics/DebugCallBack.h
        src/Application/Graphics/Shader.h
        src/Application/Graphics/Shader.cpp

        src/Core/SandBox.cpp
        src/Core/SandBox.h

        src/Utils/Timer.h
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
