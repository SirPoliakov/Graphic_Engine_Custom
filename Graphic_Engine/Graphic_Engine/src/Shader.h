#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


const std::string VERTEX_SHADER_ERROR = "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n";
const std::string FRAGMENT_SHADER_ERROR = "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n";
const std::string SHADER_PROGRAM_ERROR = "ERROR::SHADER_PROGRAM::LINKAGE_FAILED\n";

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void makeVertexShader(unsigned int& shaderP, const char* shaderSrc);
    void makeFragmentShader(unsigned int& shaderP, const char* shaderSrc);
    void makeProgram(unsigned int& programP, unsigned int& vertexShader, unsigned int& fragmentShader);

    bool shaderInfoLog(unsigned int& shaderP, const std::string ERROR_TYPE);
    bool programInfoLog(unsigned int& shaderProgramP, const std::string ERROR_TYPE);

    // use/activate the shader
    void use();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setFloat2(const std::string& name, float value1, float value2) const;
};

#endif