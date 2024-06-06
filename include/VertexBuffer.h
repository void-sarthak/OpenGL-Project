#ifndef VERTEX_BUFFER
#define VERTEX_BUFFER

#include <glad/glad.h>

class VertexBuffer
{
    private:
    unsigned int ID;

    public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const; 
};

#endif