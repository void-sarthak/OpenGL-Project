#ifndef MESH_H
#define MESH_H

#include <Renderer.h>

#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

class Mesh
{
    private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    VertexArray *va;
    VertexBuffer *vb;
    IndexBuffer *ib;

    void SetUpMesh();

    public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();

    void Draw(Shader& shader);
    
};

#endif