#version 450 core

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform Material material;
uniform Light light;
uniform vec3 eyePos;

out vec4 FragColor;

void main()
{

    vec3 N = normalize(normal);
    vec3 L = normalize(light.position - pos);
    vec3 E = normalize(eyePos - pos);
    vec3 R = normalize(reflect(-L, N));

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(E, R), 0.0), material.shininess);

    vec3 ambientColor = light.ambient * material.ambient;
    vec3 diffuseColor = diff * light.diffuse * material.diffuse;
    vec3 specularColor = spec * light.specular * material.specular;

    vec3 finalColor = ambientColor + diffuseColor + specularColor;

    FragColor = vec4(finalColor, 1.0);
}