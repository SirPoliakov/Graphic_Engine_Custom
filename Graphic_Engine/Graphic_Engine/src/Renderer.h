#pragma once
#include <intrin.h>
#include "Model.h"

class IndexBuffer;
class VertexArray;

class Renderer
{
private:

public:
    void draw(const Shader& shader, Model& _model) const;
    void clear() const;
    void swapBuffer(GLFWwindow* window) const;
};