#version 450 core

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.5f, 0.2f, 0.8f, 1.0f);
}