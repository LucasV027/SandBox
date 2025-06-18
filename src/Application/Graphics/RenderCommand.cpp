#include "RenderCommand.h"

#include "glad/glad.h"

void RenderCommand::Clear(const float r, const float g, const float b, const float a) {
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderCommand::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Program& program) {
    vao.Bind();
    ibo.Bind();
    program.Bind();
    glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void RenderCommand::Draw(const VertexArray& vao, const int first, const int count,
                         const Program& program) {
    vao.Bind();
    program.Bind();
    glDrawArrays(GL_TRIANGLES, first, count);
}

void RenderCommand::SetViewPort(const int x, const int y, const int width, const int height) {
    glViewport(x, y, width, height);
}

void RenderCommand::SetDepthTest(const bool enabled) {
    if (enabled) {
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    } else
        glDisable(GL_DEPTH_TEST);
}

void RenderCommand::SetCullFace(const bool enabled) {
    if (enabled) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

void RenderCommand::SetWireframe(const bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}
