#version 450 core

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform vec3 objectColor;
uniform vec3 eyePos;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform sampler2D ourTexture;

out vec4 FragColor;

void main()
{
    float ambientStrength = 0.1;
    float specularStrength = 0.5;

    vec3 N = normalize(normal);
    vec3 L = normalize(lightPos - pos);
    vec3 E = normalize(eyePos - pos);
    vec3 R = normalize(reflect(-L, N));

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(E, R), 0.0), 32);

    vec3 ambientColor = ambientStrength * lightColor;
    vec3 diffuseColor = diff * lightColor;
    vec3 specularColor = specularStrength * spec * lightColor;

    vec3 finalColor = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(finalColor * objectColor, 1.0);
}