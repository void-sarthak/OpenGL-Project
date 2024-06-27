#include <Window.h>
#include <iostream>
#include <Model.h>
#include <Renderer.h>
#include <thread>

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

    // Load model in a separate thread
    Model object("Models/backpack.obj");

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

        renderer.SetCamera(window.GetCamera());
        //renderer.Render();
        
        shader.Bind();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(window.GetCamera()->zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glm::mat4 view = glm::mat4();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = window.GetCamera()->GetViewMatrix();
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        shader.setMat4("model", model);

        object.DrawShader(shader);

        window.SwapBuffers();
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}