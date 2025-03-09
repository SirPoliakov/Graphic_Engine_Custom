#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Model.h"
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

    stbi_set_flip_vertically_on_load(true);

    GLCall(glEnable(GL_DEPTH_TEST));
   
    // SHADERS
    Shader myShader("Ressource/Shaders/Model_Load.vert", "Ressource/Shaders/Model_Load.frag");
    
    // TEXTURES 
    string const& path = "Ressource/Meshes/Guitare_BackPack/backpack.obj";
    Model myModel(path);

    // RENDERER 
    Renderer myRenderer;
    
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        /* Render here */
        myRenderer.clear();
        
        glm::mat4 view = myCam.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        myShader.setMat4("model", model);
        myRenderer.draw(myShader, myModel);

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