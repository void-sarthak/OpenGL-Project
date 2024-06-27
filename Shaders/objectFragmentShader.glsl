#version 450 core

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform sampler2D textureDiffuse0;
uniform sampler2D textureSpecular0;

out vec4 FragColor;

void main()
{
    FragColor = texture(textureDiffuse0, texCoord);
}