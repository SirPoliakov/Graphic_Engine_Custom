#include <iostream>
#include <GL/glew.h>

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