#include <Renderer.h>

float vertices[] = {
    // positions          // normals         // texture coords
    // Front face
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f, // 0
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f, // 1
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f, // 2
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f, // 3

    // Back face
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f, // 4
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f, // 5
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f, // 6
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f, // 7

    // Left face
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // 8
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // 9
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // 10
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // 11

    // Right face
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f, // 12
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, // 13
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, // 14
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f, // 15

    // Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f, // 16
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f, // 17
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f, // 18
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f, // 19

    // Top face
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f, // 20
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f, // 21
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f, // 22
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f  // 23
};

unsigned int indices[] = {
    // Front face
    0, 1, 2,
    2, 3, 0,

    // Back face
    4, 5, 6,
    6, 7, 4,

    // Left face
    8, 9, 10,
    10, 11, 8,

    // Right face
    12, 13, 14,
    14, 15, 12,

    // Bottom face
    16, 17, 18,
    18, 19, 16,

    // Top face
    20, 21, 22,
    22, 23, 20
};

// Buffers for object
VertexArray *va;
IndexBuffer *ib;
Shader *basicShader;

// Buffers for Light
VertexArray *lightVA;
IndexBuffer *lightIB;
Shader *lightShader;

// Object Detail
glm::vec3 objAmbient = glm::vec3(0.8f, 0.3f, 0.5f);
glm::vec3 objDiffuse = glm::vec3(0.8f, 0.3f, 0.5f);
glm::vec3 objSpecular = glm::vec3(0.5f);

// Light Details
glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
glm::vec3 ambientColor = glm::vec3(0.1f);
glm::vec3 diffuseColor = glm::vec3(0.5f);
glm::vec3 specularColor = glm::vec3(1.0f); 
glm::mat4 lightModel = glm::mat4(1.0f);

Renderer::Renderer()
{
    model = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    view = glm::mat4(1.0f);
}

Renderer::~Renderer()
{

}

void Renderer::Init()
{
    va = new VertexArray();
    VertexBuffer vb(vertices, sizeof(vertices));

    VertexBufferLayout layout;

    layout.Push<float>(3);
    layout.Push<float>(3);
    layout.Push<float>(2);

    ib = new IndexBuffer(indices, 36);

    va->AddBuffer(vb, layout);

    basicShader = new Shader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");

    va->Unbind();
    vb.Unbind();
    ib->Unbind(); 

    lightVA = new VertexArray();
    VertexBuffer lightVB(vertices, sizeof(vertices));

    VertexBufferLayout lightLayout;
    lightLayout.Push<float>(3);
    lightLayout.Push<float>(3);
    lightLayout.Push<float>(2);

    lightIB = new IndexBuffer(indices, 36);
    lightShader = new Shader("Shaders/vertexShader.glsl", "Shaders/lightFragmentShader.glsl");


    lightVA->AddBuffer(lightVB, lightLayout);

    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.3f)); 

    lightVA->Unbind();
    lightVB.Unbind();
    lightIB->Unbind();
}

void Renderer::Render()
{
    view = camera->GetViewMatrix();

    // Use the shader
    basicShader->Bind();

    // Applying the transformations
    basicShader->setMat4("model", model);
    basicShader->setMat4("projection", projection);
    basicShader->setMat4("view", view);

    //Setting uniforms
    basicShader->setVec3("material.ambient", objAmbient);
    basicShader->setVec3("material.diffuse", objDiffuse);
    basicShader->setVec3("material.specular", objSpecular);
    basicShader->setFloat("material.shininess", 32.0f);

    basicShader->setVec3("light.position", lightPos);
    basicShader->setVec3("light.ambient", ambientColor);
    basicShader->setVec3("light.diffuse", diffuseColor);
    basicShader->setVec3("light.specular", specularColor);
    basicShader->setVec3("eyePos", camera->Position);

    // Binding vertex, indices and texture data to shader
    va->Bind();
    ib->Bind();

    //Drawing the scene
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);

    // Drawing the light
    lightShader->Bind();

    // Applying the transformations
    lightShader->setMat4("model", lightModel);
    lightShader->setMat4("projection", projection);
    lightShader->setMat4("view", view);

    lightVA->Bind();
    lightIB->Bind();

    // Setting uniform
    glm::vec3 lightColor = glm::vec3(1.0f);
    lightShader->setVec3("lightColor", lightColor);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
}

void Renderer::SetCamera(Camera* camera)
{
    this->camera = camera;
}