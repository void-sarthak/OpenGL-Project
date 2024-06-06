#ifndef INDEX_BUFFER
#define INDEX_BUFFER

#include <glad/glad.h>

class IndexBuffer
{
    private:
    unsigned int ID;
    unsigned int m_count;

    public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const; 

    inline unsigned int GetCount() const { return m_count; }
};

#endif