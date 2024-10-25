#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

constexpr int SCREEN_WIDTH = 1000;
constexpr int SCREEN_HEIGHT = 700;

int main(int argc, char* argv[])
{
    SDL_Window* window = nullptr;
    SDL_GLContext context;
    int flags = SDL_WINDOW_OPENGL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL failed to initialize" << std::endl;
        return 1;
    }

    // Initialize window and openGL
    window = SDL_CreateWindow("First triangle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, flags);
    context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE;
    glewInit();

    // Get info
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    // Tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    // Set viewport and clear color
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);

    // Load

    // Game loop
    bool isRunning = true;
    while (isRunning) {
        // Inputs
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            default:
                break;
            }
        }
        // Update


        // Draw
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

        // Draw here

        SDL_GL_SwapWindow(window); // Swapbuffer
    }


    // Quit
    SDL_DestroyWindow(window);
    SDL_GL_DeleteContext(context);

    return 0;
}