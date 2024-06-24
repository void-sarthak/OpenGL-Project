#include <Window.h>

// Initialize static member
Window* Window::instance = nullptr;

// Constructor
Window::Window(unsigned int width, unsigned int height, const char* title)
    : width(width), height(height), title(title),
      window(nullptr), camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f),
      lastX(width / 2.0f), lastY(height / 2.0f), firstMouse(true), leftMouseButtonHeld(false),
      deltaTime(0.0f), lastFrame(0.0f)
{
    // Store this instance for callback functions
    instance = this;
}

// Destructor
Window::~Window()
{
    glfwTerminate();
}

// Initialize the window
bool Window::Init()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create the window
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    // Make the OpenGL context current
    glfwMakeContextCurrent(window);

    // Set callbacks
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);

    // Load OpenGL function pointers using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    // Configure OpenGL state
    glEnable(GL_DEPTH_TEST);

    return true;
}

// Close
bool Window::Close()
{
    return glfwWindowShouldClose(window);
}

// Process input
void Window::ProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void Window::UpdateFrame(float currentFrame)
{
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(window);
}

// Callback functions
void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (!instance->leftMouseButtonHeld)
        return;

    if (instance->firstMouse)
    {
        instance->lastX = (float)xpos;
        instance->lastY = (float)ypos;
        instance->firstMouse = false;
    }

    float xoffset = (float)xpos - instance->lastX;
    float yoffset = instance->lastY - (float)ypos;

    instance->lastX = (float)xpos;
    instance->lastY = (float)ypos;

    instance->camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void Window::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    instance->camera.ProcessScroll((float)yoffset);
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            instance->leftMouseButtonHeld = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // Show the cursor
        }
        else if (action == GLFW_RELEASE)
        {
            instance->leftMouseButtonHeld = false;
            instance->firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Hide the cursor
        }
    }
}
