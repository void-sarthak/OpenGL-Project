#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    private:
    unsigned int ID;

    public:
    Shader(const char *vertexShader, const char* fragmentShader);
    ~Shader();

    void shaderUse();

    void shaderSetBool(const std::string &name, bool value) const;
    void shaderSetInt(const std:: string &name, int value) const;
    void shaderSetFloat(const std::string &name, float value) const;

};

#endif
