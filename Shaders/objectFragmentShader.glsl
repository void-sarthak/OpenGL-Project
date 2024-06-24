#version 450 core

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D dragTex;

out vec4 FragColor;

void main()
{
    FragColor = texture(dragTex, texCoord);
}