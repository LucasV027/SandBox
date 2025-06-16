#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform usampler2D idTexture;
uniform vec3 materialColors[256];

void main() {
    uint id = texture(idTexture, TexCoord).r;
    FragColor = vec4(materialColors[id], 1.0);
}
