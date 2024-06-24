
#include <Window.h>
#include <iostream>
#include <Model.h>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    Window window(SCR_WIDTH, SCR_HEIGHT, "OpenGL Project");
    if(!window.Init())
        return 0;
    
    Renderer renderer;
    renderer.Init();

    Model Dragon("Models/Dragon.glb");

    Shader shader("Shaders/vertexShader.glsl", "Shaders/objectFragmentShader.glsl");

    // Main loop
    while (!window.Close())
    {
        // per-frame time logic
        float currentFrame = static_cast<float>(glfwGetTime());
        window.UpdateFrame(currentFrame);

        // input
        window.ProcessInput();

        // Render here
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Dragon.DrawShader(shader);

        // renderer.SetCamera(window.GetCamera());
        // renderer.Render();
        
        window.SwapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}