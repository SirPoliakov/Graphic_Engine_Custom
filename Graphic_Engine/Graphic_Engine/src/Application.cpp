#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"

int main()
{
   
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
   if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (GLEW_OK != glewInit())
    {
        std::cout << "ERROR" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    

    float vertices1[] = {
         -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
          0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
          0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         -0.5,-0.5f, 0.0f, 0.0f, 0.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    float texCoords[] = {
    0.0f, 0.0f,  // lower-left corner  
    1.0f, 0.0f,  // lower-right corner
    0.5f, 1.0f   // top-center corner
    };

    VertexArray vao;
    VertexBuffer vb = VertexBuffer(vertices1, 4 * 6 * sizeof(float));
    IndexBuffer ib = IndexBuffer(indices, 6);
   
    VertexBufferLayout vLayout;
    vLayout.push<float>(3);
    vLayout.push<float>(3);
    vao.addBuffer(vb, vLayout);
    
    const char* triangleVert = "Ressource\\Shaders\\Triangle.vert";
    const char* triangleFrag = "Ressource\\Shaders\\Triangle.frag";
    Shader rectangle = Shader(triangleVert, triangleFrag);

    Renderer myRenderer;

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        myRenderer.clear();

        myRenderer.draw(vao, ib, rectangle);

        /* Swap buffer and poll for and process events */
        myRenderer.swapBuffer(window);
    }


    GLCall(glfwTerminate());
    return 0;
}