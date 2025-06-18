#include "DebugCallBack.h"

#include <iostream>

#include "glad/glad.h"

namespace {
    // clang-format off
    const char* GetSourceString(const unsigned int source) {
        switch (source) {
            case GL_DEBUG_SOURCE_API:             return "API";
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "Window System";
            case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
            case GL_DEBUG_SOURCE_THIRD_PARTY:     return "Third Party";
            case GL_DEBUG_SOURCE_APPLICATION:     return "Application";
            case GL_DEBUG_SOURCE_OTHER:           return "Other";
            default: return "Unknown Source";
        }
    }

    const char* GetTypeString(const unsigned int type) {
        switch (type) {
            case GL_DEBUG_TYPE_ERROR:               return "Error";
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behaviour";
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "Undefined Behaviour";
            case GL_DEBUG_TYPE_PORTABILITY:         return "Portability";
            case GL_DEBUG_TYPE_PERFORMANCE:         return "Performance";
            case GL_DEBUG_TYPE_MARKER:              return "Marker";
            case GL_DEBUG_TYPE_PUSH_GROUP:          return "Push Group";
            case GL_DEBUG_TYPE_POP_GROUP:           return "Pop Group";
            case GL_DEBUG_TYPE_OTHER:               return "Other";
            default: return "Unknown Type";
        }
    }

    const char* GetSeverityString(const unsigned int severity) {
        switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:         return "High";
            case GL_DEBUG_SEVERITY_MEDIUM:       return "Medium";
            case GL_DEBUG_SEVERITY_LOW:          return "Low";
            case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
            default: return "Unknown Severity";
        }
    }
    // clang-format on
} // namespace

void OpenGLErrorCallback(unsigned int source, unsigned int type, unsigned int id,
                         unsigned int severity, int, const char* message, const void*) {
    // Ignore trivial notifications
    if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
        return;

    std::cerr << "---------------\n";
    std::cerr << "Debug message (" << id << "): " << message << "\n";
    std::cerr << "Source: " << GetSourceString(source) << "\n";
    std::cerr << "Type: " << GetTypeString(type) << "\n";
    std::cerr << "Severity: " << GetSeverityString(severity) << "\n\n";
}
