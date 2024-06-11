#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>

class Texture
{
    private:
    unsigned int ID;

    public:
    Texture(const char* path);
    ~Texture();

    void Bind(unsigned int slot) const;
    void Unbind() const;
};

#endif