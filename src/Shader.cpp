#include <Shader.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // Print paths for debugging
    // std::cout << "Vertex Shader Path: " << vertexPath << std::endl;
    // std::cout << "Fragment Shader Path: " << fragmentPath << std::endl;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // compile shaders
    unsigned int vertex, fragment;

    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

     // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    // print compile errors if any
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED" << std::endl;
        std::cout << infoLog << std::endl;
    }

    // delete shaders; they’re linked into our program and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{

}

void Shader::Use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    unsigned int location = glGetUniformLocation(ID, name.c_str());
    if(location == -1)
    {
        std::cout << "Location: " << name << " not found" << std::endl;
    }

    glUniform1i(location, (int)value);
}

void Shader::setInt(const std::string &name, int value) const
{
    unsigned int location = glGetUniformLocation(ID, name.c_str());

    if(location == -1)
    {
        std::cout << "Location: " << name << " not found" << std::endl;
    }

    glUniform1i(location, value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    unsigned int location = glGetUniformLocation(ID, name.c_str());

    if(location == -1)
    {
        std::cout << "Location: " << name << " not found" << std::endl;
    }

    glUniform1f(location, value);
}

void Shader::setMat4(const std::string &name, glm::mat4& value) const
{
    unsigned int location = glGetUniformLocation(ID, name.c_str());

    if(location == -1)
    {
        std::cout << "Location: " << name << " not found" << std::endl;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}