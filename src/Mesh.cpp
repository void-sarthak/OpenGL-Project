#include <Mesh.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetUpMesh();
}

Mesh::~Mesh()
{

}

void Mesh::SetUpMesh()
{
    va = new VertexArray();
    vb = new VertexBuffer(&vertices[0], vertices.size());
    ib = new IndexBuffer(&indices[0], indices.size()/sizeof(unsigned int));

    VertexBufferLayout layout;
    layout.Push<float>(3); // vertex positions
    layout.Push<float>(3); // vertex normals
    layout.Push<float>(2); // vertex textuure coords

    va->AddBuffer(*vb, layout);
}

void Mesh::Draw(Shader& shader)
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string name = textures[i].type; 

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);

        else if(name == "texture_specular")
            number = std::to_string(specularNr++);

        textures[i].Bind(i);
    }
    
    glActiveTexture(GL_TEXTURE0);

    // Draw the mesh
    va->Bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    va->Unbind();
}