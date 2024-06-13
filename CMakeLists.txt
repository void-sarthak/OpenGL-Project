cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for header files
include_directories(include)
include_directories(external/glfw/include) # Include GLFW headers globally

# Add GLAD source files
add_library(glad STATIC lib/glad/src/glad.c)

# Add stb_image library
add_library(stb_image STATIC lib/stb/stb_image.cpp)

# Set platform-specific configurations
if (WIN32)
    # Windows specific configurations
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

    add_subdirectory(lib/glfw)

    set(PLATFORM_LIBS glfw ${CMAKE_DL_LIBS})
else()
    # Linux specific configurations
    find_package(PkgConfig REQUIRED)
    pkg_search_module(GLFW REQUIRED glfw3)
    set(PLATFORM_LIBS ${GLFW_LIBRARIES} ${CMAKE_DL_LIBS})  # Added ${CMAKE_DL_LIBS} for Linux
endif()

# Add source files
set(SOURCES 
    src/main.cpp
    src/VertexBuffer.cpp
    src/IndexBuffer.cpp
    src/VertexArray.cpp
    src/Shader.cpp
    src/Texture.cpp
    src/VertexBufferLayout.cpp
    src/Camera.cpp
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link GLFW, GLAD, and stb_image libraries
target_link_libraries(OpenGLProject glad glfw stb_image ${PLATFORM_LIBS})

