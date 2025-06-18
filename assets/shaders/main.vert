#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform float zoom;
uniform vec2 offset;

void main() {
    vec2 scaledPos = aPos * zoom + offset;
    gl_Position = vec4(scaledPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
