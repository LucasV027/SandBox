#include "Renderer.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Graphics/DebugCallBack.h"
#include "Graphics/RenderCommand.h"

void Renderer::Init(const Window& window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.Get(), true);
    ImGui_ImplOpenGL3_Init("#version 450 core");
    ImGui::StyleColorsClassic();

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLErrorCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    RenderCommand::SetViewPort(0, 0, window.GetSize().x, window.GetSize().y);

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

    tex.Create(window.GetSize().x, window.GetSize().y, GL_RED_INTEGER, GL_R8UI);
    tex.Bind(0);
    program.SetUniform1i("idTexture", 0);
    program.SetUniform3fv("materialColors", 256, value_ptr(PARTICLE_COLORS[0]));
    program.UnBind();
}

Renderer::~Renderer() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::Resize(const int newWidth, const int newHeight) {
    tex.Resize(newWidth, newHeight);
    RenderCommand::SetViewPort(0, 0, newWidth, newHeight);
}

void Renderer::BeginFrame() const {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    RenderCommand::Clear(0.1f, 0.1f, 0.1f);
}

void Renderer::Render(const SandBox& sandbox) const {
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


