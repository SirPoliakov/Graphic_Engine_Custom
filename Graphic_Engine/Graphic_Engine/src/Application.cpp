#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "CameraManager.h"


const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// camera
CameraManager myCam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

//Lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
   if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);

    if (GLEW_OK != glewInit())
    {
        std::cout << "ERROR" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glEnable(GL_DEPTH_TEST));
               
    float vertices[] = {

            //positions          //normals            //texture coords
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
           -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
           -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
           -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
           -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
           -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
           -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
           -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
           -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
           -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    // positions all containers
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };


    // SHADERS
    const char* triangleVert = "Ressource\\Shaders\\Triangle.vert";
    const char* triangleFrag = "Ressource\\Shaders\\Triangle.frag";
    const char* lightVert = "Ressource\\Shaders\\light.vert";
    const char* lightFrag = "Ressource\\Shaders\\light.frag";

    Shader objectCube = Shader(triangleVert, triangleFrag);
    Shader lightCube = Shader(lightVert, lightFrag);
    

    // VAO, VBO, EBO...

    VertexArray cube_vao, light_vao;
    VertexBuffer vb = VertexBuffer(vertices, 36 * 8 * sizeof(float));
    //IndexBuffer ib = IndexBuffer(indices, 6);
   
    VertexBufferLayout vLayout;

    vLayout.push<float>(3);
    vLayout.push<float>(3);
    vLayout.push<float>(2);

    cube_vao.addBuffer(vb, vLayout);
    light_vao.addBuffer(vb, vLayout);
    // RENDERER 

    Renderer myRenderer;

    // TEXTURES 
    
    const char* path1 = "Ressource\\Textures\\container2.png";
    const char* path2 = "Ressource\\Textures\\container2_specular.png";
    //const char* path3 = "Ressource\\Textures\\matrix.jpg";

    Image img = Image(path1, ImageFormat::PNG, GLParameter::REPEAT);
    Image img2 = Image(path2, ImageFormat::PNG, GLParameter::REPEAT);
    //Image img3 = Image(path3, ImageFormat::JPG, GLParameter::CLAMP_TO_BORDER);

    const std::vector<Image> images = { img,img2};

    Texture tex = Texture(images);

    objectCube.use();
    objectCube.setInt("material.diffuse", 0);
    objectCube.setInt("material.specular", 1);

    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        /* Render here */
        myRenderer.clear();

        objectCube.use();

        //Position
        objectCube.setVec3("light.position", myCam.Position);
        objectCube.setVec3("light.direction", myCam.Front);
        objectCube.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        objectCube.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        objectCube.setVec3("viewPos", myCam.Position);

        //light properties
        objectCube.setVec3("light.ambient", 0.01f, 0.01f, 0.01f);
        objectCube.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
        objectCube.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        objectCube.setFloat("light.constant", 1.0f);
        objectCube.setFloat("light.linear", 0.09f);
        objectCube.setFloat("light.quadratic", 0.032f);

        // material properties
        objectCube.setFloat("material.shininess", 32.0f);
        
        glm::mat4 view = myCam.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);

        objectCube.setMat4("model", model);
        objectCube.setMat4("view", view);
        objectCube.setMat4("projection", projection);


        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            objectCube.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //lightCube.use();
        //lightCube.setMat4("projection", projection);
        //lightCube.setMat4("view", view);
        //model = glm::mat4(1.0f);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        //lightCube.setMat4("model", model);

        //myRenderer.draw(light_vao, lightCube, 36);

        /* Swap buffer and poll for and process events */
        myRenderer.swapBuffer(window);
    }


    GLCall(glfwTerminate());
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        myCam.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        myCam.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        myCam.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        myCam.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    myCam.ProcessMouseMovement(xoffset, yoffset);
}