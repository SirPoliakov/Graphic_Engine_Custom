#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

void Renderer::draw(const Shader& shader, Model& _model) const
{
    shader.use();
    _model.draw(shader);
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
