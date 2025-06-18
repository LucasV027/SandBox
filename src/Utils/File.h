#pragma once

#include <string>
#include <filesystem>
#include <fstream>

namespace File {
    inline std::string ReadFile(const std::filesystem::path& filePath) {
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
}
