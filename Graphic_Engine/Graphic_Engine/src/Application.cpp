#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
//#include <glm/gtc/type_ptr.hpp>
#include "CameraManager.h"
#include "Shapes.h"
#include <map>


const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;


//void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// camera
CameraManager myCam(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float rotateX = 0.0f;
float rotateY = 0.0f;
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

    // SHADERS
    Shader myShader("Ressource/Shaders/blending.vert", "Ressource/Shaders/blending.frag");
    //Shader colorShader("Ressource/Shaders/depth_test.vert", "Ressource/Shaders/SingleColor.frag");

    unsigned int cubeSize = sizeof(cubeVertices);
    unsigned int planeSize = sizeof(planeVertices);
    unsigned int transparentSize = sizeof(transparentVertices);
   
    //CUBE VERTEX DATA
    VertexArray cubeVAO;
    VertexBuffer cubeVBO(cubeVertices, cubeSize);
    VertexBufferLayout vbLCube; vector<void*> offsetsCube;
    vbLCube.push(3); offsetsCube.push_back((void*)0);
    vbLCube.push(2); offsetsCube.push_back((void*)(3 * sizeof(float)));
    cubeVAO.addBuffer(cubeVBO, vbLCube, 5*sizeof(float), offsetsCube);
    cubeVAO.unbind();

    //PLANE VERTEX DATA

    VertexArray planeVAO;
    VertexBuffer planeVBO(planeVertices, planeSize);
    VertexBufferLayout vbLPlane; vector<void*> offsetsPlane;
    vbLPlane.push(3); offsetsPlane.push_back((void*)0);
    vbLPlane.push(2); offsetsPlane.push_back((void*)(3 * sizeof(float)));
    cubeVAO.addBuffer(planeVBO, vbLPlane, 5 * sizeof(float), offsetsPlane);
    planeVAO.unbind();

    //TRANSPARENT VERTEX DATA
    VertexArray transparentVAO;
    VertexBuffer transparentVBO(transparentVertices, transparentSize);
    VertexBufferLayout vbLTransparent; vector<void*> offsetsTransparent;
    vbLTransparent.push(3); offsetsTransparent.push_back((void*)0);
    vbLTransparent.push(2); offsetsTransparent.push_back((void*)(3 * sizeof(float)));
    transparentVAO.addBuffer(transparentVBO, vbLTransparent, 5 * sizeof(float), offsetsTransparent);


    // TEXTURES 
    unsigned int cubeTexture = loadTexture("Ressource/Textures/marble.jpg");
    unsigned int floorTexture = loadTexture("Ressource/Textures/metal.png");
    unsigned int grassTexture = loadTexture("Ressource/Textures/grass.png");

    vector<glm::vec3> grasses
    {
        glm::vec3(-1.5f, 0.0f, -0.48f),
        glm::vec3(1.5f, 0.0f, 0.51f),
        glm::vec3(0.0f, 0.0f, 0.7f),
        glm::vec3(0.0f, 0.0f, 0.7f),
        glm::vec3(-0.3f, 0.0f, -2.3f),
        glm::vec3(0.5f, 0.0f, -0.6f)
    };
    unsigned int windowsSize = grasses.size();

    myShader.use();
    myShader.setInt("texture1", 0);
    
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        /* Render here */

        //Clear
        GLCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));


        myShader.use();
        
        //Camera
        glm::mat4 view = myCam.GetViewMatrix();
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        myShader.setMat4("projection", projection);
        myShader.setMat4("view", view);

        ////Floor
        planeVAO.bind();
        GLCall(glBindTexture(GL_TEXTURE_2D, floorTexture));
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        
        myShader.setMat4("model", model);
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        planeVAO.unbind();

        //Cubes
        GLCall(glEnable(GL_CULL_FACE));
        GLCall(glCullFace(GL_BACK));
        //GLCall(glFrontFace(GL_CW));
        cubeVAO.bind();
        GLCall(glBindTexture(GL_TEXTURE_2D, cubeTexture));
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f)); // translate it down so it's at the center of the scene
        myShader.setMat4("model", model);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        myShader.setMat4("model", model);

        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        cubeVAO.unbind();

        //Transparent
        GLCall(glDisable(GL_CULL_FACE));
        transparentVAO.bind();
        GLCall(glBindTexture(GL_TEXTURE_2D, grassTexture)); 
       
        for (unsigned int i = 0; i < windowsSize ; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, grasses[i]);
            //if((i/2)*2 == i) model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            myShader.setMat4("model", model);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        }

        /* Swap buffer and poll for and process events */
        GLCall(glfwSwapBuffers(window));
        GLCall(glfwPollEvents());
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
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotateY -= 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotateY += 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        rotateX -= 2.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        rotateX += 2.0f;
    }
       
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