#include <Shader.h>
#include <IndexBuffer.h>
#include <VertexArray.h>
#include <Texture.h>
#include <Camera.h>

class Renderer
{
    private:
    glm::mat4 model;
    glm::mat4 projection;
    glm::mat4 view;

    Camera* camera;

    public:
    Renderer();
    ~Renderer();

    void Init();
    void Render();
    void SetCamera(Camera* camera);
};