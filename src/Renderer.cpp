#include "Renderer.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

#include "DebugCallBack.h"
#include "Shader.h"

void Renderer::Init(const int width, const int height) {
    this->width = width;
    this->height = height;

    glm::vec3 colors[256] = {};
    colors[0] = {0.2f, 0.2f, 0.2f};
    colors[1] = {0.8f, 0.7f, 0.3f};
    colors[2] = {0.1f, 0.3f, 0.8f};
    colors[3] = {0.6f, 0.2f, 0.1f};

    GLint flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLErrorCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    glViewport(0, 0, width, height);

    // VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), QUAD, GL_STATIC_DRAW);

    // VAO Layout
    // Position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // TexCoord
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R8UI, width, height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);

    // Shaders
    const auto vs = Shader::CreateShader(mainVsPath, GL_VERTEX_SHADER);
    const auto fs = Shader::CreateShader(mainFsPath, GL_FRAGMENT_SHADER);
    program = Shader::CreateProgram(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(program);
    glUniform3fv(glGetUniformLocation(program, "materialColors"), 256, glm::value_ptr(colors[0]));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(glGetUniformLocation(program, "idTexture"), 0);
    glUseProgram(0);
}

void Renderer::Render(const SandBox& sandbox) const {
    glUseProgram(program);
    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, sandbox.Width(), sandbox.Height(), GL_RED_INTEGER, GL_UNSIGNED_BYTE,
                    sandbox.Data());
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, &tex);
    glDeleteProgram(program);
}
