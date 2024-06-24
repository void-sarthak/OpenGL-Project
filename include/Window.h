#ifndef WINDOW_H
#define WINDOW_H

#include <Camera.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
    // Constructor
    Window(unsigned int width, unsigned int height, const char* title);
    // Destructor
    ~Window();

    // Initialize the window
    bool Init();

    // Main loop
    bool Close();

    // Process input
    void ProcessInput();

    // Update frames and time
    void UpdateFrame(float currentFrame);

    // Swap the buffers
    void SwapBuffers();

    // Getter for camera
    Camera* GetCamera() { return &camera; }

    // Getter for GLFW window
    GLFWwindow* GetWindow() const { return window; }

private:
    // Window dimensions
    unsigned int width;
    unsigned int height;
    const char* title;

    // GLFW window
    GLFWwindow* window;

    // Camera
    Camera camera;
    float lastX;
    float lastY;
    bool firstMouse;
    bool leftMouseButtonHeld;

    // Timing
    float deltaTime;
    float lastFrame;

    // Callbacks
    static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

    // Static members to store class instances for GLFW callbacks
    static Window* instance;
};

#endif
