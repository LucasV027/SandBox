#pragma once

#include <filesystem>
#include <fstream>

class Shader {
public:
    static unsigned int CreateShader(const std::filesystem::path& path, unsigned int shaderType);
    static unsigned int CreateProgram(unsigned int vertexShader, unsigned int fragmentShader);

private:
    static std::string ReadFile(const std::filesystem::path& filePath);
};
