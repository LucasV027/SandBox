#include "Shader.h"

#include "glad/glad.h"

unsigned int Shader::CreateShader(const std::filesystem::path& path, unsigned int shaderType) {
    const std::string shaderSource = ReadFile(path);
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

unsigned int Shader::CreateProgram(unsigned int vertexShader, unsigned int fragmentShader) {
    const auto program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);
    glValidateProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        throw std::runtime_error("Shader program linking failed: " + std::string(infoLog));
    }

    return program;
}

std::string Shader::ReadFile(const std::filesystem::path& filePath) {
    std::ifstream fileStream(filePath, std::ios::ate | std::ios::binary);

    if (!fileStream.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath.string());
    }

    std::string buffer(fileStream.tellg(), '\0');

    fileStream.seekg(0, std::ios::beg);

    if (!fileStream.read(&buffer[0], buffer.size())) {
        throw std::runtime_error("Error reading file: " + filePath.string());
    }

    return std::move(buffer);
}
