#include "Program.h"

#include <cassert>
#include <iostream>
#include <ranges>
#include <stdexcept>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.inl"

#include "Utils/File.h"

Program::~Program() {
    glDeleteProgram(shaderProgramme);
}

void Program::Create(const std::filesystem::path& vertexShader,
                     const std::filesystem::path& fragmentShader) {
    shaderProgramme = glCreateProgram();

    assert(vertexShader.extension() == ".vert");
    assert(fragmentShader.extension() == ".frag");

    const auto vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    glAttachShader(shaderProgramme, vs);
    glDeleteShader(vs);

    const auto fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);
    glAttachShader(shaderProgramme, fs);
    glDeleteShader(fs);

    glLinkProgram(shaderProgramme);
    glValidateProgram(shaderProgramme);

    GLint success;
    glGetProgramiv(shaderProgramme, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgramme, 512, nullptr, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }

    Bind();
}

void Program::LocateVariable(const std::string& name) {
    if (locations.contains(name)) {
        return;
    }

    int location = glGetUniformLocation(shaderProgramme, name.c_str());
    if (location == -1) {
        std::cerr << "(LocateVariable) Could not find uniform " << name << std::endl;
    } else {
        locations.insert({name, location});
    }
}

void Program::SetUniform1i(const std::string& name, const int v) const {
    if (locations.contains(name)) {
        glUniform1i(locations.at(name), v);
    } else {
        std::cerr << "(SetUniform1i) Could not find uniform " << name << std::endl;
    }
}

void Program::SetUniform1f(const std::string& name, const float v) const {
    if (locations.contains(name)) {
        glUniform1f(locations.at(name), v);
    } else {
        std::cerr << "(SetUniform1f) Could not find uniform " << name << std::endl;
    }
}

void Program::SetUniform2f(const std::string& name, float v1, float v2) const {
    if (locations.contains(name)) {
        glUniform2f(locations.at(name), v1, v2);
    } else {
        std::cerr << "(SetUniform2f) Could not find uniform " << name << std::endl;
    }
}

void Program::SetUniform3fv(const std::string& name, const int count, const float* v) const {
    if (locations.contains(name)) {
        glUniform3fv(locations.at(name), count, v);
    } else {
        std::cerr << "(SetUniform3fv) Could not find uniform " << name << std::endl;
    }
}

void Program::Bind() const {
    glUseProgram(shaderProgramme);
}

void Program::UnBind() const {
    glUseProgram(0);
}

unsigned int Program::CompileShader(const std::filesystem::path& path, const GLenum shaderType) {
    const std::string shaderSource = Utils::ReadFile(path);
    const char* shaderSourcePtr = shaderSource.c_str();

    const GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSourcePtr, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLint infoLength;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
        char infoLog[infoLength];
        glGetShaderInfoLog(shader, infoLength, nullptr, infoLog);
        throw std::runtime_error("Shader compilation failed for " + path.string() + " : " +
            std::string(infoLog));
    }

    return shader;
}



