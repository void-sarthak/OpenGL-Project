#include <VertexArray.h>

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &ID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();

    const auto& elements = layout.GetElements();
    unsigned int offset = 0;
    for(unsigned int i = 0; i < elements.size(); i++)
    {
        const auto& element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, element.type, 
            element.normalized, layout.GetStride(), (const void *)(intptr_t)offset);
        
        offset += element.count * VertexBufferElements::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
}
