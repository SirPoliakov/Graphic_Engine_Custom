#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


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

    const char* triangleVert = "Ressource\\Shaders\\Triangle.vert";
    const char* triangleFrag = "Ressource\\Shaders\\Triangle.frag";

    Shader rectangle = Shader(triangleVert, triangleFrag);
    rectangle.use();

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

    VertexArray vao;
    VertexBuffer vb = VertexBuffer(vertices1, 4 * 6 * sizeof(float));
    IndexBuffer ib = IndexBuffer(indices, 6);
   
     

    //GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
    //GLCall(glEnableVertexAttribArray(0));
   
    VertexBufferLayout vLayout;
    vLayout.push<float>(3);
    vLayout.push<float>(3);
    vao.addBuffer(vb, vLayout);

    //GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
    //GLCall(glEnableVertexAttribArray(1));

    

   

   

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */

    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        vao.bind(); 
        ib.bind();
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));

        /* Swap buffer and poll for and process events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    GLCall(glfwTerminate());
    return 0;
}