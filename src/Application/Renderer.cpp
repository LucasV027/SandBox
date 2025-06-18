#include "Renderer.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Graphics/DebugCallBack.h"
#include "Graphics/RenderCommand.h"

void Renderer::Init(const Window& window, const int width, const int height) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.Get(), true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
    ImGui::StyleColorsClassic();

    this->width = width;
    this->height = height;

    glm::vec3 colors[256] = {};
    colors[0] = {0.2f, 0.2f, 0.2f};    // Air
    colors[1] = {0.8f, 0.7f, 0.3f};    // Sand
    colors[2] = {0.13f, 0.53f, 0.85f}; // Water

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLErrorCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    RenderCommand::SetViewPort(0, 0, width, height);

    vao.Init();
    vbo.Load(QUAD, sizeof(QUAD));
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    vao.AddBuffer(vbo, layout);

    program.Create(mainVsPath, mainFsPath);
    program.LocateVariable("idTexture");
    program.LocateVariable("materialColors");
    program.LocateVariable("zoom");
    program.LocateVariable("offset");

    tex.Create(width, height, GL_RED_INTEGER, GL_R8UI);
    tex.Bind(0);
    program.SetUniform1i("idTexture", 0);
    program.SetUniform3fv("materialColors", 256, value_ptr(colors[0]));
    program.UnBind();
}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::Resize(const int newWidth, const int newHeight) {
    width = newWidth;
    height = newHeight;
    tex.Resize(width, height);
    RenderCommand::SetViewPort(0, 0, width, height);
}

void Renderer::BeginFrame() const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderCommand::Clear(0.1f, 0.1f, 0.1f);
}

void Renderer::Render(const SandBox& sandbox) const {
    tex.Bind(0);
    tex.Submit(sandbox.Data());
    RenderCommand::Draw(vao, 0, 6, program);
    tex.UnBind();
}

void Renderer::EndFrame() const {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Renderer::SetZoom(const float zoom) const {
    program.Bind();
    program.SetUniform1f("zoom", zoom);
    program.UnBind();
}

void Renderer::SetOffset(const glm::vec2& offset) const {
    program.Bind();
    program.SetUniform2f("offset", offset.x, offset.y);
    program.UnBind();
}


