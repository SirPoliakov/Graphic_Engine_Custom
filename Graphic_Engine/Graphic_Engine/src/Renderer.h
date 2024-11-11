#pragma once
#include <intrin.h>
#include "Shader.h"


//#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) glClearError();\
                  x;\
                  glLogCall(#x, __FILE__, __LINE__);

void glClearError();
bool glLogCall(const char* function, const char* file, int line);


class IndexBuffer;
class VertexArray;
class Texture;

class Renderer
{
private:

public:
    void draw(const VertexArray& va, const Shader& shader, const unsigned int& count) const;
    void clear() const;
    void swapBuffer(GLFWwindow* window) const;
};