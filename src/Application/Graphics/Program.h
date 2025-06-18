#pragma once

#include <filesystem>
#include <fstream>
#include <unordered_map>

class Program {
public:
    Program() = default;
    ~Program();

    void Create(const std::filesystem::path& vertexShader,
                const std::filesystem::path& fragmentShader);

    void LocateVariable(const std::string& name);

    void SetUniform1i(const std::string& name, int v) const;
    void SetUniform1f(const std::string& name, float v) const;
    void SetUniform2f(const std::string& name, float v1, float v2) const;
    void SetUniform3fv(const std::string& name, int count, const float* v) const;

    void Bind() const;
    void UnBind() const;

private:
    static unsigned int CompileShader(const std::filesystem::path& path, unsigned int shaderType);

private:
    unsigned int shaderProgramme = 0;
    std::unordered_map<std::string, int> locations;
};
