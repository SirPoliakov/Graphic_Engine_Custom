#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "stb_image.h"


static void func(float& i, bool& plus)
{
    if (plus)
    {
        if (i+0.001f < 1.0f)
        {
            i += 0.001f;
        }
        else
        {
            plus = false;
            std::cout << "PLUS (+) ----> MOINS (-)" << std::endl;
        }
    }
    else
    {
        if (i - 0.001f > 0.0f)
        {
            i = i - 0.001f;
        }
        else
        {
            std::cout << "MOINS (-) ----> PLUS (+)" << std::endl;
            plus = true;
        }
    }
    std::cout << "i =  " << i << "  i should =    " << i-0.001f << std::endl;
}

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
             //Vertices          //Colors        //Tex Coord
         -0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,
          0.5f, 0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
          0.5f,-0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
         -0.5f,-0.5f, 0.0f,   0.0f, 0.0f, 0.0f,   0.0f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };


    // SHADERS
    const char* triangleVert = "Ressource\\Shaders\\Triangle.vert";
    const char* triangleFrag = "Ressource\\Shaders\\Triangle.frag";
    Shader rectangle = Shader(triangleVert, triangleFrag);

    

    // VAO, VBO, EBO...

    VertexArray vao;
    VertexBuffer vb = VertexBuffer(vertices1, 4 * 8 * sizeof(float));
    IndexBuffer ib = IndexBuffer(indices, 6);
   
    VertexBufferLayout vLayout;

    vLayout.push<float>(3);
    vLayout.push<float>(3);
    vLayout.push<float>(2);

    vao.addBuffer(vb, vLayout);

    // RENDERER 

    Renderer myRenderer;

    // TEXTURES 
    
    const char* path1 = "Ressource\\Textures\\container.jpg";
    const char* path2 = "Ressource\\Textures\\awesomeface.png";

    Image img1 = Image(path1, ImageFormat::JPG);
    Image img2 = Image(path2, ImageFormat::PNG);

    const std::vector<Image> images = { img1, img2};

    Texture tex = Texture(images);

    tex.setUniforms(rectangle);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    /* Loop until the user closes the window */
    float ocil = 0.0f; bool plus = true;
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        myRenderer.clear();
        func(ocil, plus);
        rectangle.setFloat("alphaRatio", ocil);
        myRenderer.draw(vao, ib, rectangle);
        /* Swap buffer and poll for and process events */
        myRenderer.swapBuffer(window);
    }


    GLCall(glfwTerminate());
    return 0;
}