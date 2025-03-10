#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Texture.h"
#include <iostream>

using std::cout;
using std::endl;

void glClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
    {
        cout << "[OpenGL Error] ( " << error << " ) " << "Function : " << function << " " << "File ---> " << file << " : " << line << endl;
        return false;
    }

    return true;
}

void Renderer::draw(const VertexArray& va, const Shader& shader, const unsigned int& count) const
{
    shader.use();
    va.bind();
    //ib.bind();
    GLCall(glDrawArrays(GL_TRIANGLES, 0, count););
}

void Renderer::clear() const
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::swapBuffer(GLFWwindow* window) const
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
