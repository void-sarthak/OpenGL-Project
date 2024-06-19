#version 450 core

struct Material
{
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

struct DirLight
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


in vec3 pos;
in vec3 normal;
in vec2 texCoord;

uniform Material material;

uniform DirLight dirLight;

#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

uniform vec3 eyePos;

out vec4 FragColor;

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

    vec3 finalColor = vec3(0.0);

    vec3 N = normalize(normal);
    vec3 E = normalize(eyePos - pos);

    finalColor += CalculateDirLight(dirLight, N, E);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        finalColor += CalcPointLight(pointLights[i], N, pos, E);

    FragColor = vec4(finalColor, 1.0);
}

vec3 CalculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 L = -normalize(light.direction);N
    vec3 R = reflect(-L, normal);

    float diff = max(dot(normal, L), 0.0);
    float spec = pow(max(dot(E, R), 0.0), material.shininess);

    vec3 color = vec3(texture(material.diffuse, texCoord));

    vec3 ambientColor = light.ambient * color;
    vec3 diffuseColor = diff * light.diffuse * color;
    vec3 specularColor = spec * light.specular * material.specular;

    return ambientColor + diffuseColor + specularColor;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3
viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance
    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));

    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuse,texCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}