#ifndef TEXTURE_H
#define TEXTURE_H

#include <stb/stb_image.h>
#include <glad/glad.h>
#include <iostream>
#include <string>

class Texture
{
    private:
    unsigned int ID;

    public:
    Texture(const char* path);
    ~Texture();

    std::string type;
    std::string path;

    void Bind(unsigned int slot) const;
    void Unbind() const;
};

#endif