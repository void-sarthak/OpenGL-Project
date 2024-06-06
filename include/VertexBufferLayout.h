#ifndef VERTEX_BUFFER_LAYOUT
#define VERTEX_BUFFER_LAYOUT

#include <vector>
#include <glad/glad.h>

struct VertexBufferElements
{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT :         return 4;
            case GL_UNSIGNED_INT :  return 4;
            case GL_UNSIGNED_BYTE : return 1;
        }
        return 0;
    }
};

class VertexBufferLayout
{
    private:
    std::vector<VertexBufferElements> elements;
    unsigned int stride;

    public:
    VertexBufferLayout()
        : stride(0) {}

    template<typename T>
    void Push(unsigned int count)
    {
    }

    template<>
    void Push<float>(unsigned int count)
    {
        elements.push_back({ GL_FLOAT, count, GL_FALSE });
        stride += count * VertexBufferElements::GetSizeOfType(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
        stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElements> GetElements() const& { return elements; }
    inline unsigned int GetStride() const { return stride; }
};

#endif