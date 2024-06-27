#include <VertexBufferLayout.h>

// Define the specialization for float
template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    elements.push_back({ GL_FLOAT, count, GL_FALSE });
    stride += count * VertexBufferElements::GetSizeOfType(GL_FLOAT);
}

// Define the specialization for unsigned int
template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_INT);
}

// Define the specialization for unsigned char
template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    stride += count * VertexBufferElements::GetSizeOfType(GL_UNSIGNED_BYTE);
}