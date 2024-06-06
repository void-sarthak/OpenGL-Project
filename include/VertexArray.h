#ifndef VERTEX_ARRAY
#define VERTEX_ARRAY

#include <VertexBuffer.h>
#include <VertexBufferLayout.h>

class VertexArray
{
    private:
    unsigned int ID;

    public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void Bind() const;
    void Unbind() const;
};

#endif