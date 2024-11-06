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

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.use();
    va.bind();
    ib.bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear() const
{
    GLCall(glClearColor(0.2f, 0.3f, 0.3f, 1.0f);)
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::swapBuffer(GLFWwindow* window) const
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}
