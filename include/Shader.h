#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    void Use();

    void setBool(const std::string &name, bool value) const;
    void setInt(const std:: string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4& value) const;

};

#endif
