#include "Shader.h"
#include "Renderer.h"

using std::cout;
using std::endl;

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
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
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    //Create shader
    unsigned int vertex, fragment;
    makeVertexShader(vertex, vShaderCode);
    shaderInfoLog(vertex, VERTEX_SHADER_ERROR);

    makeFragmentShader(fragment, fShaderCode);
    shaderInfoLog(fragment, FRAGMENT_SHADER_ERROR);

    // make shader Program
    makeProgram(ID, vertex, fragment);
    programInfoLog(ID, SHADER_PROGRAM_ERROR);

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(ID));
}



void Shader::makeVertexShader(unsigned int& shaderP, const char* shaderSrc)
{
    shaderP = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shaderP, 1, &shaderSrc, NULL);
    glCompileShader(shaderP);
}

void Shader::makeFragmentShader(unsigned int& shaderP, const char* shaderSrc)
{
    shaderP = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shaderP, 1, &shaderSrc, NULL);
    glCompileShader(shaderP);
}

void Shader::makeProgram(unsigned int& programP, unsigned int& vertexShader, unsigned int& fragmentShader)
{
    programP = glCreateProgram();
    glAttachShader(programP, vertexShader);
    glAttachShader(programP, fragmentShader);
    glLinkProgram(programP);
    glValidateProgram(programP);
}

bool Shader::shaderInfoLog(unsigned int& shaderP, const std::string ERROR_TYPE)
{
    GLint success = 0;

    glGetShaderiv(shaderP, GL_COMPILE_STATUS, &success);
    char infoLog[512];

    if (success != GL_TRUE)
    {
        glGetShaderInfoLog(shaderP, 512, NULL, infoLog);
        cout << ERROR_TYPE << infoLog << endl;
        return false;
    }
    else return true;
}

bool Shader::programInfoLog(unsigned int& shaderProgramP, const std::string ERROR_TYPE)
{
    GLint success = 0;
    GLint nbOfShaderAttached = 0;

    glGetProgramiv(shaderProgramP, GL_LINK_STATUS, &success);
    glGetProgramiv(shaderProgramP, GL_ATTACHED_SHADERS, &nbOfShaderAttached);
    char infoLog[512];

    if (success == GL_FALSE)
    {
        glGetProgramInfoLog(shaderProgramP, 512, NULL, infoLog);
        cout << ERROR_TYPE << infoLog << endl;
        return false;
    }
    else return true;
}

void Shader::use() const
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat2(const std::string& name, float value1, float value2) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), value1, value2);
}

void Shader::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


